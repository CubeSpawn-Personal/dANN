/******************************************************************************
 *                                                                             *
 *  Copyright: (c) Syncleus, Inc.                                              *
 *                                                                             *
 *  You may redistribute and modify this source code under the terms and       *
 *  conditions of the Open Source Community License - Type C version 1.0       *
 *  or any later version as published by Syncleus, Inc. at www.syncleus.com.   *
 *  There should be a copy of the license included with this file. If a copy   *
 *  of the license is not included you are granted no right to distribute or   *
 *  otherwise use this file except through a legal and valid license. You      *
 *  should also contact Syncleus, Inc. at the information below if you cannot  *
 *  find a license:                                                            *
 *                                                                             *
 *  Syncleus, Inc.                                                             *
 *  2604 South 12th Street                                                     *
 *  Philadelphia, PA 19148                                                     *
 *                                                                             *
 ******************************************************************************/

/*
 * Derived from Public-Domain source as indicated at
 * http://math.nist.gov/javanumerics/jama/ as of 9/13/2009.
 */
package com.syncleus.dann.math.linear.decomposition;

import java.util.*;
import com.syncleus.dann.math.OrderedAlgebraic;
import com.syncleus.dann.math.linear.Matrix;

/**
 * QR Decomposition.
 * <p/>
 * For an m-by-n matrix matrixToDecompose with m >= n, the QR decomposition is
 * an m-by-n orthogonal matrix factor and an n-by-n upper triangular matrix
 * factor so that matrixToDecompose = factor*factor.
 * <p/>
 * The QR decompostion always exists, even if the matrix does not have full
 * rank, so the constructor will never fail.  The primary use of the QR
 * decomposition is in the least squares solution of nonsquare systems of
 * simultaneous linear equations.  This will fail if isFullRank() returns
 * false.
 */
public class HouseholderQrDecomposition<M extends Matrix<M, F>, F extends OrderedAlgebraic<F>> implements java.io.Serializable, QrDecomposition<M, F>
{
	private static final long serialVersionUID = -2181312959012242588L;
	/**
	 * Array for internal storage of decomposition.
	 */
	private M matrix;
	/**
	 * Array for internal storage of diagonal of factor.
	 */
	private final List<F> rDiagonal;

	/**
	 * QR Decomposition, computed by Householder reflections. gives access to
	 * factor and the Householder vectors and compute factor.
	 *
	 * @param matrixToDecompose Rectangular matrix
	 */
	public HouseholderQrDecomposition(final M matrixToDecompose)
	{
		// Initialize.
		this.matrix = matrixToDecompose;
		this.rDiagonal = new ArrayList<F>(this.getWidth());
		this.rDiagonal.addAll(Collections.nCopies(this.getWidth(), this.matrix.getElementField().getZero()));

		// Main loop.
		for(int k = 0; k < this.getWidth(); k++)
		{
			// Compute 2-norm of k-th column without under/overflow.
			F nrm = this.matrix.getElementField().getZero();
			for(int i = k; i < this.getHeight(); i++)
				nrm = nrm.hypot(this.matrix.get(i, k));

			if( !nrm.equals(this.matrix.getElementField().getZero()) )
			{
				// Form k-th Householder vector.
				if( this.matrix.get(k, k).compareTo(this.matrix.getElementField().getZero()) < 0 )
					nrm = nrm.negate();
				for(int i = k; i < this.getHeight(); i++)
					this.matrix = this.matrix.set(i, k, this.matrix.get(i, k).divide(nrm));
				this.matrix = this.matrix.set(k, k, this.matrix.get(k, k).add(this.matrix.getElementField().getOne()));

				// Apply transformation to remaining columns.
				for(int j = k + 1; j < this.getWidth(); j++)
				{
					F s = this.matrix.getElementField().getZero();
					for(int i = k; i < this.getHeight(); i++)
						s = s.add(this.matrix.get(i, k).multiply(this.matrix.get(i, j)));
					s = s.negate().divide(this.matrix.get(k, k));
					for(int i = k; i < this.getHeight(); i++)
						this.matrix = this.matrix.set(i, j, this.matrix.get(i, j).add(s.multiply(this.matrix.get(i, k))));
				}
			}
			this.rDiagonal.set(k, nrm.negate());
		}
	}

	public final M getMatrix()
	{
		return this.matrix;
	}

	public final int getHeight()
	{
		return this.matrix.getHeight();
	}

	public final int getWidth()
	{
		return this.matrix.getWidth();
	}

	/**
	 * Is the matrix full rank?
	 *
	 * @return true if factor, and hence matrixToDecompose, has full rank.
	 */
	public boolean isFullRank()
	{
		for(int j = 0; j < this.getWidth(); j++)
			if( this.rDiagonal.get(j).equals(this.matrix.getElementField().getZero()) )
				return false;
		return true;
	}

	/**
	 * Return the Householder vectors
	 *
	 * @return Lower trapezoidal matrix whose columns define the reflections
	 */
	public M getHouseholderMatrix()
	{
		M householderMatrix = this.matrix.blank();
		for(int i = 0; i < this.getHeight(); i++)
			for(int j = 0; j < this.getWidth(); j++)
				if( i >= j )
					householderMatrix = householderMatrix.set(i, j, this.matrix.get(i, j));
		return householderMatrix;
	}

	/**
	 * Return the upper triangular factor
	 *
	 * @return factor
	 */
	public M getUpperTriangularFactor()
	{
		M factor = this.matrix.blank();
		for(int i = 0; i < this.getWidth(); i++)
			for(int j = 0; j < this.getWidth(); j++)
				if( i < j )
					factor = factor.set(i, j, this.matrix.get(i, j));
				else if( i == j )
					factor = factor.set(i, j, this.rDiagonal.get(i));
		return factor;
	}

	/**
	 * Generate and return the (economy-sized) orthogonal factor
	 *
	 * @return factor
	 */
	public M getOrthogonalFactor()
	{
		M factor = this.matrix.blank();
		for(int k = this.getWidth() - 1; k >= 0; k--)
		{
			for(int i = 0; i < this.getHeight(); i++)
				factor = factor.set(i, k, this.matrix.getElementField().getZero());
			factor = factor.set(k, k, this.matrix.getElementField().getOne());
			for(int j = k; j < this.getWidth(); j++)
				if( !this.matrix.get(k, k).equals(this.matrix.getElementField().getOne()) )
				{
					F s = this.matrix.getElementField().getZero();
					for(int i = k; i < this.getHeight(); i++)
						s = s.add(this.matrix.get(i, k).multiply(factor.get(i, j)));
					s = s.negate().divide(this.matrix.get(k, k));
					for(int i = k; i < this.getHeight(); i++)
						factor = factor.set(i, j, factor.get(i, j).add(s.multiply(this.matrix.get(i, k))));
				}
		}
		return factor;
	}

	/**
	 * Least squares solution of matrixToDecompose*X = solutionMatrix
	 *
	 * @param solutionMatrix matrixToDecompose SimpleRealMatrix with as many rows
	 * as matrixToDecompose and any number of columns.
	 * @return X that minimizes the two norm of factor*factor*X-solutionMatrix.
	 * @throws IllegalArgumentException SimpleRealMatrix row dimensions must
	 * agree.
	 * @throws RuntimeException SimpleRealMatrix is rank deficient.
	 */
	public M solve(final M solutionMatrix)
	{
		if( solutionMatrix.getHeight() != this.getHeight() )
			throw new IllegalArgumentException("solutionMatrix row dimensions must agree.");
		if( !this.isFullRank() )
			throw new ArithmeticException("Matrix is rank deficient.");

		// Copy right hand side
		final int nx = solutionMatrix.getWidth();
		M solved = solutionMatrix;

		// Compute Y = transpose(factor)*solutionMatrix
		for(int k = 0; k < this.getWidth(); k++)
			for(int j = 0; j < nx; j++)
			{
				F s = this.matrix.getElementField().getZero();
				for(int i = k; i < this.getHeight(); i++)
					s = s.add(this.matrix.get(i, k).multiply(solved.get(i, j)));
				s = s.negate().divide(this.matrix.get(k, k));
				for(int i = k; i < this.getHeight(); i++)
					solved = solved.set(i, j, solved.get(i, j).add(s.multiply(this.matrix.get(i, k))));
			}
		// Solve factor*X = Y;
		for(int k = this.getWidth() - 1; k >= 0; k--)
		{
			for(int j = 0; j < nx; j++)
				solved = solved.set(k, j, solved.get(k, j).divide(this.rDiagonal.get(k)));
			for(int i = 0; i < k; i++)
				for(int j = 0; j < nx; j++)
					solved = solved.set(i, j, solved.get(i, j).subtract(solved.get(k, j).multiply(this.matrix.get(i, k))));
		}

		return solved.getSubmatrix(0, this.getWidth() - 1, 0, nx - 1);
	}
}

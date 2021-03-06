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
package com.syncleus.dann.graphicalmodel.bayesian;

import java.util.List;
import com.syncleus.dann.graph.AbstractDirectedEdge;
import com.syncleus.dann.graph.ImmutableDirectedEdge;

public final class SimpleBayesianEdge<N extends BayesianNode> extends AbstractDirectedEdge<N> implements BayesianEdge<N>
{
	private static final long serialVersionUID = 5817768183659411136L;

	public SimpleBayesianEdge(final N source, final N destination)
	{
		super(source, destination);
	}

	public SimpleBayesianEdge(final N source, final N destination, final boolean allowJoiningMultipleGraphs, final boolean contextEnabled)
	{
		super(source, destination, allowJoiningMultipleGraphs, contextEnabled);
	}

	public Object getState()
	{
		return this.getSourceNode().getState();
	}

	@Override
	public SimpleBayesianEdge<N> disconnect(final N node)
	{
		return (SimpleBayesianEdge<N>) this.remove(node);
	}

	@Override
	public SimpleBayesianEdge<N> disconnect(final List<N> nodes)
	{
		return (SimpleBayesianEdge<N>) this.remove(nodes);
	}

	@Override
	public SimpleBayesianEdge<N> clone()
	{
		return (SimpleBayesianEdge<N>) super.clone();
	}
}

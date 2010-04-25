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
package com.syncleus.dann.graph.topological;

import com.syncleus.dann.graph.*;
import java.util.*;

public class SimpleTopologicalSorter<N> implements TopologicalSorter<N>
{
	public List<N> sort(BidirectedGraph<? extends N,? extends DirectedEdge<? extends N>> graph)
	{
		//initialize data structures
		final Set<N> nodes = new HashSet<N>(graph.getNodes());
		final Set<DirectedEdge<? extends N>> edges = new HashSet<DirectedEdge<? extends N>>(graph.getEdges());
		final Map<N, Set<DirectedEdge<? extends N>>> neighborEdges = new HashMap<N, Set<DirectedEdge<? extends N>>>();
		for(DirectedEdge<? extends N> edge : edges)
		{
			final List<? extends N> edgeNodes = edge.getNodes();
			for(int startNodeIndex = 0; startNodeIndex < edgeNodes.size(); startNodeIndex++)
			{
				if(!nodes.contains(edgeNodes.get(startNodeIndex)))
					throw new IllegalArgumentException("A node that is an end point in one of the edges was not in the nodes list");

				Set<DirectedEdge<? extends N>> startNeighborEdges = neighborEdges.get(edgeNodes.get(startNodeIndex));
				if( startNeighborEdges == null )
				{
					startNeighborEdges = new HashSet<DirectedEdge<? extends N>>();
					neighborEdges.put(edgeNodes.get(startNodeIndex), startNeighborEdges);
				}
				startNeighborEdges.add(edge);
			}
		}

		//pull a node of 0 degree then delete
		final List<N> topologicalNodes = new ArrayList<N>();
		while( !nodes.isEmpty() )
		{
			int preNodeCount = nodes.size();
			for( N node : nodes )
			{
				if( getIndegree(edges, node) == 0)
				{
					topologicalNodes.add(node);

					//delete node
					Set<DirectedEdge<? extends N>> neighbors = neighborEdges.get(node);
					for(DirectedEdge<? extends N> neighbor : neighbors)
					{
						List<N> adjacentNodes = new ArrayList<N>(neighbor.getNodes());
						adjacentNodes.remove(node);
						N adjacentNode = adjacentNodes.get(0);

						//delete the edge from the neighbor map
						Set<DirectedEdge<? extends N>> deleteFromEdges = neighborEdges.get(adjacentNode);
						deleteFromEdges.remove(neighbor);

						//delete the edge from edges
						edges.remove(neighbor);
					}
					nodes.remove(node);

					//since we found a nod with 0 in degree and removed it we should back out
					break;
				}
			}
			if( preNodeCount <= nodes.size() )
				return null;
		}

		return topologicalNodes;
	}

	public int getIndegree(Set<DirectedEdge<? extends N>> edges, N node)
	{
		int inDegree = 0;
		for(DirectedEdge<? extends N> edge : edges)
			if(edge.getDestinationNode() == node)
				inDegree++;
		return inDegree;
	}
}

/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }
    Vertex start = graph.getStartingVertex();
    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start, "VISITED");
    int res = INT_MAX;
    Vertex resSource, resDest;
    while (!q.empty()) {
      Vertex v = q.front();
      q.pop();
      vector<Vertex> adjacents = graph.getAdjacent(v);
      for (size_t i = 0; i < adjacents.size(); i++) {
        Vertex w = adjacents[i];
        if (graph.getVertexLabel(w) == "UNEXPLORED") {
          graph.setEdgeLabel(v, w, "VISITED");
          if (graph.getEdgeWeight(v, w) < res) {
            res = graph.getEdgeWeight(v, w);
            resSource = v;
            resDest = w;
          }
          graph.setVertexLabel(w, "VISITED");
          q.push(w);
        } else if (graph.getEdgeLabel(v, w) == "UNEXPLORED") {
          if (graph.getEdgeWeight(v, w) < res) {
            res = graph.getEdgeWeight(v, w);
            resSource = v;
            resDest = w;
          }
          graph.setEdgeLabel(v, w, "VISITED");
        }
      }
    }
    graph.setEdgeLabel(resSource, resDest, "MIN");
    return res;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here!*/
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }
    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start, "VISITED");
    unordered_map<Vertex, Vertex> parent;
    while (!q.empty()) {
      Vertex v = q.front();
      q.pop();
      vector<Vertex> adjacents = graph.getAdjacent(v);
      for (size_t i = 0; i < adjacents.size(); i++) {
        Vertex w = adjacents[i];
        if (graph.getVertexLabel(w) == "UNEXPLORED") {
          graph.setEdgeLabel(v, w, "DISCOVERY");
          graph.setVertexLabel(w, "VISITED");
          // if (w == end) {
          //   parent[w] = v;
          //   break;
          // }
          q.push(w);
          parent[w] = v;
        } else if (graph.getEdgeLabel(v, w) == "UNEXPLORED") {
          graph.setEdgeLabel(v, w, "CROSS");
        }
      }
      // if (graph.getVertexLabel(end) == "VISITED") {
      //   break;
      // }
    }
    int res = 0;
    while (end != start) {
      graph.setEdgeLabel(end, parent[end], "MINPATH");
      end = parent[end];
      res++;
    }
    return res;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());
    vector<Vertex> vertices = graph.getVertices();
    DisjointSets dset;
    dset.addelements(vertices.size());
    unordered_map<Vertex, unsigned> dict;
    for (unsigned i = 0; i < vertices.size(); i++) {
      dict[vertices[i]] = i;
    }
    unsigned count = 1;
    for (size_t i = 0; i < edges.size(); i++) {
      unsigned source = dict[edges[i].source];
      unsigned dest = dict[edges[i].dest];
      if (dset.find(source) != dset.find(dest)) {
        dset.setunion(source, dest);
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
        count++;
      }
      if (count == vertices.size()) {
        break;
      }
    }
}

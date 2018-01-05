/*
 * graph.cpp
 * Author: Huili Yu
 */

// Headers
#include "../include/graph.h"
#include <stdlib.h>
#include <assert.h>
#include <iostream>

namespace dijkstra
{
void Graph::Init(int num_of_nodes)
{
  if (num_of_nodes <= 0) {
    std::cerr << "The number of graph nodes "
    "needs to be greater than zero" << std::endl;
    exit(EXIT_FAILURE);
  }
  num_of_nodes_ = num_of_nodes;

  for (int i = 0; i < num_of_nodes_; ++i) {
    adjacency_lists_.push_back(new AdjacencyList());
  }
}

// Use the adjacency list to represent the graph
void Graph::AddEdge(int src_idx, int dest_idx, int weight)
{
  assert(src_idx >= 0 && dest_idx >= 0);
  assert(src_idx < num_of_nodes_ && dest_idx < num_of_nodes_);
  assert(src_idx != dest_idx);

  // Add an edge from source node to destination node
  GraphNode *new_node = new GraphNode(dest_idx, weight);
  adjacency_lists_[src_idx]->adjlist.push_back(new_node);

  // Add an undirected graph, add an edge from
  // destination node to source node
  new_node = new GraphNode(src_idx, weight);
  adjacency_lists_[dest_idx]->adjlist.push_back(new_node);
}

AdjacencyList * Graph::ExtractNeighbors(int node_idx)
{
  assert(node_idx >= 0 && node_idx < num_of_nodes_);
  return adjacency_lists_[node_idx];
}

int Graph::GetNumberOfNodes()
{
  return num_of_nodes_;
}

void Graph::PrintGraph()
{
  if (num_of_nodes_ == 0) {
    std::cerr << "The number of graph nodes is zero." << std::endl;
    return;
  }
  for (int i = 0; i < num_of_nodes_; ++i) {
    std::vector<GraphNode *> tmp = adjacency_lists_[i]->adjlist;
    int m = (int)tmp.size();
    for (int j = 0; j < m; j++) {
      std::cout << "(" << tmp[j]->label << ", "
          << tmp[j]->weight << ")" << "-->";
    }
        std::cout << std::endl;
  }
}

Graph::~Graph()
{
  for (int i = 0; i < num_of_nodes_; ++i) {
    std::vector<GraphNode *> tmp = adjacency_lists_[i]->adjlist;
    int m = (int)tmp.size();
    for (int j = 0; j < m; j++) {
      delete tmp[j];
    }
    delete adjacency_lists_[i];
  }
}
}  // namespace dijkstra

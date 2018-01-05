/*
 * dijkstra.cpp
 * Author: Huili Yu
 */

#include "../include/dijkstra.h"
#include <assert.h>
#include <climits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

namespace dijkstra
{
// Constructor
Dijkstra::Dijkstra(std::string &connectivity_file)
{
  // Load node connectivity from file
  std::ifstream ifs(connectivity_file.c_str());
  std::string line, val;
  int num_of_nodes;
  std::vector<std::vector<int> > connectivity;
  if (ifs.is_open()) {
    while (std::getline(ifs, line)) {
      if (line.empty() || line[0] == '#') continue;
      if (line.find(',') == std::string::npos) {
        num_of_nodes = atoi(line.c_str());
        continue;
      }
      std::vector<int> tmp(3);
      std::stringstream ss(line);
      for (int i = 0; i < 3; ++i) {
        std::getline(ss, val, ',');
        tmp[i] = atoi(val.c_str());
      }
      connectivity.push_back(tmp);
    }
    ifs.close();
  }
  else {
    std::cerr << "Failed to open the connectivity file." << std::endl;
    exit(EXIT_FAILURE);
  }

  // Create graph
  graph_.Init(num_of_nodes);
  for (int i = 0; i < (int)connectivity.size(); ++i) {
    graph_.AddEdge(connectivity[i][0],
                   connectivity[i][1],
                   connectivity[i][2]);
  }
}

// Find the shortest path using heap
int Dijkstra::FindShortestPath(int start_idx,
                               int end_idx,
                               std::vector<int> &path)
{
  // initialize the graph node
  int num_of_nodes = graph_.GetNumberOfNodes();
  assert(start_idx >= 0 && end_idx >= 0);
  assert(start_idx < num_of_nodes && end_idx < num_of_nodes);
  assert(start_idx != end_idx);
  Heap<int, int> Q(num_of_nodes);

  std::vector<int> dist(num_of_nodes, INT_MAX);
  dist[start_idx] = 0;
  std::vector<int> prev(num_of_nodes, -1);

  Dataum<int, int> node(start_idx, dist[start_idx]);
  Q.Insert(node);

  // main loop
  while (Q.GetNumOfItems() > 0) {
    Dataum<int, int> min_dataum = Q.ExtractMin();
    int u = min_dataum.idx;
    std::vector<GraphNode *> adjlist =
        graph_.ExtractNeighbors(u)->adjlist;
    for (int i = 0; i < (int)adjlist.size(); i++) {
      int v = adjlist[i]->label;
      int weight = adjlist[i]->weight;
      if (dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        Dataum<int, int> tmp(v, dist[v]);
        // Update heap
        if (!Q.Modify(tmp)) {
          Q.Insert(tmp);
        }
        prev[v] = u;
      }
    }
  }

  // Extract the shortest path
  int tmp_idx = end_idx;
  while (tmp_idx != -1) {
    path.push_back(tmp_idx);
    tmp_idx = prev[tmp_idx];
  }
  reverse(path.begin(), path.end());
  return dist[end_idx];
}

// Print the path
void Dijkstra::PrintPath(std::vector<int> &path)
{
  int n = (int)path.size();
  if (n == 0) {
    std::cerr << "The number of path nodes is zero." << std::endl;
    return;
  }
  for (int i = 0; i < n; i++) {
    if (i < n - 1) {
      std::cout << path[i] << "->";
    }
    else {
      std::cout << path[i] << std::endl;
    }
  }
}
}  // namespace dijkstra

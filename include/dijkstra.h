/*
 * dijkstra.h
 * This file is a class for Dijkstra's algorithm using the heap
 * data structure and a graph with adjacency list representation
 * Author: Huili Yu
 */

#ifndef INCLUDES_DIJKSTRA_H_
#define INCLUDES_DIJKSTRA_H_

#include <vector>
#include <string>
#include "../include/graph.h"
#include "../include/heap.h"

namespace dijkstra
{
typedef struct Node
{
  int node_idx;
  int dist;
  Node() {};
  Node(int idx, int dst) : node_idx(idx), dist(dst) {};
} Node;

struct compare
{
  bool operator()(const Node &l, const Node &r) const
  {
    return l.dist > r.dist;
  }
};

class Dijkstra
{
 public:
  Dijkstra() {};

  /*
   * Constructor
   * @param connectivity_file: a string to specify
   * the file for graph node connectivity
   */
  Dijkstra(std::string &connectivity_file);

  /*
   * FindShortestPath function finds the shortest path between two nodes
   * @param start_idx: the index of start node
   * @param end_idx: the index of end node
   * @param path: vector contains the node indices of the shortest path
   */
  int FindShortestPath(int start_idx, int end_idx,
                       std::vector<int> &path);

  /*
   * PrintPath function displays the shortest path
   */
  void PrintPath(std::vector<int> &path);

  virtual ~Dijkstra() {};
 private:
  Graph graph_;
};
}  // namespace dijkstra

#endif /* INCLUDES_DIJKSTRA_H_ */

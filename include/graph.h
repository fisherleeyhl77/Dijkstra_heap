/*
 * graph.h
 * Author: Huili Yu
 */

#ifndef INCLUDES_GRAPH_H_
#define INCLUDES_GRAPH_H_

// Headers
#include <vector>

namespace dijkstra
{
// Types
typedef struct GraphNode
{
  int label;
  int weight;
  GraphNode(int l, int w) : label(l), weight(w) {}
} GraphNode;

typedef struct AdjacencyList
{
  std::vector<GraphNode *> adjlist;
} AdjacencyList;

class Graph
{
 public:
  Graph() : num_of_nodes_(0),
            adjacency_lists_(std::vector<AdjacencyList *>(0)) {}

  /*
   * Init function initializes the graph used in Dijkstra's algorithm
   * @param num_of_nodes: the number of nodes that graph will contain
   */
  void Init(int num_of_nodes);

  /*
   * AddEdge function adds an edge from source index to destination index
   * @param src_idx: the index of the source node
   * @param dest_idx: the index of the destination node
   * @param weight: the weight of the edge
   */
  void AddEdge(int src_idx, int dest_idx, int weight);

  /*
   * ExtractNeighbors function extracts the neighboring nodes of a node
   * @param node_idx: the index of the considering node
   * return: the neighboring nodes in adjacency list representation
   */
  AdjacencyList *ExtractNeighbors(int node_idx);

  /*
   * GetNumberOfNodes function gets the number of nodes in the graph
   */
  int GetNumberOfNodes();

  /*
   * PrintGraph prints the labels of all the graph nodes
   */
  void PrintGraph();

  virtual ~Graph();
 private:
  int num_of_nodes_;  // number of nodes in the graph
  // adjacency lists for the graph
  std::vector<AdjacencyList *> adjacency_lists_;
};
}  // namespace dijkstra

#endif /* INCLUDES_GRAPH_H_ */

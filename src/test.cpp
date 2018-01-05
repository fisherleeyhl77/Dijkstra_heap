/*
 * test.cpp
 * Author: Huili Yu
 */

#include <iostream>
#include <climits>
#include <cstdlib>
#include <string>
#include "../include/graph.h"
#include "../include/dijkstra.h"

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "Please input the file for specifying "
                 "the graph connectivity" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string connectivity_file = argv[1];
  dijkstra::Dijkstra dj(connectivity_file);
  int startNodeIdx = 0;
  int endNodeIdx = 6;
  std::vector<int> path;
  int length_of_path =
      dj.FindShortestPath(startNodeIdx, endNodeIdx, path);
  dj.PrintPath(path);
  std::cout << "The length of path is " << length_of_path << std::endl;

  startNodeIdx = 4;
  endNodeIdx = 1;
  path.clear();
  length_of_path = dj.FindShortestPath(startNodeIdx, endNodeIdx, path);
  dj.PrintPath(path);
  std::cout << "The length of path is " << length_of_path << std::endl;

  std::cout << "End of main" << std::endl;
  return 0;
}



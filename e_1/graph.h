#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <memory>
#include <utility>

namespace MathHelpers {

class Graph {
  int nodeCount; // No. of vertices

  // In a weighted graph, we need to store vertex
  // and weight pair for every edge
  std::list<std::pair<int, int>> *adj;

public:
  Graph(); // Constructor

  // function to add an edge to graph
  void addEdge(int u, int v, int w);

  // prints shortest path from s
  void dijkstraPath(int s, void (*progressFunc)(float progress));
};

} // namespace MathHelpers

#endif // GRAPH_H

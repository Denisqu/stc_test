#include "graph.h"
#include <limits>
#include <set>
#include <vector>

using namespace MathHelpers;
using namespace std;

Graph::Graph() {
  this->nodeCount = 0;
  adj = new list<pair<int, int>>();
}

void Graph::addEdge(int u, int v, int w) {
  adj->push_back(make_pair(v, w));
  adj->push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::dijkstraPath(int src, void (*progressFunc)(float progress)) {
  // Create a set to store vertices that are being
  // processed
  set<pair<int, int>> setds;

  // Create a vector for distances and initialize all
  // distances as max value of int
  vector<int> dist(nodeCount, numeric_limits<int>::max());

  // Insert source itself in Set and initialize its
  // distance as 0.
  setds.insert(make_pair(0, src));
  dist[src] = 0;

  /* Looping till all shortest distance are finalized
     then setds will become empty    */
  while (!setds.empty()) {
    // The first vertex in Set is the minimum distance
    // vertex, extract it from set.
    pair<int, int> tmp = *(setds.begin());
    setds.erase(setds.begin());

    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted distance (distance must be first item
    // in pair)
    int u = tmp.second;

    // 'i' is used to get all adjacent vertices of a vertex
    list<pair<int, int>>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      // Get vertex label and weight of current adjacent
      // of u.
      int v = (*i).first;
      int weight = (*i).second;

      //    If there is shorter path to v through u.
      if (dist[v] > dist[u] + weight) {
        /*  If distance of v is not INF then it must be in
            our set, so removing it and inserting again
            with updated less distance.
            Note : We extract only those vertices from Set
            for which distance is finalized. So for them,
            we would never reach here.  */
        if (dist[v] != numeric_limits<int>::max())
          setds.erase(setds.find(make_pair(dist[v], v)));

        // Updating distance of v
        dist[v] = dist[u] + weight;
        setds.insert(make_pair(dist[v], v));
      }
    }
  }

  // Print shortest distances stored in dist[]
  printf("Vertex   Distance from Source\n");
  for (int i = 0; i < nodeCount; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

#pragma once
// graph structure and algorithms

#include <list>
#include <vector>
#include <fstream>

namespace GraphNS { 
typedef std::vector<std::list<int>> adj_t;
class Graph {
 private:
  adj_t::size_type vertex_count;
  adj_t adjlist;

 public:
  // ctor with size
  Graph(adj_t::size_type size);
  // ctor with ifstream
  Graph(adj_t::size_type size, std::ifstream &input);

  // EFFECTS: the total number of vertices
  adj_t::size_type size() const;

  // EFFECTS: print adjacencies for each vertex
  void print() const;

  // EFFECTS: get adjacency list
  const adj_t &get_adjacency_list() const;

  // EFFECTS: add edge to graph
  void add_edge(int u, int v);
  void get_vertex(int idx);

}; // class Graph

//////////////////////////////////////////////////////////////////////////////////
// Graph Algorithms
////////////////////////////////////////////////////////////////////////////////

// EFFECTS: explore all vertices in graph with Depth first search
void dfs(const Graph &g, int s, std::vector<bool> &explored);

// EFFECTS: create a directed graph with reversed order
Graph reverse_graph(const Graph &G);

// EFFECTS: create a directed graph with new indices
Graph update_finishing_times();
// EFFECTS: calculate finishing times using kosarjus
std::vector<int> topological_sort(const Graph &g);

// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
void dfs_sort(const Graph &g, int s, std::vector<bool> &explored_array,
              std::vector<int> &ordering, int &label); 
 
// == overload for class Graph
bool operator==(const Graph &left, const Graph &right);

} // namespace GraphNS
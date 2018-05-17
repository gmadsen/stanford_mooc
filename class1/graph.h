#pragma once
// graph structure and algorithms

#include <fstream>
#include <list>
#include <utility>
#include <vector>
#include <memory>

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

};  // class Graph

class WeightedGraph {
 private:
  struct Vertex {
    int label;
    std::vector<std::pair<int, int>> adj_edges;
    bool explored;
  };  // class Vertex
  std::vector<std::unique_ptr<Vertex>> vertices;
public:
WeightedGraph(std::ifstream &input);
size_t size() const;

void print() const;
};  // class WeightedGraph

//////////////////////////////////////////////////////////////////////////////////
// Graph Algorithms
////////////////////////////////////////////////////////////////////////////////

// EFFECTS: explore all vertices in graph with Depth first search
void dfs(const Graph &g, int s, std::vector<bool> &explored);

// EFFECTS: create a directed graph with reversed order
Graph reverse_graph(const Graph &g);

// EFFECTS: create a directed graph with new indices
Graph update_labels(const Graph &g, const std::vector<int> &order);
// EFFECTS: calculate finishing times using kosarjus
std::vector<int> topological_sort(const Graph &g);

// EFFECTS: return a vector of SCC sizes
std::vector<int> kosaraju(const Graph &g);

// EFFECTS: return a vector of shortest paths from s to all Dijkstra's
vector<int> dijkstra(WeightedGraph wg, int s);
// == overload for class Graph
bool operator==(const Graph &left, const Graph &right);

}  // namespace GraphNS
/// graph structure and algorithms

#include "graph.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

namespace GraphNS {

// helper functions
void add_edges_from_stream(ifstream &input, Graph &g);

// class Graph CTOR
Graph::Graph(adj_t::size_type size)
    : vertex_count(size), adjlist(size, list<int>()) {}

Graph::Graph(adj_t::size_type size, ifstream &input)
    : vertex_count(size), adjlist(size, list<int>()) {
  add_edges_from_stream(input, *this);
}

const adj_t &Graph::get_adjacency_list() const { return adjlist; }

adj_t::size_type Graph::size() const { return vertex_count; }

void Graph::add_edge(int u, int v) { adjlist[u].push_back(v); }

// EFFECTS: print adjacency list for each vertex
void Graph::print() const {
  for (vector<list<int>>::const_iterator i = adjlist.begin();
       i != adjlist.end(); ++i) {
    cout << "vertex " << distance(adjlist.begin(), i) << " is adjacent to: ";
    for (list<int>::const_iterator j = i->begin(); j != i->end(); ++j) {
      cout << *j << " ";
    }
    cout << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////
// Graph Algorithms
////////////////////////////////////////////////////////////////////////////////

// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
void dfs(const Graph &g, int s, vector<bool> &explored_array) {
  explored_array[s] = true;
  cout << "s is : " << s << endl;
  auto &adj_list = g.get_adjacency_list();
  for (const auto &edge : adj_list[s]) {
    if (!explored_array[edge]) {
      dfs(g, edge, explored_array);
    }
  }
}

// EFFECTS: create a directed graph with reversed order
Graph reverse_graph(const Graph &g) {
  Graph grev(g.size());
  const auto &orig_adj_list = g.get_adjacency_list();
  for (adj_t::const_iterator i = orig_adj_list.begin();
       i != orig_adj_list.end(); ++i) {
    for (list<int>::const_iterator j = i->begin(); j != i->end(); ++j) {
      grev.add_edge(*j, distance(orig_adj_list.cbegin(), i));
    }
  }
  return grev;
}

// EFFECTS: create a directed graph with new indices
Graph update_finishing_times();
// EFFECTS: calculate finishing times using kosarjus
std::vector<int> topological_sort(const Graph &g) {
  int size = g.size();
  vector<int> ordering(size, 0);
  vector<bool> explored(size, false);
  int current_label = size - 1;
  const auto &vertices = g.get_adjacency_list();
  for (auto i = vertices.cbegin(); i != vertices.cend(); ++i) {
      auto dist = distance(vertices.cbegin(), i);
      if (!explored[dist]) {
          dfs_sort(g, dist, explored, ordering, current_label);
      }
  }
  return ordering;
}


// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
void dfs_sort(const Graph &g, int s, vector<bool> &explored_array,
              vector<int> &ordering, int &label) {
  explored_array[s] = true;
  auto &adj_list = g.get_adjacency_list();
  for (const auto &edge : adj_list[s]) {
    if (!explored_array[edge]) {
      dfs_sort(g, edge, explored_array, ordering, label);
    }
  }
  ordering[s] = label;
  --label; 
}

///////////////////////////////////////////////////////
/////////////Overloads and Helpers////////////////////
//////////////////////////////////////////////////////

// EFFECTS: == override for class Graph
bool operator==(const Graph &left, const Graph &right) {
  return (left.size() == right.size() &&
          left.get_adjacency_list() == right.get_adjacency_list());
}

void add_edges_from_stream(ifstream &input, Graph &g) {
  int u;
  int v;
  while (input >> u) {
    input >> v;
    g.add_edge(u, v);
  }
}

}  // namespace GraphNS
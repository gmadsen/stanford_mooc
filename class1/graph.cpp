/// graph structure and algorithms

#include "graph.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <utility>

using namespace std;

namespace GraphNS {

//////////////////////// helper functions//////////////////
//////////////////////////////////////////////////////////
void add_edges_from_stream(ifstream &input, Graph &g);
void dfs_sort(const Graph &g, int s, std::vector<bool> &explored_array,
              std::vector<int> &ordering, int &label);
void kosaraju_dfs_loop(const Graph &g, vector<int> &ordering,
                       map<int, int> &leaders);
void kosaraju_dfs(const Graph &g, int s, vector<bool> &explored_array,
                  vector<int> &ordering, int &finish_count,
                  map<int, int> &leaders, int l);

////////////////////////////////////////////////////////////

/////////////////////classs WeightedGraph//////////////////
WeightedGraph::WeightedGraph(ifstream &input) {
  string line;
  while (getline(input, line)) {
    istringstream str_ss(line);
     vertices.push_back(make_unique<Vertex>());
    str_ss >> vertices.back()->label;
    vertices.back()->explored = false;
    int outvertex = 0;
    int weight = 0;
    while (str_ss >> outvertex) {
      str_ss.ignore(1, ',');
      str_ss >> weight;
      vertices.back()->adj_edges.emplace_back(make_pair(outvertex, weight));
    }
  }
}
size_t WeightedGraph::size() const {
  return vertices.size();
}
void WeightedGraph::print() const {
  for (const auto &i : vertices) {
    cout << "vertex " << i->label << " has weighted edges ";
    for (const auto &j : i->adj_edges) {
      cout << j.first << "," << j.second << " ";
    }
    cout << endl;
  }
}

//////////////////////////////////////////////////////////

/////////////// class Graph //////////////////////////
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
  cout << endl;
}
//////////////////// class Graph

//////////////////////////////////////////////////////////////////////////////////
// Graph Algorithms
////////////////////////////////////////////////////////////////////////////////

// EFFECTS: explore all vertices in graph with Depth first search
// MODIFIES: explored array
// REQUIRES: assumes initial call has an explored array of all false
void dfs(const Graph &g, int s, vector<bool> &explored_array) {
  explored_array[s] = true;
  // cout << "s is : " << s << endl;
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
Graph update_labels(const Graph &g, const vector<int> &new_order) {
  Graph g_update(g.size());
  const auto &orig_adj_list = g.get_adjacency_list();
  for (adj_t::const_iterator i = orig_adj_list.begin();
       i != orig_adj_list.end(); ++i) {
    auto dist = distance(orig_adj_list.cbegin(), i);
    for (list<int>::const_iterator j = i->begin(); j != i->end(); ++j) {
      g_update.add_edge(new_order[dist], new_order[*j]);
    }
  }
  return g_update;
}

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

vector<int> kosaraju(const Graph &g) {
  int size = g.size();
  vector<int> ordering(size, 0);
  map<int, int> leaders;

  kosaraju_dfs_loop(reverse_graph(g), ordering, leaders);
  leaders.clear();
  kosaraju_dfs_loop(update_labels(g, ordering), ordering, leaders);

  vector<int> scc_sizes;
  scc_sizes.reserve(leaders.size());
  for (auto i : leaders) {
    scc_sizes.push_back(i.second);
  }
  sort(scc_sizes.begin(), scc_sizes.end(), greater<int>());
  int split_size = scc_sizes.size();
  vector<int> five_scc(scc_sizes.begin(),
                       scc_sizes.begin() + (split_size < 5 ? split_size : 5));
  return five_scc;
}

// EFFECTS: calculate finishing times using kosarjus
void kosaraju_dfs_loop(const Graph &g, vector<int> &ordering,
                       map<int, int> &leaders) {
  vector<bool> explored(g.size(), false);

  int t = -1;
  // global leader
  int s = 0;
  const auto &vertices = g.get_adjacency_list();
  for (auto i = vertices.crbegin(); i != vertices.crend(); ++i) {
    auto dist = distance(vertices.cbegin(), i.base()) - 1;
    if (!explored[dist]) {
      s = dist;
      kosaraju_dfs(g, dist, explored, ordering, t, leaders, s);
    }
  }
}

// REQUIRES: assumes initial call has an explored array of all false
void kosaraju_dfs(const Graph &g, int s, vector<bool> &explored_array,
                  vector<int> &ordering, int &finish_count,
                  map<int, int> &leaders, int l) {
  explored_array[s] = true;
  leaders[l] += 1;
  auto &adj_list = g.get_adjacency_list();
  for (const auto &edge : adj_list[s]) {
    if (!explored_array[edge]) {
      kosaraju_dfs(g, edge, explored_array, ordering, finish_count, leaders, l);
    }
  }
  ++finish_count;
  ordering[s] = finish_count;
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
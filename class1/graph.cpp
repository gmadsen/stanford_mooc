/// graph structure and algorithms

#include "graph.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

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
////////////////////////////////////////////////////////////

WeightedGraph::WeightedGraph(ifstream &input) {
  string line;
  while (getline(input, line)) {
    istringstream str_ss(line);
    vertices.push_back(make_unique<Vertex>());
    str_ss >> vertices.back()->label;
    --vertices.back()->label;
    vertices.back()->explored = false;
    int outvertex = 0;
    int weight = 0;
    while (str_ss >> outvertex) {
      str_ss.ignore(1, ',');
      str_ss >> weight;
      --outvertex;
      vertices.back()->adj_edges.emplace_back(make_pair(outvertex, weight));
    }
  }
}
size_t WeightedGraph::size() const { return vertices.size(); }

void WeightedGraph::print() const {
  for (const auto &i : vertices) {
    cout << "vertex " << i->label << " has weighted edges ";
    for (const auto &j : i->adj_edges) {
      cout << j.first << "," << j.second << " ";
    }
    cout << endl;
  }
}

const vector<unique_ptr<WeightedGraph::Vertex>> &WeightedGraph::get_vertices()
    const {
  return vertices;
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
/////////////////////////////////////////////////////////////////////////
////////////////////  End of class Graph//////////////////////////////////////
/////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
//////////// class VertexHeap /////////////////////////////////
////////////////////////////////////////////////////////////////
bool vert_compare(pair<int, int> a, pair<int, int> b) {
  return (a.second > b.second);
}

pair<int, int> VertexHeap::top() const { return heap[0]; }

void VertexHeap::print() const {
  for (auto i : heap) {
    cout << "vertex " << i.first << " greedy score " << i.second << endl;
  }
}
void VertexHeap::push(pair<int, int> v) {
  heap.push_back(v);
  push_heap(heap.begin(), heap.end(), vert_compare);
}
void VertexHeap::pop() {
  pop_heap(heap.begin(), heap.end(), vert_compare);
  heap.pop_back();
}
void VertexHeap::remove(int vertex_value) {
  auto it =
      find_if(heap.begin(), heap.end(), [&vertex_value](const auto &vertex) {
        return vertex.first == vertex_value;
      });
  if (it != heap.end()) {
    *it = heap.back();
    heap.pop_back();
    make_heap(heap.begin(), heap.end(), vert_compare);
  }
}
int VertexHeap::value_at(int vertex_value) const {
  auto it =
      find_if(heap.begin(), heap.end(), [&vertex_value](const auto &vertex) {
        return vertex.first == vertex_value;
      });
  if (it != heap.end()) {
    return it->second;
  }
  return -1;
}
size_t VertexHeap::size() const { return heap.size(); }
/////////////////////////////////////////////////////////////
/////////////// class VertexHeap////////////////////////////
///////////////////////////////////////////////////////////

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

vector<int> dijkstra(WeightedGraph &wg, int s) {
  /////// initialize
  VertexHeap heap;
  int size = wg.size();
  const auto &pvertices = wg.get_vertices();

  // set all distances to inf
  vector<int> distance(size, numeric_limits<int>::max());
  // fill untouched with all vertices
  // make heap
  for (const auto &i : pvertices) {
    heap.push(make_pair(i->label, numeric_limits<int>::max()));
  }
  // add s to touched
  distance[s] = 0;
  pvertices[s]->explored = true;
  heap.remove(s);
  for (const auto &i : pvertices[s]->adj_edges) {
    heap.remove(i.first);
    int greedy_score = distance[s] + i.second;
    heap.push(make_pair(i.first, greedy_score));
  }

  while (heap.size() > 0) {
    pair<int, int> p(heap.top());
    distance[p.first] = p.second;
    heap.remove(p.first);
    pvertices[p.first]->explored = true;
    for (const auto &i : pvertices[p.first]->adj_edges) {
      if (pvertices[i.first]->explored == false) {
        int greedy_score = distance[p.first] + i.second;
        int current_value = heap.value_at(i.first);
        if (current_value > greedy_score) {
          heap.remove(i.first);
          heap.push(make_pair(i.first, greedy_score));
        }
      }
    }
  }

  return distance;
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
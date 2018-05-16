#include "unit_test_framework.h"

#include "graph.h"
#include <fstream>
#include <list>
#include <vector>


using namespace std;
using namespace GraphNS;

// test add_edges
TEST(test_add_edges) {
  Graph g(5);

  g.add_edge(0,1);
  g.add_edge(0,2);
  g.add_edge(1,4);
  g.add_edge(4,1);

  adj_t expected(5,list<int> ());
  expected[0].push_back(1);
  expected[0].push_back(2);
  expected[1].push_back(4);
  expected[4].push_back(1);
  ASSERT_EQUAL(g.get_adjacency_list(), expected);
}

// test add_edges from stream ctor
TEST(test_fstream_ctor) {
  ifstream input("small_graph.txt");
  Graph g(5, input);

  adj_t expected(5,list<int> ());
  expected[0].push_back(1);
  expected[0].push_back(2);
  expected[1].push_back(4);
  expected[4].push_back(1);
  ASSERT_EQUAL(g.get_adjacency_list(), expected);
}

// test DFS for complete exploration
TEST(test_dfs_small_graph) {
  ifstream input("small_graph.txt");
  Graph g(5, input);
  vector<bool> explored_array(5, false);
  vector<bool> expected(5, true);
  expected[3] = false;
  dfs(g, 0, explored_array);
  ASSERT_EQUAL(explored_array, expected);
}

// test reverse_graph_small
TEST(test_reverse_graph_small) {
  ifstream input("small_graph.txt");
  Graph g(5, input);
  Graph grev = reverse_graph(g);
 

  adj_t expected(5,list<int> ());
  expected[1].push_back(0);
  expected[1].push_back(4);
  expected[2].push_back(0);
  expected[4].push_back(1);
  ASSERT_EQUAL(grev.get_adjacency_list(), expected);
}

// test topological ordering
TEST(test_topological_ordering) {
  Graph g(5);
  g.add_edge(1,0);
  g.add_edge(1,4);
  g.add_edge(2,0);
  g.add_edge(2,3);
  g.add_edge(4,2);

  vector<int> expected(5,0);
  expected[0] = 4;
  expected[1] = 0;
  expected[2] = 2;
  expected[3] = 3;
  expected[4] = 1;

  vector<int> actual = topological_sort(g);
  for (auto i : actual) {
    cout << i << " ";
  }
  cout << endl;

  ASSERT_EQUAL(actual, expected);
}

TEST_MAIN()

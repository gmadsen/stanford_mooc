// Main
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "mult_algorithm.h"
#include "graph.h"
#include <fstream>

using namespace std;
using GraphNS::Graph;
using GraphNS::kosaraju;
using GraphNS::adj_t;

int main(int argc, char **argv) {
  // open file
  ifstream file("large_graph.txt");

 //////////////// // start timer for filling
  chrono::time_point<chrono::system_clock> start_fill, end_fill, start_count,
      end_count;
  start_fill = chrono::system_clock::now();

  // open data file and create graph
  Graph g(8757144, file);
  //Graph g(11, file);

  ////////////////////// end fill timer//////////////////////
  end_fill = chrono::system_clock::now();
  chrono::duration<double> fill_seconds = end_fill - start_fill;
  cout << "filling took: " << fill_seconds.count() << "s" << endl;
  /////////////////////////////////////////////////////

  /////////////////// start timer for algorithm///////////////
  start_count = chrono::system_clock::now();

  // DO main algorithm
  vector<int> leader_sizes = kosaraju(g);

  ////////////////////// end timer///////////////////////////
  end_count = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_count - start_count;
  std::cout << "\n computation took " << elapsed_seconds.count() << "s" << endl;
  cout << "leader sizes are " ;
  for (auto i : leader_sizes) {
    cout << i << " ";

  }
  cout << endl;
  return 0;
}
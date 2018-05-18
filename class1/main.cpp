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
using GraphNS::WeightedGraph;
using GraphNS::dijkstra;

int main(int argc, char **argv) {
  // open file
  ifstream file("dijkstraData.txt");

 //////////////// // start timer for filling
  chrono::time_point<chrono::system_clock> start_fill, end_fill, start_count,
      end_count;
  start_fill = chrono::system_clock::now();

  // open data file and create graph
  WeightedGraph wg(file); 

  ////////////////////// end fill timer//////////////////////
  end_fill = chrono::system_clock::now();
  chrono::duration<double> fill_seconds = end_fill - start_fill;
  cout << "filling took: " << fill_seconds.count() << "s" << endl;
  /////////////////////////////////////////////////////

  /////////////////// start timer for algorithm///////////////
  start_count = chrono::system_clock::now();

  // DO main algorithm
auto a = dijkstra(wg,0);
  ////////////////////// end timer///////////////////////////
  end_count = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_count - start_count;
  std::cout << "\n computation took " << elapsed_seconds.count() << "s" << endl;
  vector<int> answer {a[6], a[36], a[58], a[81], a[98], a[114], a[132], a[164], a[187], a[196]};
  cout << "answer is: " << endl;
  for (auto i : answer) {
    cout << i << ",";
  }
  cout << endl;
  return 0;
}
// Main
#include <string>
#include <iostream>
#include "mult_algorithm.h"
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {

typedef list<pair<int, list<int>>> graph_t;

  chrono::time_point<chrono::system_clock> start_fill, end_fill, start_count, end_count;
  //open file

  // start timer for filling
  start_fill = chrono::system_clock::now();
  string line;
  graph_t graph;
  while (getline(cin,line)) {
    stringstream cur_line(line);
    int vertex;
    cur_line >> vertex;
    int single_adjacency;
    list<int> line_adjacencies;
    while (cur_line >> single_adjacency) {
      line_adjacencies.push_back(single_adjacency);
    }
    graph.push_back(make_pair(vertex,line_adjacencies));

    //graph.push_back(current_number);
    cout << "current vertex is: " << graph.back().first << endl;
    cout << "corresponding adjacencies are: ";
    for (auto i : graph.back().second) {
     cout << i << " "; 
    }
    cout << endl;
  }
  //end fill timer
  end_fill = chrono::system_clock::now();
  chrono::duration<double> fill_seconds = end_fill - start_fill;

  cout << "filling took: " << fill_seconds.count() << "s" << endl;
  //start timer
  start_count = chrono::system_clock::now();
  long long count = 0;
  int n = graph.size();
  int iterations = n * ceil(log(n));
  int value = iterations;
  cout << "will run " << iterations << " of randomized cut" << endl;
  for (int i = 0; i < iterations; ++i) {
    cout << "On iteration " << i << endl;
    int single_value = min_cut_contraction(graph);
    cout << "This iterations min cut was " << single_value << endl;
    if (single_value < value) value = single_value; 
  } 
  cout << "value is : " << value << endl;

  //end timer
  end_count = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_count - start_count;
  std::cout << "minimum cut count is: " << count <<  endl; 
  std::cout << "\n computation took " << elapsed_seconds.count() << "s" << endl;
  return 0;
}
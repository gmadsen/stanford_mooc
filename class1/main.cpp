// Main
#include <string>
#include <iostream>
#include "mult_algorithm.h"
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv) {


  //open file

  // start timer for filling
  chrono::time_point<chrono::system_clock> start_fill, end_fill, start_count, end_count;
  start_fill = chrono::system_clock::now();

  // open data file and create graph
  

  //end fill timer
  end_fill = chrono::system_clock::now();
  chrono::duration<double> fill_seconds = end_fill - start_fill;
  cout << "filling took: " << fill_seconds.count() << "s" << endl;


  //start timer for algorithm
  start_count = chrono::system_clock::now();

  //end timer
  end_count = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_count - start_count;
  std::cout << "\n computation took " << elapsed_seconds.count() << "s" << endl;
  return 0;
}
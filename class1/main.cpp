// Main
#include <string>
#include <iostream>
#include "mult_algorithm.h"
#include <chrono>
#include <fstream>
using namespace std;

int main(int argc, char **argv) {

  chrono::time_point<chrono::system_clock> start_fill, end_fill, start_count, end_count;
  vector<int> input;
  int current_number = 0;
  //open file

  // start timer for filling
  start_fill = chrono::system_clock::now();
  while (cin >> current_number) {
    input.push_back(current_number);
  }
  //end fill timer
  end_fill = chrono::system_clock::now();
  chrono::duration<double> fill_seconds = end_fill - start_fill;

  cout << "filling took: " << fill_seconds.count() << "s" << endl;
  //start timer
  start_count = chrono::system_clock::now();
  long long count = 0;
  std::cout << "hi from above" << endl;
  inversion_count(input, count);
  
  //end timer
  end_count = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end_count - start_count;
  std::cout << "inversion count is: " << count <<  endl; 
  std::cout << "\n computation took " << elapsed_seconds.count() << "s" << endl;
  return 0;
}
// Main
#include <string>
#include <iostream>
#include "mult_algorithm.h"
using namespace std;
int main(int argc, char **argv) {
  string num1(argv[1]);
  string num2(argv[2]);
   auto ans = karatsuba(num1, num2);
  cout << ans << " is the answer beez" << endl;
  return 0;
}
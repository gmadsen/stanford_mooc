#include "mult_algorithm.h"
#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// main.exe num1 num2

// continuous cstring of numbers to vector
vector<int> cstring_num_to_vector(const char *p) {
  vector<int> num_vect;
  for (const char *i = p; i < p + strlen(p); ++i) {
    int number = *i - '0';
    num_vect.push_back(number);
  }
  return num_vect;
}
// function for finding the differnce of larger numbers
string find_diff(string str1, string str2) {
  if (str1 == "") {
    str1 = "0";
  }
  if (str2 == "") {
    str2 = "0";
  }
  string str = "";
  string::reverse_iterator left = str1.rbegin();
  string::reverse_iterator right = str2.rbegin();

  while (right != str2.rend()) {
    int left_num = int(*left - '0');
    int right_num = int(*right - '0');
    if (left_num < right_num) {
      auto temp = left + 1;
      while (*temp == '0') {
        *temp = '9';
        ++temp;
      }
      *temp = char((*temp - '0') - 1) + '0';
      left_num += 10;
    }
    auto value = left_num - right_num;
    str.push_back(char(value) + '0');
    ++left;
    ++right;
  }
  while (left != str1.rend()) {
    str.push_back(*left);
    ++left;
  }
  // remove trailing zeros
  while (str.back() == '0') {
    str.pop_back();
  }
  // reverse order of string to correct form
  reverse(str.begin(), str.end());
  return str;
}
// Function for finding sum of larger numbers
string find_sum(string str1, string str2) {
  // Before proceeding further, make sure length
  // of str2 is larger.
  if (str1.length() > str2.length()) swap(str1, str2);

  // Take an empty string for storing result
  string str = "";

  // Calculate lenght of both string
  int n1 = str1.length(), n2 = str2.length();
  int diff = n2 - n1;

  // Initialy take carry zero
  int carry = 0;

  // Traverse from end of both strings
  for (int i = n1 - 1; i >= 0; i--) {
    // Do school mathematics, compute sum of
    // current digits and carry
    int sum = ((str1[i] - '0') + (str2[i + diff] - '0') + carry);
    str.push_back(sum % 10 + '0');
    carry = sum / 10;
  }

  // Add remaining digits of str2[]
  for (int i = n2 - n1 - 1; i >= 0; i--) {
    int sum = ((str2[i] - '0') + carry);
    str.push_back(sum % 10 + '0');
    carry = sum / 10;
  }

  // Add remaining carry
  if (carry) str.push_back(carry + '0');

  // reverse resultant string
  reverse(str.begin(), str.end());

  return str;
}

// integer exponentiation
unsigned long long ipow(unsigned long long base, unsigned long long exp) {
  unsigned long long result = 1;
  for (;;) {
    if (exp & 1) result *= base;
    exp >>= 1;
    if (!exp) break;
    base *= base;
  }

  return result;
}

// pad zeros on right of string
string pad_zero(string num, int zeroc) {
  for (int i = 0; i < zeroc; ++i) {
    num.push_back('0');
  }
  return num;
}
// karatsuba algorithm
string karatsuba(string num1, string num2) {
  // assume size is same
  // base case
  auto min_length = min(num1.size(), num2.size());
  assert(min_length != 0);
  if (min_length <= 2) {
    int sum = stoi(num1) * stoi(num2);
    return to_string(sum);
  }
  // recursive case
  int m = min_length / 2;
  int index_1 = num1.size() - m;
  int index_2 = num2.size() - m;
  string num1_l = num1.substr(0, index_1);
  string num1_r = num1.substr(index_1);
  string num2_l = num2.substr(0, index_2);
  string num2_r = num2.substr(index_2);
  string z2 = karatsuba(num1_l, num2_l);
  string z0 = karatsuba(num1_r, num2_r);
  string z1_l = find_sum(num1_l, num1_r);
  string z1_r = find_sum(num2_l, num2_r);
  string z1 = find_diff(find_diff(karatsuba(z1_l, z1_r), z2), z0);
  // auto result = z2 * ipow(10, m * 2) + z1 * ipow(10, m) + z0;
  return find_sum(find_sum(pad_zero(z2, m * 2), pad_zero(z1, m)), z0);
}

//EFFECTS: merge two sorted vectors
vector<int> merge(const vector<int> &left, const vector<int> &right) {
  vector<int> merged_vector;

  // start iterators for both inputs
  auto left_iter = left.begin();
  auto right_iter = right.begin();

  while (left_iter != left.end() && right_iter != right.end()) {
    if (*left_iter < *right_iter) {
      merged_vector.push_back(*left_iter);
      ++left_iter;
    } else {
      merged_vector.push_back(*right_iter);
      ++right_iter;
    }
  }
  while (left_iter != left.end()) {
    merged_vector.push_back(*left_iter);
    ++left_iter;
  }
  while (right_iter != right.end()) {
    merged_vector.push_back(*right_iter);
    ++right_iter;
  }
  return merged_vector;
}

// sort an unsorted vector with merge sort algorithm
vector<int> merge_sort(const vector<int> &input) {
  if (input.size() <= 1) {
    return input;
  }
  int half = input.size()/2;
  vector<int>::const_iterator middle = input.begin() + half;
  vector<int> left = merge_sort(vector<int> (input.begin(), middle));
  vector<int> right = merge_sort(vector<int> (middle, input.end()));
  return merge(left, right);
}


//EFFECTS: count inversions using merge 
vector<int> inversion_merge(const vector<int> &left, const vector<int> &right, long long &count) {
  vector<int> merged_vector;

  // start iterators for both inputs
  auto left_iter = left.begin();
  auto right_iter = right.begin();

  while (left_iter != left.end() && right_iter != right.end()) {
    if (*left_iter < *right_iter) {
      merged_vector.push_back(*left_iter);
      ++left_iter;
    } else {
      merged_vector.push_back(*right_iter);
      ++right_iter;
      count += left.end() - left_iter;
    }
  }
  while (left_iter != left.end()) {
    merged_vector.push_back(*left_iter);
    ++left_iter;
  }
  while (right_iter != right.end()) {
    merged_vector.push_back(*right_iter);
    ++right_iter;
  }
  return merged_vector;
}

// count the number of inversions in a vector using merge sort
vector<int> inversion_count(const vector<int> &input, long long &count) {
  if (input.size() <= 1) {
    return input;
  }
  int half = input.size()/2;
  vector<int>::const_iterator middle = input.begin() + half;
  vector<int> left = inversion_count(vector<int> (input.begin(), middle), count);
  vector<int> right = inversion_count(vector<int> (middle, input.end()), count);
  return inversion_merge(left, right, count);
}
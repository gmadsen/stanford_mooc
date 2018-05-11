#include "mult_algorithm.h"
#include <stdint.h>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

// main.exe num1 num2

typedef list<pair<int, list<int>>> graph_t;

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

// EFFECTS: merge two sorted vectors
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
  int half = input.size() / 2;
  vector<int>::const_iterator middle = input.begin() + half;
  vector<int> left = merge_sort(vector<int>(input.begin(), middle));
  vector<int> right = merge_sort(vector<int>(middle, input.end()));
  return merge(left, right);
}

// EFFECTS: count inversions using merge
vector<int> inversion_merge(const vector<int> &left, const vector<int> &right,
                            long long &count) {
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
  int half = input.size() / 2;
  vector<int>::const_iterator middle = input.begin() + half;
  vector<int> left = inversion_count(vector<int>(input.begin(), middle), count);
  vector<int> right = inversion_count(vector<int>(middle, input.end()), count);
  return inversion_merge(left, right, count);
}

// Effects: inplace partition a vector with a chosen partition element
vector<int>::iterator vector_partition(vector<int>::iterator begin,
                                       vector<int>::iterator end,
                                       vector<int>::iterator pivot) {
  if (begin != pivot) {
    std::swap(*begin, *pivot);
  }
  vector<int>::iterator i = begin;
  vector<int>::iterator j = begin + 1;

  while (j != end) {
    if (*j < *begin) {
      std::swap(*j, *(i + 1));
      ++i;
    }
    ++j;
  }
  std::swap(*begin, *i);
  return i;
}

// Effects: find median of medians of a vector
vector<int>::iterator med_of_med(vector<int>::iterator begin,
                                 vector<int>::iterator end) {
  int size = end - begin;
  vector<int>::iterator mid = end;
  vector<int>::iterator last = end - 1;
  if (size % 2 == 0) {
    mid = begin + size / 2 - 1;
  } else {
    mid = begin + (size - 1) / 2;
  }

  vector<vector<int>::iterator> drie{begin, mid, last};
  std::sort(
      drie.begin(), drie.end(),
      [](vector<int>::iterator a, vector<int>::iterator b) { return *a < *b; });
  return drie[1];
}

// Effects: sort a vector inplace with QuickSort algorithm
void quicksort(vector<int>::iterator begin, vector<int>::iterator end,
               long long int &comp_count) {
  int size = end - begin;
  // base case
  if (size == 1 || size == 0) return;

  comp_count += size - 1;
  auto p = med_of_med(begin, end);
  vector<int>::iterator pivot = vector_partition(begin, end, p);
  // left
  // cout << "pivot is: " << *pivot << endl;
  quicksort(begin, pivot, comp_count);
  // right
  quicksort(pivot + 1, end, comp_count);
}

// EFFECTS: perform a single random cut and update graph
// MODIFIES: input graph
void single_random_cut(graph_t &graph) {
  // new element
  int n = graph.back().first;

  // choose edge  by choosing an adjacency randomly
  // srand(time(NULL));
  // find appropriate iterators pointing to head
  int head_idx = rand() % graph.size();
  graph_t::iterator head_iter = graph.begin();
  advance(head_iter, head_idx);
  int head_val = head_iter->first;

  // find iterator for tail side
  int tail_idx = rand() % head_iter->second.size();
  auto tail_iter = head_iter->second.begin();
  advance(tail_iter, tail_idx);
  int tail_val = *tail_iter;

  // cout << "head value is: " << head_val << endl;
  // cout << "tail value is: " << tail_val << endl;

  list<int> new_edges;

  // find head vertices corresponding to edge choice
  auto it = std::find_if(graph.begin(), graph.end(),
                         [&](const std::pair<int, list<int>> &element) {
                           return element.first == tail_val;
                         });
  const auto &head_verts = head_iter->second;
  const auto &tail_verts = it->second;

  // add all non tail/head edges to new list
  for (const auto &i : head_verts) {
    if (i != head_val && i != tail_val) {
      new_edges.push_back(i);
    }
  }
  for (const auto &i : tail_verts) {
    if (i != tail_val && i != head_val) {
      new_edges.push_back(i);
    }
  }

  // remove tail and head vertices from list
  graph.erase(it);
  graph.erase(head_iter);

  // update all other vertices
  graph.push_back(make_pair(n + 1, new_edges));
  for (auto &i : graph) {
    auto &ad_list = i.second;
    replace_if(
        ad_list.begin(), ad_list.end(),
        [&](int element) { return element == head_val || element == tail_val; },
        n + 1);
  }
}
void graph_print(const graph_t &graph) {
  // print
  for (auto i : graph) {
    cout << "vertex " << i.first << " has edges: ";
    for (auto j : i.second) {
      cout << j << " ";
    }
    cout << endl;
  }
}

// find minimum cut based on repeated randomized contraction algorithm
int min_cut_contraction(list<pair<int, list<int>>> graph) {
  while (graph.size() > 2) {
    single_random_cut(graph);
    //graph_print(graph);
  }
  int min_cut = graph.front().second.size();
  // cout << "min cut is: " << min_cut << endl;
  return min_cut;
}

#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <list>

// main.exe num1 num2

// continuous cstd::string of numbers to vector
std::vector<int> cstring_num_to_vector(const char *p);

// function for finding the differnce of larger numbers
std::string find_diff(std::string str1, std::string str2);

// Function for finding sum of larger numbers
std::string find_sum(std::string str1, std::string str2);

// integer exponentiation
unsigned long long ipow(unsigned long long base, unsigned long long exp);

// pad zeros on right of std::string
std::string pad_zero(std::string num, int zeroc);

// karatsuba algorithm
std::string karatsuba(std::string num1, std::string num2);

// continuous cstd::string of numbers to vector
std::vector<int> merge_sort(const std::vector<int> &unsorted_input);

// merge two sorted vectors
std::vector<int> merge(const std::vector<int> &left,
                       const std::vector<int> &right);

// sort an unsorted vector using merge_sort algorithm
std::vector<int> merge_sort(const std::vector<int> &input);

// EFFECTS: count inversions using merge
std::vector<int> inversion_merge(const std::vector<int> &left,
                                 const std::vector<int> &right,
                                 long long &count);

// count the number of inversions in a vector using merge sort
std::vector<int> inversion_count(const std::vector<int> &input,
                                 long long &count);

// Effects: inplace partition a vector with a chosen partition element
std::vector<int>::iterator vector_partition (
    std::vector<int>::iterator begin, std::vector<int>::iterator end,
    std::vector<int>::iterator pivot);

// Effects: sort a vector inplace with QuickSort algorithm
void quicksort(std::vector<int>::iterator begin, std::vector<int>::iterator end, long long int &comp_count);

// EFFECTS: calc min cut by random contraction algorithm

int min_cut_contraction (std::list<std::pair<int,std::list<int>>> graph); 
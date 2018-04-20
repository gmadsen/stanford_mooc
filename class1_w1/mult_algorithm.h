#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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
std::string karatsuba(const std::string &num1, const std::string &num2); 

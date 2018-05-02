#include "unit_test_framework.h"

#include "mult_algorithm.h"

using namespace std;

//test addition basic
TEST(test_addition) {
string num1 = "1"; 
string num2 = "2";
string ans = find_sum(num1,num2);
ASSERT_EQUAL(ans, "3")
}

//test addition long 
TEST(test_addition_long) {
string num1 = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"; 
string num2 = "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
string ans = find_sum(num1,num2);
ASSERT_EQUAL(ans, "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110")
}

TEST(test_diff_basic) {
    string num1 = "87";
   ASSERT_EQUAL(find_diff(num1, "7"), "80"); 
   ASSERT_EQUAL(find_diff(num1, "80"), "7");
   ASSERT_EQUAL(find_diff(num1, "6"), "81")
}

TEST(test_diff_long) {
    string num1 = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    string num2 = "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999991";
    ASSERT_EQUAL(find_diff(num1,num2), "9");
}

TEST(test_karatsuba_small) {
    ASSERT_EQUAL(karatsuba("12", "13"), "156")
    ASSERT_EQUAL(karatsuba("123", "123"), "15129")
}

TEST(test_merge_small) {
    vector<int> left {1,5,7,8,9}; 
    vector<int> right {2,3,4,11,40}; 
    vector<int> expected {1, 2, 3, 4, 5, 7, 8, 9, 11, 40};
    ASSERT_EQUAL(expected, merge(left,right));
}

TEST(test_merge_sort_small) {
    vector<int> input {1,3,2,5,7,4,6,8,9};
    vector<int> expected {1,2,3,4,5,6,7,8,9};
    ASSERT_EQUAL(expected, merge_sort(input));
}

TEST(test_inversion_count_small) {
    vector<int> unsorted {1,2,3,5,6,7,4,8,9};
    int expected = 3;
    int actual = 0;
    inversion_count(unsorted, actual);
    ASSERT_EQUAL(expected, actual); 
}

TEST_MAIN()
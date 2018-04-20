#include "../unit_test_framework.h"

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
}
TEST_MAIN()
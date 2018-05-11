#include "unit_test_framework.h"

#include "mult_algorithm.h"

using namespace std;

// test addition basic
TEST(test_addition) {
  string num1 = "1";
  string num2 = "2";
  string ans = find_sum(num1, num2);
  ASSERT_EQUAL(ans, "3")
}

// test addition long
TEST(test_addition_long) {
  string num1 =
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1111111111111111111111111111111111111111";
  string num2 =
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "9999999999999999999999999999999999999999";
  string ans = find_sum(num1, num2);
  ASSERT_EQUAL(ans,
               "111111111111111111111111111111111111111111111111111111111111111"
               "11111111111111111111111111111111111111111111111110")
}

TEST(test_diff_basic) {
  string num1 = "87";
  ASSERT_EQUAL(find_diff(num1, "7"), "80");
  ASSERT_EQUAL(find_diff(num1, "80"), "7");
  ASSERT_EQUAL(find_diff(num1, "6"), "81")
}

TEST(test_diff_long) {
  string num1 =
      "100000000000000000000000000000000000000000000000000000000000000000000000"
      "0000000000000000000000000000000";
  string num2 =
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999991";
  ASSERT_EQUAL(find_diff(num1, num2), "9");
}

TEST(test_karatsuba_small){ASSERT_EQUAL(karatsuba("12", "13"), "156")
                               ASSERT_EQUAL(karatsuba("123", "123"), "15129")}

TEST(test_merge_small) {
  vector<int> left{1, 5, 7, 8, 9};
  vector<int> right{2, 3, 4, 11, 40};
  vector<int> expected{1, 2, 3, 4, 5, 7, 8, 9, 11, 40};
  ASSERT_EQUAL(expected, merge(left, right));
}

TEST(test_merge_sort_small) {
  vector<int> input{1, 3, 2, 5, 7, 4, 6, 8, 9};
  vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
  ASSERT_EQUAL(expected, merge_sort(input));
}

TEST(test_inversion_count_small) {
  vector<int> unsorted{1, 2, 3, 5, 6, 7, 4, 8, 9};
  int expected = 3;
  long long int actual = 0;
  inversion_count(unsorted, actual);
  ASSERT_EQUAL(expected, actual);
}

TEST(test_vector_partition_small) {
  vector<int> unsorted{9, 8, 7, 6, 5, 4, 3, 2, 1};
  vector<int> expected{1, 5, 4, 3, 2, 6, 9, 8, 7};
  vector_partition(unsorted.begin(), unsorted.end(), unsorted.begin() + 3);
  ASSERT_EQUAL(unsorted, expected);
}

TEST(test_vector_quicksort_small) {
  vector<int> unsorted{4, 3, 2, 1};
  vector<int> expected{1, 2, 3, 4};
  long long int count = 0;
  quicksort(unsorted.begin(), unsorted.end(), count);
  // cout << "count is: " << count << endl;
  // cout << "sorted vector is: ";
  // for (unsigned i = 0; i < unsorted.size(); ++i) {
  //      cout << unsorted[i] << " ";
  // }
  ASSERT_EQUAL(unsorted, expected);
}

TEST(test_quicksort_mid) {
  vector<int> unsorted{20, 12, 13, 11, 14, 18, 19, 17, 16, 15};
  vector<int> expected{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  long long count = 0;
  quicksort(unsorted.begin(), unsorted.end(), count);
  // cout << "sorted vector is: ";
  // for (unsigned i = 0; i < unsorted.size(); ++i) {
  //     cout << unsorted[i] << " ";
  // }
  ASSERT_EQUAL(unsorted, expected);
}

TEST(test_min_cut_contraction) {
  list<pair<int, list<int>>> graph;
  graph.push_back(make_pair(1, list<int>{2, 3}));
  graph.push_back(make_pair(2, list<int>{1, 3}));
  graph.push_back(make_pair(3, list<int>{1, 2}));
  int value = min_cut_contraction(graph);
  cout << "value is : " << value << endl;
}
TEST(test_min_cut_contraction_diamond) {
  list<pair<int, list<int>>> graph;
  graph.push_back(make_pair(1, list<int>{2, 3, 4}));
  graph.push_back(make_pair(2, list<int>{1, 4}));
  graph.push_back(make_pair(3, list<int>{1, 4}));
  graph.push_back(make_pair(4, list<int>{1, 2, 3}));
  int n = graph.size();
  int iterations = n * n * ceil(log(n));
  int value = iterations;
  for (int i = 0; i < iterations; ++i) {
    int single_value = min_cut_contraction(graph);
    if (single_value < value) value = single_value;
  }
  cout << "value is : " << value << endl;
}

TEST_MAIN()
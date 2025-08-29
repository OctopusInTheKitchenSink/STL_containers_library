#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "../Sorted_Container/Set_Conteiner/s21_multiset.h"

TEST(multiset, empty_const) {
  s21::multiset<double> a;
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, init_list_constr1) {
  s21::multiset<double> a({});
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, init_list_constr2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 5);
};

TEST(multiset, init_copy_constr1) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b(a);
  double mass[] = {-3, -1.3, 3.2, 10.2, 10.2};
  int j = 0;
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, init_copy_constr2) {
  s21::multiset<double> a;
  s21::multiset<double> b(a);
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, move_copy1) {
  s21::multiset<double> a;
  s21::multiset<double> b(std::move(a));
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, move_copy2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b(std::move(a));
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.empty(), false);
  EXPECT_EQ(b.size(), 5);
};

TEST(multiset, init_move1) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  s21::multiset<double> b;
  b = std::move(a);
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.empty(), false);
  EXPECT_EQ(b.size(), 5);
};

TEST(multiset, init_move2) {
  s21::multiset<double> a;
  s21::multiset<double> b;
  b = std::move(a);
  EXPECT_EQ(a.empty(), b.empty());
  EXPECT_EQ(a.size(), b.size());
};

TEST(multiset, self_init1) {
  s21::multiset<double> a;
  a = std::move(a);
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, self_init2) {
  s21::multiset<double> a({-1.3, -3., 3.2, 10.2, 10.2});
  a = std::move(a);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 5);
};

TEST(multiset, begin_end) {
  s21::multiset<double> a;
  EXPECT_EQ(a.end(), a.begin());
};

TEST(multiset, check_elements) {
  s21::multiset<double> a({1.1, 2.2, 3.3, -4.4, 4.4, 4.4, 5.5});
  double mass[] = {-4.4, 1.1, 2.2, 3.3, 4.4, 4.4, 5.5};
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, check_reverse) {
  s21::multiset<double> a({1.1, 2.2, 3.3, -4.4, 4.4, 4.4, 5.5});
  double mass[] = {5.5, 4.4, 4.4, 3.3, 2.2, 1.1, -4.4};
  int j = 0;
  for (auto i = a.end_elem(); i != a.end(); --i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, max_size_empty_multiset) {
  s21::multiset<double> a;
  s21::multiset<double> b;
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, max_size) {
  s21::multiset<double> a({2.2, 2.2, 2.2});
  s21::multiset<double> b({3.3, 3.3});
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(multiset, clear1) {
  s21::multiset<double> a;
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, clear2) {
  s21::multiset<double> a({2.2, 2.2, 2.2});
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 3);
  a.clear();
  EXPECT_EQ(a.empty(), true);
  EXPECT_EQ(a.size(), 0);
};

TEST(multiset, insert_to_empty) {
  s21::multiset<double> a;
  double mass[] = {-9., -0.3, 1.2, 3.3, 3.3, 22.2};
  int j = 0;
  a.insert(22.2);
  a.insert(3.3);
  a.insert(-9.0);
  a.insert(1.2);
  a.insert(3.3);
  a.insert(-0.3);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 6);
};

TEST(multiset, insert) {
  s21::multiset<double> a({22.2, 3.3, -9.0});
  double mass[] = {-9., -0.3, 1.2, 3.3, 3.3, 22.2};
  int j = 0;
  a.insert(1.2);
  a.insert(3.3);
  a.insert(-0.3);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(a.size(), 6);
};

TEST(multiset, erase_empty) {
  s21::multiset<double> a;
  EXPECT_THROW(a.erase(nullptr), std::out_of_range);
};

TEST(multiset, erase1) {
  s21::multiset<std::string> a({"Hello", "world", "and", "humanty"});
  s21::multiset<std::string> b({"Life"});
  auto rem = b.begin();
  a.erase(rem);
  EXPECT_EQ(a.size(), 4);
};

TEST(multiset, erase2) {
  s21::multiset<std::string> a({"Hello", "world", "and", "humanity"});
  const char* mass[] = {"Hello", "and", "humanity", "world"};
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(*i, mass[j++]);
  }
  for (int i = 0; i < 4; ++i) {
    auto rem = a.begin();
    a.erase(rem);
    int k = i + 1;
    if (i != 3) {
      for (auto j = a.begin(); j != a.end(); ++j) {
        EXPECT_EQ(*j, mass[k++]);
      }
    } else {
      EXPECT_EQ(a.empty(), true);
      EXPECT_EQ(a.size(), 0);
    }
  }
};

TEST(multiset, swap) {
  s21::multiset<std::string> a({"1", "2", "3", "4"}), b({"5", "6", "7"});
  const char* mass1[] = {"1", "2", "3", "4"};
  const char* mass2[] = {"5", "6", "7"};
  std::swap(a, b);
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 4);
  int j = 0;
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass2[j++], *i);
  }
  j = 0;
  for (auto i = b.begin(); i != b.end(); ++i) {
    EXPECT_EQ(mass1[j++], *i);
  }
};

TEST(multiset, empty_swap) {
  s21::multiset<int> a, b;
  std::swap(a, b);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
};

TEST(multiset, merge1) {
  s21::multiset<int> a, b({1, 2, 3, 4, 5});
  int mass[] = {1, 2, 3, 4, 5}, j = 0;
  a.merge(b);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(b.empty(), true);
  EXPECT_EQ(b.size(), 0);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, merge2) {
  s21::multiset<int> a, b({1, 2, 3, 4, 4, 5});
  int mass[] = {1, 2, 3, 4, 4, 5}, j = 0;
  a.merge(b);
  EXPECT_EQ(a.size(), 6);
  EXPECT_EQ(b.empty(), true);
  EXPECT_EQ(b.size(), 0);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass[j++], *i);
  }
};

TEST(multiset, merge3) {
  s21::multiset<double> a({3., 12., 45., 50., 64., 75., 80.});
  s21::multiset<double> b({1., 12., 13., 15., 50., 70., 80.});
  double mass1[] = {1.,  3.,  12., 12., 13., 15., 45.,
                    50., 50., 64., 70., 75., 80., 80.};
  a.merge(b);
  int j = 0;
  EXPECT_EQ(a.size(), 14);
  EXPECT_EQ(b.size(), 0);
  EXPECT_EQ(b.empty(), true);
  for (auto i = a.begin(); i != a.end(); ++i) {
    EXPECT_EQ(mass1[j++], *i);
  }
};

TEST(multiset, counter1) {
  s21::multiset<int> a({1, 2, 3, 4, 5, 4});
  EXPECT_EQ(a.count(50), 0);
  EXPECT_EQ(a.count(4), 2);
  EXPECT_EQ(a.count(1), 1);
};

TEST(multiset, counter2) {
  s21::multiset<int> a;
  EXPECT_EQ(a.count(50), 0);
};

TEST(multiset, find_contains) {
  s21::multiset<int> a({1, 2, 3, 4, 5});
  auto iter = a.find(2);
  a.erase(iter);
  EXPECT_EQ(a.contains(2), false);
  iter = a.find(4);
  a.erase(iter);
  EXPECT_EQ(a.contains(4), false);
  iter = a.find(5);
  a.erase(iter);
  EXPECT_EQ(a.contains(5), false);
  iter = a.find(3);
  a.erase(iter);
  EXPECT_EQ(a.contains(3), false);
  iter = a.find(1);
  a.erase(iter);
  EXPECT_EQ(a.contains(1), false);
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.find(10), a.end());
};

TEST(multiset, range) {
  s21::multiset<int> a({1, 2, 2, 3});
  auto res = a.equal_range(4);
  EXPECT_EQ(res.first, res.second);
  res = a.equal_range(2);
  EXPECT_EQ(a.lower_bound(2), res.first);
  EXPECT_EQ(a.lower_bound(3), res.second);
  for (auto i = res.first; i != res.second; ++i) {
    EXPECT_EQ(*i, 2);
  }
  res = a.equal_range(1);
  EXPECT_EQ(res.first, a.begin());
  EXPECT_EQ(res.second, a.lower_bound(2));
  res = a.equal_range(3);
  EXPECT_EQ(res.first, a.end_elem());
  EXPECT_EQ(res.second, a.end());
};

TEST(multiset, lower_upper_bound) {
  s21::multiset<int> a({1, 2, 2, 3});
  EXPECT_EQ(a.lower_bound(1), a.begin());
  EXPECT_EQ(a.upper_bound(1), a.lower_bound(2));
  EXPECT_EQ(a.upper_bound(2), a.lower_bound(3));
  EXPECT_EQ(a.upper_bound(3), a.end());
};
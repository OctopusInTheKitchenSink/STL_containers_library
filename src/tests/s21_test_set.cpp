#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "../Sorted_Container/Set_Conteiner/s21_set.cpp"

TEST(set, empty_constr) {
  s21::set<int> st;
  s21::set<std::string> st1;
  s21::set<double> st3;
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
  EXPECT_EQ(st1.empty(), true);
  EXPECT_EQ(st1.size(), 0);
  EXPECT_EQ(st1.begin(), nullptr);
  EXPECT_EQ(st1.end(), nullptr);
  EXPECT_EQ(st3.empty(), true);
  EXPECT_EQ(st3.size(), 0);
};

TEST(set, init_list1) {
  s21::set<int> st({});
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
};

TEST(set, init_list2) {
  s21::set<int> st({1, 2, 3, 4});
  int s[] = {1, 2, 3, 4};
  int j = 0;
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.size(), 4);
  for (auto i = st.begin(); i != st.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
};

TEST(set, init_list3) {
  s21::set<int> st({3, 4, 2, 1, 1, 87, 54});
  int s[] = {1, 2, 3, 4, 54, 87};
  int j = 0;
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.size(), 6);
  st.show();
  for (auto i = st.begin(); i != st.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
}

TEST(set, copy_const1) {
  s21::set<int> st({1, 2, 3, 4});
  int s[] = {1, 2, 3, 4};
  int j = 0;
  s21::set<int> st1(st);
  EXPECT_EQ(st.empty(), st1.empty());
  EXPECT_EQ(st.size(), st1.size());
  for (auto i = st.begin(); i != st.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
  j = 0;
  for (auto i = st1.begin(); i != st1.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
};

TEST(set, eq_constr1) {
  s21::set<int> st({1, 2, 3, 4});
  s21::set<int> st1({4, 5, 6, 7, 8, 9, 0});
  int s[] = {1, 2, 3, 4};
  st1 = std::move(st);
  int j = 0;
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st1.empty(), false);
  EXPECT_EQ(st.size(), 0);
  EXPECT_EQ(st1.size(), 4);
  for (auto i = st1.begin(); i != st1.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
};

TEST(set, eq_constr2) {
  s21::set<int> st({1, 2, 3, 4});
  int s[] = {1, 2, 3, 4};
  st = std::move(st);
  int j = 0;
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.size(), 4);
  for (auto i = st.begin(); i != st.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
};

TEST(set, eq_constr3) {
  s21::set<int> a({1, 2, 3});
  a = a;
  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(a.empty(), false);
};

TEST(set, eq_constr4) {
  s21::set<int> a;
  s21::set<int> b = a;
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());
};

TEST(set, eq_constr5) {
  s21::set<int> st({1, 2, 3, 4});
  s21::set<int> st1({4, 5, 6, 7, 8, 9, 0});
  int s[] = {1, 2, 3, 4};
  st1 = st;
  int j = 0;
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st1.empty(), false);
  EXPECT_EQ(st.size(), 4);
  EXPECT_EQ(st1.size(), 4);
  for (auto i = st1.begin(); i != st1.end(); ++i) {
    EXPECT_EQ(*i, s[j++]);
  }
}

TEST(set, begin_end_1) {
  s21::set<double> st({2.3, 4.4, 1.2, 92.2, 0.2, -9.2});
  EXPECT_EQ(*st.begin(), -9.2);
  EXPECT_EQ(*st.end_iter(), 92.2);
  auto ptr = st.end();
  EXPECT_THROW(--ptr, std::out_of_range);
};

TEST(set, begin_end_2) {
  s21::set<double> st({2.3});
  EXPECT_EQ(*st.begin(), 2.3);
  EXPECT_EQ(*st.end_iter(), 2.3);
};

TEST(set, begin_end_3) {
  s21::set<int> st({1});
  st.erase(st.begin());
  EXPECT_EQ(st.begin(), nullptr);
  EXPECT_EQ(st.end_iter(), nullptr);
};

TEST(set, max_size1) {
  s21::set<int> set1;
  s21::set<int> set2;
  EXPECT_EQ(set1.max_size(), set2.max_size());
  set1.insert(1);
  set2.insert(2);
  EXPECT_EQ(set1.size(), 1);
  EXPECT_EQ(set2.size(), 1);
  EXPECT_EQ(set1.max_size(), set2.max_size());
};

TEST(set, max_size2) {
  s21::set<int> set1({1, 2, 3, 4, 5});
  s21::set<int> set2({3, 4, 5});
  EXPECT_EQ(set1.max_size(), set2.max_size());
  set1.insert(1);
  set1.insert(2);
  EXPECT_EQ(set1.max_size(), set2.max_size());
};

TEST(set, max_size3) {
  s21::set<double> a, b;
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(set, max_size4) {
  s21::set<std::string> a, b;
  EXPECT_EQ(a.max_size(), b.max_size());
};

TEST(set, clear1) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7, 8});
  st.clear();
  EXPECT_EQ(st.end(), nullptr);
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
};

TEST(set, clear2) {
  s21::set<int> st;
  st.clear();
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
};

TEST(set, clear3) {
  s21::set<std::string> a({"djahg", "dkjnsd"});
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.empty(), false);
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.empty(), true);
};

TEST(set, insert1) {
  s21::set<double> st;
  for (double i = 0.0; i < 10.0; ++i) {
    auto res = st.insert(i);
    EXPECT_EQ(true, res.second);
  }
  EXPECT_EQ(st.size(), 10);
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.end(), nullptr);
  st.erase(st.begin());
  EXPECT_EQ(*st.begin(), 1.0);
  st.clear();
  EXPECT_EQ(st.size(), 0);
  EXPECT_EQ(st.empty(), true);
};

TEST(set, insert2) {
  s21::set<int> st({1, 2, 3, 4});
  for (int i = 1; i < 11; ++i) {
    auto res = st.insert(i);
    if (i < 5)
      EXPECT_EQ(false, res.second);
    else
      EXPECT_EQ(true, res.second);
  }
  EXPECT_EQ(st.size(), 10);
};

TEST(set, insert3) {
  s21::set<int> a({1, 2, 3});
  a.clear();
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.empty(), true);
  auto res = a.insert(10);
  EXPECT_EQ(res.first, a.begin());
  EXPECT_EQ(res.second, true);
  EXPECT_EQ(a.size(), 1);
}

TEST(set, erase1) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7});
  for (int i = 0; i < 7; ++i) {
    st.erase(st.begin());
    EXPECT_EQ(st.contains(i + 1), false);
  }
  EXPECT_THROW(st.erase(st.begin()), std::out_of_range);
};

TEST(set, erase2) {
  s21::set<int> st;
  EXPECT_THROW(st.erase(st.begin()), std::out_of_range);
  s21::set<std::string> st1;
  EXPECT_THROW(st1.erase(st1.begin()), std::out_of_range);
  s21::set<double> st3;
  EXPECT_THROW(st3.erase(st3.begin()), std::out_of_range);
};

TEST(set, erase3) {
  s21::set<int> t;
  s21::set<int> t1({1});
  EXPECT_THROW(t.erase(t1.end()), std::out_of_range);
};

TEST(set, erase4) {
  s21::set<std::string> a({"akjd", "ghjg", "bkjb"});
  a.erase(a.begin());
  EXPECT_THROW(a.erase(nullptr), std::logic_error);
  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(*a.begin(), "bkjb");
};

TEST(set, swap1) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7});
  int a1[] = {1, 2, 3, 4, 5, 6, 7};
  s21::set<int> st1({10, 20, 30, 40, 50});
  int a2[] = {10, 20, 30, 40, 50};
  st.swap(st1);
  int i = 0;
  for (auto t = st.begin(); t != st.end(); ++t) {
    EXPECT_EQ(*t, a2[i++]);
  }
  EXPECT_EQ(st.size(), 5);
  EXPECT_EQ(st1.size(), 7);
  i = 0;
  for (auto t = st1.begin(); t != st1.end(); ++t) {
    EXPECT_EQ(*t, a1[i++]);
  }
};

TEST(set, find) {
  s21::set<int> st({1, 2, 3, 4, 5, 6, 7, 8, 9});
  EXPECT_EQ(st.contains(1), true);
  st.erase(st.find(1));
  EXPECT_EQ(st.contains(1), false);
  EXPECT_EQ(st.contains(3), true);
  st.erase(st.find(3));
  EXPECT_EQ(st.contains(3), false);
  EXPECT_EQ(st.contains(5), true);
  st.erase(st.find(5));
  EXPECT_EQ(st.contains(5), false);
  EXPECT_EQ(st.contains(7), true);
  st.erase(st.find(7));
  EXPECT_EQ(st.contains(7), false);
  EXPECT_EQ(st.contains(9), true);
  st.erase(st.find(9));
  EXPECT_EQ(st.contains(9), false);
  EXPECT_EQ(st.size(), 4);
  for (int i = 1; i < 10; i++) {
    if (i % 2)
      EXPECT_EQ(st.contains(i), false);
    else
      EXPECT_EQ(st.contains(i), true);
  }
};

TEST(set, merge1) {
  s21::set<int> st1({1, 2, 3, 4});
  s21::set<int> st2({1, 2, 3, 4});
  int a[] = {1, 2, 3, 4};
  st1.merge(st2);
  int i = 0;
  for (auto t = st1.begin(); t != st1.end(); ++t) {
    EXPECT_EQ(*t, a[i++]);
  }
  i = 0;
  for (auto t = st2.begin(); t != st2.end(); ++t) {
    EXPECT_EQ(*t, a[i++]);
  }
};

TEST(set, merge2) {
  s21::set<int> st1({1, 2, 3, 4});
  s21::set<int> st2({3, 4, 5, 6});
  int b[] = {3, 4}, c[] = {1, 2, 3, 4, 5, 6};
  st1.merge(st2);
  int i = 0;
  for (auto t = st1.begin(); t != st1.end(); ++t) {
    EXPECT_EQ(*t, c[i++]);
  }
  EXPECT_EQ(st1.size(), 6);
  i = 0;
  for (auto t = st2.begin(); t != st2.end(); ++t) {
    EXPECT_EQ(*t, b[i++]);
  }
  EXPECT_EQ(st2.size(), 2);
};

TEST(set, merge3) {
  s21::set<int> st1({1, 2, 3, 4});
  s21::set<int> st2({5, 6, 7, 8});
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  st1.merge(st2);
  int i = 0;
  for (auto t = st1.begin(); t != st1.end(); ++t) {
    EXPECT_EQ(*t, a[i++]);
  }
  i = 0;
  EXPECT_EQ(st1.size(), 8);
  EXPECT_EQ(st2.size(), 0);
};

TEST(set, end_iter) {
  s21::set<int> st1({1, 2, 3, 4, 5, 6});
  auto iter = st1.end_iter();
  int a[] = {6, 5, 4, 3, 2, 1};
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(*iter--, a[i]);
  }
};

TEST(set, move_constr1) {
  s21::set<int> st1({1, 2, 3, 4, 5, 6});
  int a[] = {6, 5, 4, 3, 2, 1};
  s21::set<int> st2(std::move(st1));
  EXPECT_EQ(st1.empty(), true);
  EXPECT_EQ(st1.size(), 0);
  EXPECT_EQ(st2.empty(), false);
  EXPECT_EQ(st2.size(), 6);
  auto iter = st2.end_iter();
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(a[i], *iter--);
  }
};

TEST(set, move_constr2) {
  s21::set<int> st1;
  s21::set<int> st2(std::move(st1));
  EXPECT_EQ(st1.empty(), true);
  EXPECT_EQ(st1.size(), 0);
  EXPECT_EQ(st2.empty(), true);
  EXPECT_EQ(st2.size(), 0);
};

TEST(set, copy_constr2) {
  s21::set<int> st1({1, 2, 3, 4, 5, 6});
  s21::set<int> st2({10, 20, 30});
  int a[] = {10, 20, 30};
  int i = 0;
  st1 = st2;
  EXPECT_EQ(st1.size(), st2.size());
  for (auto t = st1.begin(); t != st1.end(); ++t) {
    EXPECT_EQ(a[i++], *t);
  }
};

TEST(set, copy_constr4) {
  s21::set<int> st1;
  s21::set<int> st2(st1);
  EXPECT_EQ(st1.empty(), true);
  EXPECT_EQ(st1.size(), 0);
  EXPECT_EQ(st2.empty(), true);
  EXPECT_EQ(st2.size(), 0);
}

TEST(set, copy_constr3) {
  s21::set<int> st1;
  s21::set<int> st2;
  st1 = st2;
  EXPECT_EQ(st1.empty(), true);
  EXPECT_EQ(st1.size(), 0);
  EXPECT_EQ(st2.empty(), true);
  EXPECT_EQ(st2.size(), 0);
};

TEST(set, contains_1) {
  s21::set<double> a(
      {1.2, -2.2, -4.7, 67.2, 12., 54., 34., -234., -23., -67., 98.});
  EXPECT_EQ(a.contains(-6.), false);
  EXPECT_EQ(a.contains(1.2), true);
  EXPECT_EQ(a.contains(-2.2), true);
  EXPECT_EQ(a.contains(-4.7), true);
  EXPECT_EQ(a.contains(67.2), true);
  EXPECT_EQ(a.contains(12.), true);
  EXPECT_EQ(a.contains(54.), true);
  EXPECT_EQ(a.contains(34.), true);
  EXPECT_EQ(a.contains(-234.), true);
  EXPECT_EQ(a.contains(-23.), true);
  EXPECT_EQ(a.contains(-67.), true);
  EXPECT_EQ(a.contains(98.), true);
  s21::set<std::string> b({"a", "b", "c"});
  EXPECT_EQ(b.contains("b"), true);
  EXPECT_EQ(b.contains("f"), false);
}

TEST(set, insert_many_1) {
  s21::set<int> s;
  int a[] = {1, 2, 3, 8, 4, 5, 6, 7, 8}, b[] = {1, 2, 3, 4, 5, 6, 7, 8};
  auto vec = s.insert_many(1.1, 2.4f, 3, 8, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    if (i == 8) {
      EXPECT_EQ(false, vec[i].second);
    } else
      EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, b[j++]);
  }
};

TEST(set, insert_many_2) {
  s21::set<int> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(set, insert_many_3) {
  s21::set<int> s({10, 12, 14});
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14};
  auto vec = s.insert_many(1.1, 2.4f, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(set, insert_many_4) {
  s21::set<double> s;
  double a[] = {1.1, 2.4, 3, 4, 5, 6.6, 7., 8};
  auto vec = s.insert_many(1.1, 2.4, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(set, insert_many_5) {
  s21::set<int> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(set, insert_many_6) {
  s21::set<double> s({10.2, 12.1, 14.8});
  double a[] = {-1.1, 2.4, 3, 4, 5, 6.6, 7, 8, 10.2, 12.1, 14.8};
  auto vec = s.insert_many(-1.1, 2.4, 3, std::move(4), 5, 6.6, 7.f, 8);
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(a[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(set, insert_many_7) {
  s21::set<std::string> s;
  std::string a[] = {"a", "b", "c", "d", "d"}, b[] = {"c", "a", "d", "d", "b"};
  auto vec = s.insert_many("c", "a", "d", std::move("d"), "b");
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    if (i == 3) {
      EXPECT_EQ(false, vec[i].second);
      j++;
    } else
      EXPECT_EQ(b[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

TEST(set, insert_many_8) {
  s21::set<std::string> s;
  auto vec = s.insert_many();
  int j = 0;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(s.empty(), true);
};

TEST(set, insert_many_9) {
  s21::set<std::string> s({"h", "w", "z"});
  std::string a[] = {"a", "b", "c", "h", "w", "z"}, b[] = {"c", "b", "a"};
  auto vec = s.insert_many(std::move("c"), std::move("b"), "a");
  int j = 0;
  for (auto i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(b[j++], *vec[i].first);
  }
  j = 0;
  for (auto i = s.begin(); i != s.end_iter(); ++i) {
    EXPECT_EQ(*i, a[j++]);
  }
};

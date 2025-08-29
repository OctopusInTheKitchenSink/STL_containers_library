#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>
#include <list>

#include "../Sequence_Containers/list/s21_list.h"

TEST(list, constructor){
    s21::list<int> a;
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_THROW(a.pop_front(), std::out_of_range);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
};

TEST(list, constructor_with_size){
    s21::list<int> a(5);
    EXPECT_EQ(a.empty(), false);
    EXPECT_EQ(a.size(), 5);
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, 0);
    }
};

TEST(list, constructor_with_init_list){
    s21::list<int> a({6, 5, 4, 3, 8, 5, 7, 3, 6, 7});
    int buff[] = {6, 5, 4, 3, 8, 5, 7, 3, 6, 7};
    EXPECT_EQ(a.size(), 10);
    EXPECT_EQ(a.empty(), false);
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, constructor_with_empty_init_list){
    s21::list<int> a({});
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_THROW(a.pop_front(), std::out_of_range);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
};

TEST(list, copy_constructor_1){
    s21::list<int> a({5, 4, 7, 6, 5});
    s21::list<int> b(a);
    EXPECT_EQ(a.max_size(), b.max_size());
    int buff[] = {5, 4, 7, 6, 5};
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
};

TEST(list, copy_constructor_2){
    s21::list<int> a({});
    s21::list<int> b(a);
    EXPECT_EQ(a.max_size(), b.max_size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_THROW(a.pop_front(), std::out_of_range);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
    EXPECT_THROW(b.pop_front(), std::out_of_range);
    EXPECT_THROW(b.pop_back(), std::out_of_range);
};

TEST(list, copy_constructor_3){
    s21::list<int> a;
    s21::list<int> b(a);
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_THROW(a.pop_front(), std::out_of_range);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
    EXPECT_THROW(b.pop_front(), std::out_of_range);
    EXPECT_THROW(b.pop_back(), std::out_of_range);
};

TEST(list, move_constructor_1){
    s21::list<int> a({5, 4, 7, 6, 5});
    s21::list<int> b(std::move(a));
    int buff[] = {5, 4, 7, 6, 5};
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), false);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 5);
    int j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
};

TEST(list, move_constructor_2){
    s21::list<int> a({});
    s21::list<int> b(std::move(a));
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 0);
};

TEST(list, move_constructor_3){
    s21::list<int> a;
    s21::list<int> b(std::move(a));
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 0);
};

TEST(list, move_assignment_operator_1){
    s21::list<int> a({5, 4, 7, 6, 5});
    s21::list<int> b({6, 4, 2});
    b = std::move(a);
    int buff[] = {5, 4, 7, 6, 5};
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), false);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 5);
    int j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
};

TEST(list, move_assignment_operator_2){
    s21::list<int> a({});
    s21::list<int> b({});
    b = std::move(a);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 0);
};

TEST(list, move_assignment_operator_3){
    s21::list<int> a;
    s21::list<int> b;
    b = std::move(a);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 0);
};

TEST(list, start_end_sides_1){
    s21::list<int> a({5, 4, 7, 6, 5});
    EXPECT_EQ(a.front(), *a.begin());
    EXPECT_EQ(a.back(), *a.end());
};

TEST(list, start_and_sides_2){
    s21::list<int> a;
    EXPECT_THROW(a.front(), std::logic_error);
    EXPECT_THROW(a.back(), std::logic_error);
    EXPECT_EQ(a.begin(), a.end());
};

TEST(list, start_and_sides_3){
    s21::list<int> a({});
    EXPECT_THROW(a.front(), std::logic_error);
    EXPECT_THROW(a.back(), std::logic_error);
    EXPECT_EQ(a.begin(), a.end());
};

TEST(list, clear_1){
    s21::list<int> a({5, 4, 7, 6, 5});
    a.clear();
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
};

TEST(list, clear_2){
    s21::list<int> a({});
    a.clear();
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
};

TEST(list, clear_3){
    s21::list<int> a;
    a.clear();
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
};

TEST(list, insert_erase_1){
    s21::list<double> a({2.2, -2.1, 3.4, 77.6, 0.1});
    double buff[] = {3.3, 3.4, -41.1, 77.6, 0.1};
    EXPECT_EQ(*a.insert(++a.begin(), 3.3), 3.3);
    a.insert(--a.end(), -41.1);
    EXPECT_THROW(a.insert(nullptr, 34), std::invalid_argument);
    a.erase(a.begin());
    a.erase(++a.begin());
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(buff[j++], *i);
    }
    EXPECT_THROW(a.erase(nullptr), std::out_of_range);
    a.erase(a.end());
    EXPECT_EQ(*a.end(), 77.6);
    EXPECT_EQ(a.size(), 4);
};

TEST(list, push_pop){
    s21::list<int> a;
    a.push_back(12.2);
    a.push_front(32);
    EXPECT_EQ(*a.begin(), 32);
    EXPECT_EQ(*(++a.begin()), 12);
    EXPECT_EQ(a.size(), 2);
    a.push_back(222);
    EXPECT_EQ(a.back(), 222);
    EXPECT_EQ(a.size(), 3);
    a.pop_front();
    EXPECT_EQ(a.front(), 12);
    EXPECT_EQ(a.size(), 2);
    a.pop_back();
    EXPECT_EQ(a.back(), 12);
    EXPECT_EQ(a.size(), 1);
    a.pop_front();
    EXPECT_EQ(a.size(), 0);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
    EXPECT_THROW(a.pop_front(), std::out_of_range);
};

TEST(list, swap){
    s21::list<std::string> a({"Hello", "darkness", "my", "old", "friend"});
    s21::list<std::string> b({"Coraline,", "Coraline,", "dimmi", "le", "tue", "verità"});
    std::string buff1[] = {"Hello", "darkness", "my", "old", "friend"},
    buff2[] = {"Coraline,", "Coraline,", "dimmi", "le", "tue", "verità"};
    a.swap(b);
    int j = 0;
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(b.size(), 5);
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff2[j++]);
    }
    EXPECT_EQ(*a.end(), buff2[j]);
    j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff1[j++]);
    }
    EXPECT_EQ(*b.end(), buff1[j]);
};

TEST(list, empty_swap){
    s21::list<int> a, b;
    a.swap(b);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
};

TEST(list, merge){
    s21::list<int> a;
    a.merge(a);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
};

TEST(list, sort_merge_1){
    s21::list<double> a({23.2, 1233.1, 654.4, -12, -0.2, 13, 6.6}),
    b({-12, 3.1, -0, 121., 12, 654.4, 3});
    double buff_a[] = {-12, -0.2, 6.6, 13, 23.2, 654.4, 1233.1}, 
    buff_b[] = {-12, 0, 3, 3.1, 12, 121, 654.4}, 
    buff_res[] = {-12, -12, -0.2, 0, 3, 3.1, 6.6, 12, 13, 23.2, 121, 654.4, 654.4, 1233.1};
    a.sort(), b.sort();
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_a[j++]);
    }
    EXPECT_EQ(*a.end(), buff_a[j]);
    j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff_b[j++]);
    }
    EXPECT_EQ(*b.end(), buff_b[j]);
    a.merge(b);
    j = 0;
    EXPECT_EQ(a.size(), 14);
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_res[j++]);
    }
    EXPECT_EQ(*a.end(), buff_res[j]);
};

TEST(list, sort_merge_2){
    s21::list<std::string> a({"cucumber", "a", "b"}), b({"m", "d", "hello"});
    std::string buff_a[] = {"a", "b", "cucumber"}, buff_b[] = {"d", "hello", "m"},
    buff_merg[] = {"a", "b", "cucumber", "d", "hello", "m"};
    a.sort(), b.sort();
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_a[j++]);
    }
    EXPECT_EQ(*a.end(), buff_a[j]);
    j = 0;
    for(auto i = b.begin(); i != b.end(); ++i){
        EXPECT_EQ(*i, buff_b[j++]);
    }
    EXPECT_EQ(*b.end(), buff_b[j]);
    a.merge(b);
    j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_merg[j++]);
    }
    EXPECT_EQ(*a.end(), buff_merg[j]);
};

TEST(list, splice_1){
    s21::list<double> a({3.3, 12., 7., -3.2, -0.3}), b({90, 60, 43.2, 56., -23.});
    double buff_res[] = {90, 60, 43.2, 56., -23., 3.3, 12., 7., -3.2, -0.3};
    a.splice(a.begin(), b);
    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 10);
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_res[j++]);
    }
    EXPECT_EQ(*a.end(), buff_res[j]);
};

TEST(list, splice_2){
    s21::list<double> a({3.3, 12., 7., -3.2, -0.3}), b({90, 60, 43.2, 56., -23.});
    double buff_res[] = {90, 60, 43.2, 56., -23., 3.3, 12., 7., -3.2, -0.3};
    a.splice(a.begin(), b);
    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.empty(), true);
    EXPECT_EQ(a.size(), 10);
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_res[j++]);
    }
    EXPECT_EQ(*a.end(), buff_res[j]);
};

TEST(list, splice_3){
    s21::list<int> a({1, 2}), b({3, 4});
    EXPECT_THROW(a.splice(b.begin(), b), std::invalid_argument);
    EXPECT_THROW(a.splice(b.end(), b), std::invalid_argument);
};

TEST(list, reverse){
    s21::list<char> a({'a', 'b', 'c', 's', 'a', 'e', 'w'});
    char buff[] = {'w', 'e', 'a', 's', 'c', 'b', 'a'};
    a.reverse();
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, unique){
    s21::list<int> a({2, 3, 2, 3, 5, 6, 7, 123, 342, 6, 6, 5, 5, 85667});
    int buff_1[] = {2, 3, 2, 3, 5, 6, 7, 123, 342, 6, 5, 85667},
    buff_2[] = {2, 3, 5, 6, 7, 123, 342, 85667};
    a.unique();
    EXPECT_EQ(a.size(), 12);
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_1[j++]);
    }
    EXPECT_EQ(*a.end(), buff_1[j]);
    j = 0;
    a.sort();
    a.unique();
    EXPECT_EQ(a.size(), 8);
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff_2[j++]);
    }
    EXPECT_EQ(*a.end(), buff_2[j]);
};

TEST(list, insert_many_back_1){
    s21::list<int> a;
    a.insert_many_back(2, 3, 5, 1, 2, 3, 678);
    int buff[] = {2, 3, 5, 1, 2, 3, 678};
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_back_2){
    s21::list<double> a({3.2, 232.2, -24., 90.2, -574.4});
    a.insert_many_back(-0.2, -0.98, 887.2, 2.2, 56.);
    double buff[] = {3.2, 232.2, -24., 90.2, -574.4, -0.2, -0.98, 887.2, 2.2, 56.};
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_front_1){
    s21::list<int> a;
    a.insert_many_front(2, 3, 5, 1, 2, 3, 678);
    int buff[] = {678, 3, 2, 1, 5, 3, 2};
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_front_2){
    s21::list<double> a({3.2, 232.2, -24., 90.2, -574.4});
    a.insert_many_front(-0.2, -0.98, 887.2, 2.2, 56.);
    double buff[] = {56., 2.2, 887.2, -0.98, -0.2, 3.2, 232.2, -24., 90.2, -574.4};
    int j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_1){
    s21::list<int> a;
    EXPECT_THROW(a.insert_many(nullptr, 1, 2, 3), std::invalid_argument);
};

TEST(list, insert_many_2){
    s21::list<int> a({1, 2, 3});
    a.insert_many(a.begin(), 23, 435, 45, 23, 65);
    int buff[] = {23, 435, 45, 23, 65, 1, 2, 3}, j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_3){
    s21::list<int> a({1, 2, 3});
    auto pos = ++a.begin();
    auto res = a.insert_many(pos, 23, 435, 45, 23, 65);
    int buff[] = {1, 23, 435, 45, 23, 65, 2, 3}, j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
    j = 1;
    for(auto i = res; i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(list, insert_many_4){
    s21::list<int> a({1, 2, 3});
    auto res = a.insert_many(a.end(), 23, 435, 45, 23, 65);
    int buff[] = {1, 2, 23, 435, 45, 23, 65, 3}, j = 0;
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
    j = 2;
    for(auto i = res; i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};


TEST(ListTest, push_back) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.push_back(412);
  b.push_back(412);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, pop_back) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.pop_back();
  b.pop_back();
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, pop_backErr) {
  s21::list<int> a = {};
  EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST(ListTest, pop_back1) {
  s21::list<int> a = {};
  a.push_back(10);
  a.pop_back();
  EXPECT_EQ(a.size(), 0);
}

TEST(ListTest, erase) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  auto it1 = a.begin();
  auto it2 = b.begin();
  a.erase(++it1);
  b.erase(++it2);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  auto it11 = a.begin();
  auto it22 = b.begin();
  a.erase(it11);
  b.erase(it22);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, clear_empty) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.clear();
  b.clear();

  EXPECT_EQ(a.empty(), b.empty());
}

TEST(ListTest, size) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};

  EXPECT_EQ(a.size(), b.size());
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(ListTest, reverse_swap) {
  std::list<int> a = {1, 2, 3};
  std::list<int> a1{a};
  a1.reverse();

  s21::list<int> b = {1, 2, 3};
  s21::list<int> b1{b};
  b1.reverse();
  b.swap(b1);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b1.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, merge) {
  std::list<int> a = {1, 2, 3};
  std::list<int> a1{a};
  a1.merge(a);

  s21::list<int> b = {1, 2, 3};
  s21::list<int> b1{b};
  b1.merge(b);

  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a1.begin();
    auto it2 = b1.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, splice) {
  std::list<int> a{1, 2, 3, 4, 5, 6};
  std::list<int> b{3, 4, 5, 5, 6, 6};
  a.splice(a.end(), b);

  s21::list<int> a1{1, 2, 3, 4, 5, 6};
  s21::list<int> b1{3, 4, 5, 5, 6, 6};
  a1.splice(a1.end_iter(), b1);

  auto it1 = a.end();
  auto it2 = a1.end();

  ASSERT_EQ(a.size(), a1.size());
  auto j = a.begin();
  for(auto i = a1.begin(); i != a1.end_iter(); ++i, ++j){
    EXPECT_EQ(*i, *j);
  }
  
}

TEST(ListTest, InsertMany) {
  s21::list<int> a{1, 2, 3, 4};
  auto it = a.begin();
  ++it;
  a.insert_many(it, 7, 8, 9);
  s21::list<int> b{1, 7, 8, 9, 2, 3, 4};
  it = a.begin();
  for (auto it1 = b.begin(); it1 != b.end(); ++it1) {
    ASSERT_EQ(*it, *it1);
    ++it;
  }
}

TEST(ListTest, front_FrontMany) {
  s21::list<int> a(5);
  s21::list<int> b{4, 3, 2, 1, 0, 0, 0, 0, 0, 10};
  ASSERT_EQ(a.size(), 5);
  a.push_back(10);
  a.insert_many_front(1, 2, 3, 4);
  ASSERT_EQ(a.size(), 10);
  for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(ListTest, move) {
  s21::list<int> a(5);
  s21::list<int> b(std::move(a));
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, move1) {
  s21::list<int> a(5);
  s21::list<int> b;
  b = std::move(a);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, FrontBack) {
  s21::list<int> a{1, 2, 3, 4, 5};
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 5);
}

TEST(ListTest, FrontBackEmpty) {
  s21::list<int> a{};
  EXPECT_THROW(a.front(), std::logic_error);
  EXPECT_THROW(a.back(), std::logic_error);
}

TEST(ListTest, Empty) {
  s21::list<int> a{};
  ASSERT_EQ(a.empty(), 1);
  a.push_back(123);
  ASSERT_EQ(a.empty(), 0);
}

TEST(ListTest, MaxSize) {
  s21::list<int> a{};
  EXPECT_GT(a.max_size(), 10000);
}

TEST(ListTest, clear) {
  s21::list<int> a{1, 2, 3, 4, 5, 6};
  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(ListTest, insert1) {
  s21::list<int> a{1, 2, 4, 5, 6};
  auto it = a.begin();
  ++it;
  ++it;
  a.insert(it, 3);
  it = a.begin();
  for (size_t i = 1; i < 7; i++) {
    ASSERT_EQ(*it, i);
    ++it;
  }
}

TEST(ListTest, erase1) {
  s21::list<int> a{1, 2, 3, 4};
  auto it = a.end();
  --it;
  a.erase(it);
  it = a.begin();
  int buff[] = {1, 2, 4};
  for (size_t i = 0; i < 3; i++, ++it) {
    ASSERT_EQ(*it, buff[i]);
  }
}

TEST(ListTest, push_front) {
  s21::list<int> a{1, 2, 3, 4};
  a.push_front(10);
  a.push_front(12);
  auto it = a.begin();
  ASSERT_EQ(*it, 12);
  ++it;
  ASSERT_EQ(*it, 10);
  ASSERT_EQ(a.size(), 6);
}

TEST(ListTest, pop_front) {
  s21::list<int> a{1, 2, 3, 4};
  a.pop_front();
  auto it = a.begin();
  ASSERT_EQ(*it, 2);
  a.push_front(12);
  a.push_front(142);
  a.pop_front();
  it = a.begin();
  ASSERT_EQ(*it, 12);
  ASSERT_EQ(a.size(), 4);
}

TEST(ListTest, pop_front_one) {
  s21::list<int> a{1};
  a.pop_front();
  ASSERT_EQ(a.size(), 0);
}

TEST(ListTest, swap) {
  s21::list<int> a{1, 2, 3, 4, 5};
  s21::list<int> b{5, 4, 3};
  a.swap(b);
  auto itA = a.begin();
  auto itB = b.begin();
  for (size_t i = 5; i > 2; i--) {
    ASSERT_EQ(*itA, i);
    ++itA;
  }

  for (size_t i = 1; i < 6; i++) {
    ASSERT_EQ(*itB, i);
    ++itB;
  }

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, merge1) {
  s21::list<int> a{1, 5, 6, 9, 9};
  s21::list<int> b{5, 6, 7, 8, 12, 12};
  s21::list<int> total{1, 5, 5, 6, 6, 7, 8, 9, 9, 12, 12};
  a.merge(b);
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
  ASSERT_EQ(a.size(), total.size());
}

TEST(ListTest, merge2) {
  s21::list<int> a{1, 5, 6, 9, 9};
  s21::list<int> b{1, 5};
  s21::list<int> total{1, 1, 5, 5, 6, 9, 9};
  a.merge(b);
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       ++it1, ++it2) {
    ASSERT_EQ(*it1, *it2);
  }
  ASSERT_EQ(a.size(), total.size());
}

TEST(ListTest, max_size) {
  s21::list<int> a = {1, 2, 3};

  EXPECT_GT(a.max_size(), 1000);
}

TEST(ListTest, reverseErr) {
  s21::list<int> a = {};
  EXPECT_THROW(a.reverse(), std::logic_error);
}

TEST(ListTest, splice1) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6};
  s21::list<int> b = {100, 200, 300, 400, 500};
  s21::list<int> total = {1, 2, 100, 200, 300, 400, 500, 3, 4, 5, 6};
  auto it = a.begin();
  ++it;
  ++it;
  a.splice(it, b);

  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
  }
}

TEST(ListTest, splice2) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6};
  s21::list<int> b = {100, 200, 300, 400, 500};
  s21::list<int> total = {1, 2, 3, 4, 5, 100, 200, 300, 400, 500, 6};
  auto it = a.end();
  a.splice(it, b);

  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
  }
}

TEST(ListTest, unique) {
  s21::list<int> a = {1, 1, 1, 1, 2, 2, 3, 5, 6, 6, 8};
  s21::list<int> total = {1, 2, 3, 5, 6, 8};
  a.unique();
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(a.size(), total.size());
}

TEST(ListTest, insertManyBack) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_back(4, 5, 6, 7);
  auto it = a.begin();
  for (size_t i = 1; i < 8; i++) {
    EXPECT_EQ(*it, i);
    ++it;
  }
  EXPECT_EQ(a.size(), 7);
}

TEST(ListTest, sort) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_back(5, 1, 2, 5, 12, 3, 5, 6, 1, 4);
  std::list<int> total{1, 2, 3, 5, 1, 2, 5, 12, 3, 5, 6, 1, 4};
  a.sort();
  total.sort();
  auto it1 = total.begin();
  for (auto it = a.begin(); it != a.end(); ++it, ++it1) {
    EXPECT_EQ(*it, *it1);
  }
  EXPECT_EQ(a.size(), total.size());
}

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>
#include <vector>

#include "../Sequence_Containers/vector/s21_vector.h"

TEST(vector, empty_constructor){
    s21::vector<int> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
};

TEST(vector, const_with_size){
    s21::vector<int> a(10);
    EXPECT_EQ(a.size(), 10);
    EXPECT_EQ(a.capacity(), 10);
    for(size_t i = 0; i < a.size(); ++i){
        EXPECT_EQ(a[i], 0);
    }
};

TEST(vector, init_list_1){
    s21::vector<int> a({1, 2, 3});
    for(size_t i = 0; i < a.size(); ++i){
        EXPECT_EQ(a[i], i + 1);
    }
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, init_list_2){
    s21::vector<int> a({});
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, copy_constr_1){
    s21::vector<int> a({1, 2, 3});
    a.push_back(34);
    s21::vector<int> b(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    for(size_t i = 0; i < a.size(); ++i){
        EXPECT_EQ(a[i], b[i]);
    }
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, copy_constr_2){
    s21::vector<int> a({});
    s21::vector<int> b(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, copy_constr_3){
    s21::vector<int> a;
    s21::vector<int> b(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.capacity(), 0);
};

TEST(vector, move_constr_1){
    s21::vector<int> a({1, 2, 3});
    a.push_back(4);
    s21::vector<int> b(std::move(a));
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), false);
    for(size_t i = 0; i < b.size(); ++i){
        EXPECT_EQ(b[i], i + 1);
    }
    EXPECT_EQ(a.capacity(), 0);
    EXPECT_EQ(b.capacity(), 20);
};

TEST(vector, move_constr_2){
    s21::vector<int> a;
    s21::vector<int> b(std::move(a));
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.capacity(), b.capacity());
};

TEST(vector, move_assignment_1){
    s21::vector<int> a({1, 2, 3});
    a = std::move(a);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.empty(), false);
    for(size_t i = 0; i < a.size(); ++i){
        EXPECT_EQ(a[i], i + 1);
    }
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, move_assignment_2){
    s21::vector<int> a({1, 2, 3});
    a.push_back(4);
    s21::vector<int> b = std::move(a);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(b.empty(), false);
    for(size_t i = 0; i < b.size(); ++i){
        EXPECT_EQ(b[i], i + 1);
    }
    EXPECT_EQ(a.capacity(), 0);
    EXPECT_EQ(b.capacity(), 20);
};

TEST(vector, move_assignment_3){
    s21::vector<int> a;
    s21::vector<int> b = std::move(a);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.capacity(), b.capacity());
};

TEST(vector, move_assignment_4){
    s21::vector<int> a({6, 7, 8, 9});
    s21::vector<int> b({1, 2, 3, 4, 5});
    b = std::move(a);
    EXPECT_EQ(a.empty(), true);
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(b.empty(), false);
    EXPECT_EQ(b.size(), 4);
    for(size_t i = 0; i < b.size(); ++i){
        EXPECT_EQ(b[i], i + 6);
    }
    EXPECT_EQ(b.capacity(), 20);
};

TEST(vector, at_1){
    s21::vector<int> a({1, 2, 3});
    EXPECT_EQ(a.at(1), 2);
    EXPECT_EQ(a.at(0), 1);
    EXPECT_EQ(a.at(10), 0);
    EXPECT_THROW(a.at(50), std::out_of_range);
    EXPECT_THROW(a.at(-10), std::out_of_range);
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, data1){
    s21::vector<double> a({-1.1, -2.2, 1.2, 2.4, 0});
    auto mass = a.data();
    double buff[] = {-1.1, -2.2, 1.2, 2.4, 0};
    for(size_t i = 0; i < a.size(); ++i){
        EXPECT_EQ(mass[i], buff[i]);
    }
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, begin_end){
    s21::vector<int> a({1, 2, 3, 4, 5, 6, 7, 8, 9});
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, a[*i - 1]);
    }
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, max_size1){
    s21::vector<int> a({1, 2}), b({1, 2, 3, 4});
    EXPECT_EQ(a.max_size(), b.max_size());
    s21::vector<int> c, d;
    EXPECT_EQ(c.max_size(), d.max_size());
    EXPECT_EQ(a.capacity(), 20);
};

TEST(vector, reserve){
    s21::vector<int> a({1, 2, 3, 4});
    a.reserve(100);
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.capacity(), 100);
    for(size_t i = 0; i < a.size(); ++i){
        if(i < 4){
            EXPECT_EQ(a[i], i + 1);
        }
        else{
            EXPECT_EQ(a[i], 0);
        }
    }
    EXPECT_EQ(a.capacity(), 100);
};

TEST(vector, shrink_1){
    s21::vector<int> a({1, 2, 3, 4});
    a.reserve(100);
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.capacity(), 100);
    for(size_t i = 0; i < a.size(); ++i){
        if(i < 4){
            EXPECT_EQ(a[i], i + 1);
        }
        else{
            EXPECT_EQ(a[i], 0);
        }
    }
    EXPECT_EQ(a.capacity(), 100);
    a.shrink_to_fit();
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a.capacity(), 4);
};

TEST(vector, shrink_2){
    s21::vector<int> a({1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
    EXPECT_EQ(a.capacity(), 20);
    a.shrink_to_fit();
    EXPECT_EQ(a.capacity(), 10);
    s21::vector<int> b;
    b.reserve(30);
    b.shrink_to_fit();
    EXPECT_EQ(b.capacity(), 0);
};

TEST(vector, clear1){
    s21::vector<int> a;
    a.clear();
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 0);
    a.push_back(10);
    a.push_back(20);
    EXPECT_EQ(a.size(), 2);
    a.clear();
    EXPECT_EQ(a.size(), 0);
    for(int i = 0; i < a.capacity(); ++i){
        EXPECT_EQ(a[i], 0);
    }
};

TEST(vector, insert01){
    s21::vector<int> a(5), b;
    auto res = a.insert(&a[2], 3);
    EXPECT_EQ(*res, 3);
    res = a.insert(&a[1], 2);
    EXPECT_EQ(*res, 2);
    res = a.insert(&a[0], 1);
    EXPECT_EQ(*res, 1);
    res = a.insert(&a[0], 0);
    EXPECT_EQ(*res, 0);
    res = a.insert(&a[6], 4);
    EXPECT_EQ(*res, 4);
    EXPECT_THROW(a.insert(&b[0], 7), std::out_of_range);
    EXPECT_EQ(a.size(), 10);
    int buff[] = {0, 1, 0, 2, 0, 3, 4, 0, 0, 0};
    int j = 0;
    auto i = a.end();
    for(auto i = a.begin(); i != a.end(); ++i){
        EXPECT_EQ(*i, buff[j++]);
    }
    EXPECT_EQ(*a.end(), buff[j]);
};

TEST(vector, erase1){
    s21::vector<int> a({1, 2, 3, 4, 5, 6, 7}), b(2);
    int buff[] = {2, 5, 6, 7};
    a.erase(&a[0]);
    a.erase(&a[1]);
    a.erase(&a[2]);
    EXPECT_THROW(a.erase(&b[0]), std::out_of_range);
    EXPECT_THROW(a.erase(&a[50]), std::out_of_range);
    EXPECT_EQ(a.size(), 4);
};

TEST(vector, front_back1){
    s21::vector<int> a({1, 2, 3, 4});
    EXPECT_EQ(a.front(), 1);
    EXPECT_EQ(a.back(), 4);
    a.clear();
    EXPECT_THROW(a.front(), std::logic_error);
    EXPECT_THROW(a.back(), std::logic_error);
};

TEST(vector, pop){
    s21::vector<int> a;
    for(int i = 0; i < 100; ++i){
        a.push_back(i);
    }
    EXPECT_EQ(a.size(), 100);
    EXPECT_EQ(a.capacity(), 160);
    for(int i = 0; i < 100; ++i){
        a.pop_back();
    }
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 160);
    EXPECT_THROW(a.pop_back(), std::out_of_range);
};

TEST(vector, create) {
  s21::vector<int> vec(5);

  EXPECT_EQ(vec.size(), 5);
};

TEST(vector, empty) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, Iterator) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  for (auto it1 = vec.begin(); it1 != vec.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, const_iterator) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  for (auto it1 = vec.begin(); it1 != vec.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, Iterator1) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1 = vec;
  for (auto it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, const_iterator1) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1 = vec;
  for (auto it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, move) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1(std::move(vec));
  for (auto it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, move1) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1;
  vec1 = std::move(vec);
  for (auto it1 = vec1.begin(); it1 != vec1.end(); ++it1) {
    EXPECT_EQ(*it1, 1);
  }
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, at) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  EXPECT_EQ(vec.at(4), 1);

  EXPECT_THROW(vec.at(22), std::out_of_range);
}

TEST(vector, bracket) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  vec[5] = 10;
  EXPECT_EQ(vec[5], 10);
}

TEST(vector, front_back) {
  s21::vector<int> vec{50, 1, 1, 1, 1, 1, 112};
  EXPECT_EQ(vec.front(), 50);
  EXPECT_EQ(vec.back(), 112);

  s21::vector<int> vec1{};
  EXPECT_THROW(vec1.front(), std::logic_error);
  EXPECT_THROW(vec1.back(), std::logic_error);
}

TEST(vector, data) {
  s21::vector<int> vec{50, 1, 1, 1, 1, 1, 112};

  int *data = vec.data();
  data[6] = 32;
  EXPECT_EQ(data[0], 50);
  EXPECT_EQ(data[6], 32);
}

TEST(vector, not_empty) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_EQ(vec.empty(), false);
  EXPECT_EQ(vec.size(), 3);
};

TEST(vector, reserve_capacity) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(152);
  EXPECT_EQ(vec.capacity(), 152);
};

TEST(vector, shrink_to_fit) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(152);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 3);
};

TEST(vector, clear) {
  s21::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, insert) {
  s21::vector<int> vec{1, 2, 3, 4, 5, 6};
  auto it = vec.end();
  --it;
  --it;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert1) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.end();
  --it;
  --it;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert2) {
  s21::vector<int> vec{};
  auto it = vec.begin();
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert5) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(4);
  auto it = vec.begin();
  ++it;
  ++it;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, erase) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  auto it = vec.end();
  --it;
  --it;
  vec.erase(it);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 4);
  EXPECT_EQ(vec[3], 5);
};

TEST(vector, push_back) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.push_back(6);
  vec.push_back(7);
  vec.push_back(9);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 9);
};

TEST(vector, pop_back) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.pop_back();
  vec.pop_back();
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
};

TEST(vector, max_size) {
  s21::vector<int> vec{};
  EXPECT_GT(vec.max_size(), 10000);
};

TEST(vector, erase_error1) {
  s21::vector<int> vec{};
  auto it = vec.begin();
  EXPECT_THROW(vec.erase(it), std::out_of_range);
};

TEST(vector, const_iterator2) {
  s21::vector<int> vec{1, 5};
  auto it = vec.begin();
  ++it;
  EXPECT_EQ(*it, 5);
  --it;
  EXPECT_EQ(*it, 1);
  it = vec.end();
};

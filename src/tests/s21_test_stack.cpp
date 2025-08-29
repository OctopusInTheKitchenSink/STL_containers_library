#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "../Container_Adaptor/stack/s21_stack.cpp"

TEST(stack, empty_const) {
  s21::stack<int> st;
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
};

TEST(stack, push_1) {
  s21::stack<double> st({1.2, 2.2});
  EXPECT_EQ(st.size(), 2);
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.top(), 2.2);
};

TEST(stack, push_2) {
  s21::stack<double> st({1.2, 2.2});
  st.push(2.2);
  st.push(3.3);
  EXPECT_EQ(st.size(), 4);
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.top(), 3.3);
};

TEST(stack, const_copy) {
  s21::stack<std::string> st({"Hello", "world"});
  s21::stack<std::string> st1(st);
  EXPECT_EQ(st.empty(), st1.empty());
  EXPECT_EQ(st.size(), st1.size());
  EXPECT_EQ(st1.top(), st.top());
};

TEST(stack, move_test) {
  s21::stack<std::string> st({"Hello", "world"});
  s21::stack<std::string> st1 = std::move(st);
  EXPECT_EQ(st.empty(), true);
  EXPECT_EQ(st.size(), 0);
  EXPECT_EQ(st1.empty(), false);
  EXPECT_EQ(st1.size(), 2);
  EXPECT_EQ(st1.top(), "world");
  EXPECT_THROW(st.top(), std::out_of_range);
};

TEST(stack, assign_move) {
  s21::stack<std::string> st({"acjh"});
  st = s21::stack<std::string>({"jsbc", "cksjb"});
  EXPECT_EQ(st.size(), 2);
  EXPECT_EQ(st.empty(), false);
  EXPECT_EQ(st.top(), "cksjb");
};

TEST(stack, pop_1) {
  s21::stack<int> st({1, 2, 3, 4, 5, 6});
  EXPECT_EQ(st.top(), 6);
  st.pop();
  EXPECT_EQ(st.top(), 5);
  st.pop();
  st.pop();
  st.pop();
  EXPECT_EQ(st.top(), 2);
  st.pop();
  st.pop();
  EXPECT_THROW(st.pop(), std::out_of_range);
};

TEST(stack, swap_1) {
  s21::stack<int> st({1, 2, 3, 4, 5, 6});
  s21::stack<int> st1({10, 20, 30, 40, 50, 60});
  st.swap(st1);
  EXPECT_EQ(st.size(), st1.size());
  for (int i = 6; i > 0; --i) {
    EXPECT_EQ(st1.top(), i);
    EXPECT_EQ(st.top(), i * 10);
    st.pop();
    st1.pop();
  }
  EXPECT_THROW(st.pop(), std::out_of_range);
  EXPECT_THROW(st1.pop(), std::out_of_range);
};

TEST(stack, insert_many_1) {
  std::string str[] = {"six", "five", "four", "three", "two", "one"};
  s21::stack<std::string> q{"one", "two", "three", "four"};
  q.insert_many_back("five", "six");
  EXPECT_EQ(q.empty(), false);
  EXPECT_EQ(q.size(), 6);
  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(q.top(), str[i]);
    q.pop();
  }
  EXPECT_THROW(q.pop(), std::out_of_range);
};

TEST(stack, insert_many_2) {
  s21::stack<int*> q;
  q.insert_many_back(nullptr, new int(5));
  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.empty(), false);
  EXPECT_EQ(*q.top(), 5);
  q.pop();
  EXPECT_EQ(q.top(), nullptr);
  q.pop();
  EXPECT_THROW(q.pop(), std::out_of_range);
};

TEST(stack, insert_many_3) {
  s21::stack<int> q{1, 2, 3};
  int buff[] = {3, 3, 2, 1};
  int x = q.top();
  q.insert_many_back(x);
  EXPECT_EQ(q.size(), 4);
  EXPECT_EQ(q.empty(), false);
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(q.top(), buff[i]);
    q.pop();
  }
};
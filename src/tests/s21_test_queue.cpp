#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>

#include "../Container_Adaptor/queue/s21_queue.h"

TEST(queue, push_1)
{
    s21::queue<int> new_q;
    new_q.push(2);
    new_q.push(3);
    EXPECT_EQ(new_q.size(), 2);
};

TEST(queue, push_2)
{
    s21::queue<int> new_q({1, 2, 3});
    new_q.push(2);
    new_q.push(3);
    EXPECT_EQ(new_q.size(), 5);
}

TEST(queue, init_list_1)
{
    s21::queue<double> new_q({2.2, 3.3, 4.4});
    EXPECT_EQ(new_q.size(), 3);
};

TEST(queue, copy_const)
{
    s21::queue<double> new_q({2.2, 3.3, 4.4});
    s21::queue<double> q2(new_q);
    EXPECT_EQ(new_q.size(), 3);
};

TEST(queue, move_test)
{
    s21::queue<std::string> str({"Hello", "World"});
    auto len = str.size();
    s21::queue<std::string> str2 = std::move(str);
    EXPECT_EQ(len, str2.size());
    EXPECT_EQ(str.size(), 0);
    EXPECT_TRUE(str.empty());
};

TEST(queue, assign_move)
{
    s21::queue<std::string> str1({"lksdm", "sdjh"});
    str1 = s21::queue<std::string>({"Hello", "world", "!"});
    EXPECT_EQ(str1.size(), 3);
};

TEST(queue, front_1)
{
    s21::queue<std::string> str1({"lksdm", "sdjh"});
    EXPECT_EQ(str1.front(), "lksdm");
    EXPECT_EQ(str1.size(), 2);
};

TEST(queue, front_2)
{
    s21::queue<std::string> str1;
    EXPECT_THROW(str1.front(), std::out_of_range);
};

TEST(queue, back_1)
{
    s21::queue<std::string> str1({"lksdm", "sdjh"});
    EXPECT_EQ(str1.back(), "sdjh");
    EXPECT_EQ(str1.size(), 2);
};

TEST(queue, back_2)
{
    s21::queue<std::string> str1;
    EXPECT_THROW(str1.back(), std::out_of_range);
};

TEST(queue, pop_1)
{
    s21::queue<int> que({1, 2, 3, 4, 5});
    que.pop();
    EXPECT_EQ(que.front(), 2);
    que.pop();
    EXPECT_EQ(que.front(), 3);
    que.push(9);
    que.pop();
    que.pop();
    que.pop();
    EXPECT_EQ(que.front(), 9);
    que.pop();
    EXPECT_THROW(que.pop(), std::out_of_range);
};

TEST(queue, swap_1)
{
    s21::queue<float> q1({1.2f, 2.3f, 4.5f});
    s21::queue<float> q2({3.1f, 5.6f, 7.2f, 7.2f, 78.2f});
    q1.swap(q2);
    EXPECT_EQ(q1.size(), 5);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q1.front(), 3.1f);
    EXPECT_EQ(q2.front(), 1.2f);
    q1.pop(), q2.pop();
    EXPECT_EQ(q1.front(), 5.6f);
    EXPECT_EQ(q2.front(), 2.3f);
    q1.pop(), q2.pop();
    EXPECT_EQ(q1.front(), 7.2f);
    EXPECT_EQ(q2.front(), 4.5f);
    q2.pop();
    q1.pop();
    EXPECT_THROW(q2.pop(), std::out_of_range);
    EXPECT_EQ(q1.front(), 7.2f);
    q1.pop();
    EXPECT_EQ(q1.front(), 78.2f);
    q1.pop();
    EXPECT_THROW(q1.pop(), std::out_of_range);
};

TEST(queue, insert_many_1){
    s21::queue<int> q;
    q.insert_many_back();
    EXPECT_EQ(q.empty(), true);
    int x = 89;
    q.insert_many_back(2.2f, 3.9, 100, std::move(x));
    EXPECT_EQ(q.size(), 4);
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_EQ(q.front(), 100);
    q.pop();
    EXPECT_EQ(q.front(), 89);
    q.pop();
    EXPECT_THROW(q.pop(), std::out_of_range);
};

TEST(queue, insert_many_2){
    std::string str[] = {"one", "two", "three", "four", "five", "six"};
    s21::queue<std::string> q{"one", "two", "three", "four"};
    q.insert_many_back("five", "six");
    EXPECT_EQ(q.empty(), false);
    EXPECT_EQ(q.size(), 6);
    for(int i = 0; i < 6; ++i){
        EXPECT_EQ(q.front(), str[i]);
        q.pop();
    }
    EXPECT_THROW(q.pop(), std::out_of_range);
};

TEST(queue, insert_many_3){
    s21::queue<int*> q;
    q.insert_many_back(nullptr, new int(5));
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.empty(), false);
    EXPECT_EQ(q.front(), nullptr);
    q.pop();
    EXPECT_EQ(*q.front(), 5);
    q.pop();
    EXPECT_THROW(q.pop(), std::out_of_range);
};

TEST(queue, insert_many_4){
    s21::queue<int> q {1, 2, 3};
    int buff[] = {1, 2, 3, 1};
    int x = q.front();
    q.insert_many_back(x);
    EXPECT_EQ(q.size(), 4);
    EXPECT_EQ(q.empty(), false);
    for(int i = 0; i < 4; ++i){
        EXPECT_EQ(q.front(), buff[i]);
        q.pop();
    }
};
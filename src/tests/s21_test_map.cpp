#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <map>

#include "../Sorted_Container/map/s21_map.h"

TEST(MapTest, CreateInsert) {
  s21::map<int, int> a;
  a[1] = 10;
  a[12] = 4;
  EXPECT_EQ(a.at(1), 10);
  EXPECT_EQ(a.at(12), 4);
}

TEST(MAPTest, intializeer_list) {
  s21::map<int, int> a{{1, 2}, {10, 2}, {14, 2}};
  a[10] = 10;
  EXPECT_EQ(a.at(1), 2);
  EXPECT_EQ(a.at(10), 10);
}

TEST(MAPTest, atErr) {
  s21::map<int, int> a{{1, 2}, {10, 2}, {14, 2}};
  EXPECT_THROW(a.at(124), std::out_of_range);
}

TEST(MAPTest, empty) {
  s21::map<int, int> a{{1, 2}, {10, 2}, {14, 2}};
  EXPECT_EQ(a.empty(), 0);
}

TEST(MAPTest, Iterator) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  auto it = a.begin();
  EXPECT_EQ((*it).second, 2);
  it++;
  EXPECT_EQ((*it).second, 5);
  it++;
  EXPECT_EQ((*it).second, 4);
  it--;
  EXPECT_EQ((*it).second, 5);
  EXPECT_EQ(a.end(), nullptr);
}

TEST(MAPTest, size) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  EXPECT_EQ(a.size(), 3);
}

TEST(MAPTest, max_size) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  EXPECT_GT(a.max_size(), 1000);
}

TEST(MAPTest, clear) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  a.clear();
  EXPECT_EQ(a.size(), 0);
}

TEST(MAPTest, InsertOrAssing) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  auto it = a.insert_or_assign(1, 2);
  EXPECT_EQ(it.second, 0);
  EXPECT_EQ((*it.first).second, 2);
  it = a.insert_or_assign(12, 21);
  EXPECT_EQ((*it.first).second, 21);
}

TEST(MAPTest, swap) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  s21::map<int, int> b{{4, 1}, {10, 2}, {141, 4412}, {123, 512}};
  a.swap(b);
  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(b.size(), 3);
  a.merge(b);
  EXPECT_EQ(a.size(), 6);
  EXPECT_EQ(b.size(), 0);
}

TEST(MAPTest, contains) {
  s21::map<int, int> a{{1, 2}, {10, 5}, {14, 4}};
  EXPECT_TRUE(a.contains(1));
  EXPECT_FALSE(a.contains(112));
}

TEST(MAPTest, sizeErase) {
  s21::map<int, int> a{{1, 2}, {10, 2}, {14, 2}};
  EXPECT_EQ(a.size(), 3);
  a[1] = 5;
  EXPECT_EQ(a.size(), 3);
  a[124] = 5;
  EXPECT_EQ(a.size(), 4);
  auto it = a.begin();
  a.erase(it);
  EXPECT_EQ(a.size(), 3);
}

TEST(MAPTest, insert_many) {
  s21::map<int, int> a;
  auto result =
      a.insert_many(std::pair{1, 10}, std::pair{2, 20}, std::pair{1, 999});

  EXPECT_EQ(result.size(), 3);
  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_FALSE(result[2].second);

  EXPECT_EQ(a.size(), 2);
  EXPECT_EQ(a.at(1), 10);
  EXPECT_EQ(a.at(2), 20);
}

TEST(MAPTest, move_assignment) {
  s21::map<int, int> a;
  auto result =
      a.insert_many(std::pair{1, 10}, std::pair{2, 20}, std::pair{1, 999});

  s21::map<int, int> b;
  b.insert({999, 0});

  b = std::move(a);

  EXPECT_EQ(b.size(), 2);
  EXPECT_EQ(b.at(1), 10);
  EXPECT_EQ(b.at(2), 20);
  EXPECT_EQ(a.size(), 0);

  b = std::move(b);
}

TEST(MAPTest, copyConstructorEmpty) {
  s21::map<int, int> original;
  EXPECT_EQ(original.size(), 0);

  s21::map<int, int> copy(original);

  EXPECT_EQ(copy.size(), 0);
  EXPECT_TRUE(copy.empty());

  copy[1] = 42;
  EXPECT_EQ(copy.size(), 1);
  EXPECT_EQ(original.size(), 0);
}

TEST(MAPTest, Insert1) {
  s21::map<int, int> m;
  EXPECT_EQ(m.size(), 0);

  auto res1 = m.insert(1, 10);
  EXPECT_TRUE(res1.second);
  EXPECT_EQ(m.size(), 1);

  auto res2 = m.insert(1, 20);
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(m.size(), 1);
}

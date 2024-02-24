#include <vector>
#include "gtest/gtest.h"
#include "white_box_code.h"

TEST(HashTableTest, InsertOneItem) {
  HashTable<int, std::string> table;
  table.insert(1, "apple");
  EXPECT_EQ(table.size(), 1);
  EXPECT_EQ(table.find(1), "apple");
}
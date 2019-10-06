#include "gtest/gtest.h"

#include "libc/stdlib.h"

TEST(AtoiTest, EmptyString) {
  ASSERT_EQ(lg::atoi(""), 0);
}

TEST(AtoiTest, NullString) {
  ASSERT_EQ(lg::atoi(nullptr), 0);
  ASSERT_EQ(lg::atoi(NULL), 0);
}

TEST(AtoiTest, DigitsOnly) {
  ASSERT_EQ(lg::atoi("0"), 0);
  ASSERT_EQ(lg::atoi("1"), 1);
  ASSERT_EQ(lg::atoi("2"), 2);
  ASSERT_EQ(lg::atoi("10"), 10);
  ASSERT_EQ(lg::atoi("23467814"), 23467814);
  ASSERT_EQ(lg::atoi("0034"), 34);
}

TEST(AtoiTest, NonDigits) {
  ASSERT_EQ(lg::atoi("c"), 0);
  ASSERT_EQ(lg::atoi("1c"), 1);
  ASSERT_EQ(lg::atoi("123x123"), 123);
  ASSERT_EQ(lg::atoi("1345.3"), 1345);
}

TEST(AtoiTest, PlusMinusSigns) {
  ASSERT_EQ(lg::atoi("-1"), -1);
  ASSERT_EQ(lg::atoi("+1"), 1);
}

TEST(AtoiTest, StringsWithWhitespace) {
  ASSERT_EQ(lg::atoi(" 1"), 1);
  ASSERT_EQ(lg::atoi("  -1"), -1);
  ASSERT_EQ(lg::atoi("   -1   "), -1);
}

TEST(AtoiTest, EdgeCases) {
  ASSERT_EQ(lg::atoi("-2147483648"), -2147483648);
  ASSERT_EQ(lg::atoi("2147483647"), 2147483647);
}

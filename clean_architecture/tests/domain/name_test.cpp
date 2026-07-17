#include "../../domain/name.h"

#include <gtest/gtest.h>

TEST(NameTest, ValidName) {
  Name name("Taka");
  EXPECT_EQ(name.getValue(), "Taka");
}

TEST(NameTest, EmptyName) { EXPECT_THROW(Name(""), std::invalid_argument); }

TEST(NameTest, DigitsOnly) {
  EXPECT_THROW(Name("12345"), std::invalid_argument);
}

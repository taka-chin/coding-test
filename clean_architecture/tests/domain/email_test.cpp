#include "../../model/email.h"

#include <gtest/gtest.h>

TEST(EmailTest, ValidEmail) {
  Email email("test@example.com");
  EXPECT_EQ(email.getValue(), "test@example.com");
}

TEST(EmailTest, EmptyEmail) { EXPECT_THROW(Email(""), std::invalid_argument); }

TEST(EmailTest, NoAtmark) {
  EXPECT_THROW(Email("testexample.com"), std::invalid_argument);
}

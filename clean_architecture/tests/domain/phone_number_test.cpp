#include "../../domain/phone_number.h"

#include <gtest/gtest.h>

TEST(PhoneNumberTest, ValidPhoneNumber) {
    PhoneNumber phoneNumber("01012345678");
      EXPECT_EQ(phoneNumber.getValue(), "01012345678");
}

TEST(PhoneNumberTest, EmptyPhoneNumber) { EXPECT_THROW(PhoneNumber(""), std::invalid_argument); }

TEST(PhoneNumberTest, inValidPhoneNumber) {
    EXPECT_THROW(PhoneNumber("010123456789"), std::invalid_argument);
}

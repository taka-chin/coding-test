#include "../../domain/user.h"

#include <chrono>

#include <gtest/gtest.h>

using namespace std::chrono;

TEST(UserTest, ConstructorSetsValues) {
  auto updatedAt = system_clock::time_point{};

  User user(
      1,
      Name("Taka"),
      Email("taka@example.com"),
      PhoneNumber("01012345678"),
      updatedAt);

  EXPECT_EQ(user.getId(), 1);
  EXPECT_EQ(user.getName().getValue(), "Taka");
  EXPECT_EQ(user.getEmail().getValue(), "taka@example.com");
  EXPECT_EQ(user.getPhoneNumber().getValue(), "01012345678");
}

TEST(UserTest, CanUpdateAfterThirtyDays) {
  auto updatedAt = system_clock::time_point{};
  User user(
      1,
      Name("Taka"),
      Email("taka@example.com"),
      PhoneNumber("01012345678"),
      updatedAt);

  EXPECT_FALSE(user.canUpdate(updatedAt + hours(24 * 29)));
  EXPECT_TRUE(user.canUpdate(updatedAt + hours(24 * 30)));
}

TEST(UserTest, UpdateNameChangesNameAndUpdatedAt) {
  auto updatedAt = system_clock::time_point{};
  auto now = updatedAt + hours(24 * 31);
  User user(
      1,
      Name("Taka"),
      Email("taka@example.com"),
      PhoneNumber("01012345678"),
      updatedAt);

  user.updateName(Name("Taro"), now);

  EXPECT_EQ(user.getName().getValue(), "Taro");
  EXPECT_FALSE(user.canUpdate(now + hours(24 * 29)));
  EXPECT_TRUE(user.canUpdate(now + hours(24 * 30)));
}

TEST(UserTest, UpdateEmailChangesEmailAndUpdatedAt) {
  auto updatedAt = system_clock::time_point{};
  auto now = updatedAt + hours(24 * 31);
  User user(
      1,
      Name("Taka"),
      Email("taka@example.com"),
      PhoneNumber("01012345678"),
      updatedAt);

  user.updateEmail(Email("new@example.com"), now);

  EXPECT_EQ(user.getEmail().getValue(), "new@example.com");
  EXPECT_FALSE(user.canUpdate(now + hours(24 * 29)));
  EXPECT_TRUE(user.canUpdate(now + hours(24 * 30)));
}

TEST(UserTest, UpdatePhoneNumberChangesPhoneNumberAndUpdatedAt) {
  auto updatedAt = system_clock::time_point{};
  auto now = updatedAt + hours(24 * 31);
  User user(
      1,
      Name("Taka"),
      Email("taka@example.com"),
      PhoneNumber("01012345678"),
      updatedAt);

  user.updatePhoneNumber(PhoneNumber("09012345678"), now);

  EXPECT_EQ(user.getPhoneNumber().getValue(), "09012345678");
  EXPECT_FALSE(user.canUpdate(now + hours(24 * 29)));
  EXPECT_TRUE(user.canUpdate(now + hours(24 * 30)));
}

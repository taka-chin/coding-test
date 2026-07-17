#include "../../database/database_user_repository.h"

#include <chrono>
#include <map>
#include <optional>
#include <string>

#include <gtest/gtest.h>

using namespace std::chrono;

TEST(DatabaseUserRepositoryTest, FindByIdReturnsUser) {
    Database database;

    std::map<std::string, std::string> userData;
    userData["id"] = "1";
    userData["name"] = "Taka";
    userData["email"] = "taka@example.com";
    userData["phone"] = "01012345678";
    userData["updated_at"] = "0";
    database.create_user(userData);

    DatabaseUserRepository repository(&database);

    std::optional<User> user = repository.findById("1");

    ASSERT_TRUE(user.has_value());
    EXPECT_EQ(user->getId(), 1);
    EXPECT_EQ(user->getName().getValue(), "Taka");
    EXPECT_EQ(user->getEmail().getValue(), "taka@example.com");
    EXPECT_EQ(user->getPhoneNumber().getValue(), "01012345678");
    EXPECT_EQ(user->getUpdatedAt(), system_clock::time_point{});
}

TEST(DatabaseUserRepositoryTest, FindByIdReturnsNulloptWhenUserDoesNotExist) {
    Database database;
    DatabaseUserRepository repository(&database);

    std::optional<User> user = repository.findById("999");

    EXPECT_FALSE(user.has_value());
}

TEST(DatabaseUserRepositoryTest, SaveUpdatesUser) {
    Database database;

    std::map<std::string, std::string> userData;
    userData["id"] = "1";
    userData["name"] = "Taka";
    userData["email"] = "taka@example.com";
    userData["phone"] = "01012345678";
    userData["updated_at"] = "0";
    database.create_user(userData);

    DatabaseUserRepository repository(&database);
    auto updatedAt = system_clock::from_time_t(100);
    User user(
        1,
        Name("Taro"),
        Email("taro@example.com"),
        PhoneNumber("09012345678"),
        updatedAt
    );

    repository.save(user);

    std::map<std::string, std::string>* savedUser = database.find_user_by_id("1");

    ASSERT_NE(savedUser, nullptr);
    EXPECT_EQ((*savedUser)["id"], "1");
    EXPECT_EQ((*savedUser)["name"], "Taro");
    EXPECT_EQ((*savedUser)["email"], "taro@example.com");
    EXPECT_EQ((*savedUser)["phone"], "09012345678");
    EXPECT_EQ((*savedUser)["updated_at"], "100");
}

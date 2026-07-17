#pragma once
#include <chrono>
#include <ctime>
#include <map>
#include <optional>
#include <string>

// Database層
#include "../usecase/user_repository.h"
#include "database.cpp"

class DatabaseUserRepository : public UserRepository {
 private:
  Database* database;

  std::chrono::system_clock::time_point parseTime(
      const std::string& timeString) const {
    if (timeString.empty()) {
      return std::chrono::system_clock::time_point{};
    }

    std::time_t time = static_cast<std::time_t>(std::stoll(timeString));
    return std::chrono::system_clock::from_time_t(time);
  }

  std::string formatTime(
      const std::chrono::system_clock::time_point& timePoint) const {
    std::time_t time = std::chrono::system_clock::to_time_t(timePoint);
    return std::to_string(time);
  }

 public:
  DatabaseUserRepository(Database* database) : database(database) {}

  std::optional<User> findById(const std::string& userId) override {
    auto userData = database->find_user_by_id(userId);

    if (userData == nullptr) {
      return std::nullopt;
    }

    return User(std::stoi((*userData)["id"]), Name((*userData)["name"]),
                Email((*userData)["email"]), PhoneNumber((*userData)["phone"]),
                parseTime((*userData)["updated_at"]));
  }

  void save(const User& user) override {
    std::map<std::string, std::string> userData;

    userData["id"] = std::to_string(user.getId());
    userData["name"] = user.getName().getValue();
    userData["email"] = user.getEmail().getValue();
    userData["phone"] = user.getPhoneNumber().getValue();
    userData["updated_at"] = formatTime(user.getUpdatedAt());

    database->update_user(userData);
  }
};

#pragma once
#include <optional>
#include <string>

//ドメイン層
#include "../domain/user.h"

class UserRepository {
 public:
  virtual std::optional<User> findById(const std::string& userId) = 0;
  virtual void save(const User& user) = 0;
  virtual ~UserRepository() = default;
};

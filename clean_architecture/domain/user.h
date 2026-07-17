#pragma once
#include <chrono>
#include <string>

// ドメイン層
#include "email.h"
#include "name.h"
#include "phone_number.h"

// ユーザーを表すクラス
// valueObjectを属性として持つ
// 更新日時を管理する
// 更新可能か判断する

class User {
 private:
  int id;
  Name name;
  Email email;
  PhoneNumber phoneNumber;
  std::chrono::system_clock::time_point updatedAt;

 public:
  User(int id, const Name& name, const Email& email,
       const PhoneNumber& phoneNumber,
       const std::chrono::system_clock::time_point& updatedAt)
      : id(id),
        name(name),
        email(email),
        phoneNumber(phoneNumber),
        updatedAt(updatedAt) {}

  int getId() const { return id; }

  const Name& getName() const { return name; }

  const Email& getEmail() const { return email; }

  const PhoneNumber& getPhoneNumber() const { return phoneNumber; }

  const std::chrono::system_clock::time_point& getUpdatedAt() const {
    return updatedAt;
  }

  void updateName(const Name& newName,
                  const std::chrono::system_clock::time_point& now) {
    name = newName;
    updatedAt = now;
  }

  void updateEmail(const Email& newEmail,
                   const std::chrono::system_clock::time_point& now) {
    email = newEmail;
    updatedAt = now;
  }

  void updatePhoneNumber(const PhoneNumber& newPhoneNumber,
                         const std::chrono::system_clock::time_point& now) {
    phoneNumber = newPhoneNumber;
    updatedAt = now;
  }

  bool canUpdate(const std::chrono::system_clock::time_point& now) const {
    auto diff = std::chrono::duration_cast<std::chrono::hours>(now - updatedAt);
    return diff.count() / 24 >= 30;
  }
};

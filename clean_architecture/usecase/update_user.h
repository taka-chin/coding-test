#pragma once
#include <optional>
#include <stdexcept>
#include <string>

// ドメイン層
#include "../domain/email.h"
#include "../domain/name.h"
#include "../domain/phone_number.h"
#include "../domain/user.h"
// ユースケース層
#include "notification_service.h"
#include "user_repository.h"

struct UpdateUserRequest {
  std::optional<std::string> name;
  std::optional<std::string> email;
  std::optional<std::string> phone;
};

class UpdateUser {
 private:
  UserRepository* userRepository;
  NotificationService* notificationService;

 public:
  UpdateUser(UserRepository* userRepository,
             NotificationService* notificationService)
      : userRepository(userRepository),
        notificationService(notificationService) {}

  // 1. user_id と更新内容を受け取る
  User execute(const std::string& userId, const UpdateUserRequest& request) {
    // 2. UserRepository から User を取得する
    std::optional<User> foundUser = userRepository->findById(userId);

    // 3.ドメインのルールで更新できるか確認する
    if (!foundUser.has_value()) {
      throw std::runtime_error("User not found");
    }

    User user = foundUser.value();
    auto now = std::chrono::system_clock::now();

    if (!user.canUpdate(now)) {
      throw std::runtime_error(
          "User information can only be updated once every 30 days");
    }
    if (request.name.has_value()) {
      Name newName(request.name.value());
      user.updateName(newName, now);
      notificationService->sendUpdateNotification(user.getEmail());
    }

    if (request.email.has_value()) {
      Email oldEmail = user.getEmail();
      Email newEmail(request.email.value());
      user.updateEmail(newEmail, now);
      notificationService->sendEmailChangeConfirmation(oldEmail);
      notificationService->sendUpdateNotification(user.getEmail());
    }

    if (request.phone.has_value()) {
      PhoneNumber newPhoneNumber(request.phone.value());
      user.updatePhoneNumber(newPhoneNumber, now);
    }

    userRepository->save(user);

    return user;
  }
};

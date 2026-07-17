#pragma once
#include "../domain/user.h"
#include "../domain/name.h"
#include "../domain/email.h"
#include "../domain/phone_number.h"
#include "user_repository.h"
#include "notification_service.h"

#include <optional>
#include <stdexcept>
#include <string>

struct UpdateUserRequest {
    std::optional<std::string> name;
    std::optional<std::string> email;
    std::optional<std::string> phone;
};

// ユーザー更新処理
// 1. user_id と更新内容を受け取る
// 2. UserRepository から User を取得する
// 3. ドメインのルールで更新できるか確認する
// 4. Name / Email / PhoneNumber を使って値を作る
// 5. User を更新する
// 6. UserRepository に保存する
// 7. 必要なら NotificationService に通知を依頼する

class UpdateUser {
private:
    UserRepository* userRepository;
    NotificationService* notificationService;

public:
    UpdateUser(
        UserRepository* userRepository,
        NotificationService* notificationService
    ) : userRepository(userRepository),
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
            throw std::runtime_error("User information can only be updated once every 30 days");
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

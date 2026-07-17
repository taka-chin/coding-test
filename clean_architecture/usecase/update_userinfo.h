#pragma once
#include "../domain/user.h"
#include "../domain/name.h"
#include "../domain/email.h"
#include "../domain/phone_number.h"
#include "user_repository.h"
#include "notification_service.h"

// ユーザー更新処理
// 1. user_id と更新内容を受け取る
// 2. UserRepository から User を取得する
// 3. ドメインのルールで更新できるか確認する
// 4. Name / Email / PhoneNumber を使って値を作る
// 5. User を更新する
// 6. UserRepository に保存する
// 7. 必要なら NotificationService に通知を依頼する

class UpdateUserInfo {
private:
    UserRepository* userRepository;
    NotificationService* notificationService;

public:
    UpdateUserInfo(
        UserRepository* userRepository,
        NotificationService* notificationService
    ) : userRepository(userRepository),
        notificationService(notificationService) {}
    
    UserInfo execute(const std::string& userId, const UpdateUserRequest& request) {
        // ここにユースケースの手順を書く
        User user = userRepository->findById(userId);
        if (!user.) {
            throw runtime_error("User not found");
        }
    }
};


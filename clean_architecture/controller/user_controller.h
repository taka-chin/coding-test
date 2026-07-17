#pragma once
#include <string>

// ユースケース層
#include "../usecase/update_user.h"

// ユーザー更新処理を行うコントローラー
// リクエストを受け取る
// usecaseを呼ぶ

class UserController {
 private:
  UpdateUser* updateUser;

 public:
  UserController(UpdateUser* updateUser) : updateUser(updateUser) {}

  // ユーザー情報を更新する
  User update_user(const std::string& userId,
                   const UpdateUserRequest& request) {
    return updateUser->execute(userId, request);
  }
};

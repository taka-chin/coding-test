#pragma once
#include "../domain/user.h"

#include <optional>
#include <string>

// 1. **ユーザー情報の更新**
//    - 名前、メールアドレス、電話番号を更新可能
//    - 名前は空文字列や数字のみは不可
//    - ユーザー情報の変更は30日に1回まで

class UserRepository {
public:
    virtual std::optional<User> findById(const std::string& userId) = 0;
    virtual void save(const User& user) = 0;
    virtual ~UserRepository() = default;
};

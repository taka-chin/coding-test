#pragma once
#include <optional>
#include <string>
#include "userinfo.h"

class UserRepository {
public:
    virtual std::optional<UserInfo> findById(const std::string& userId) = 0;
    virtual void save(const UserInfo& userInfo) = 0;
    virtual ~UserRepository() = default;
};
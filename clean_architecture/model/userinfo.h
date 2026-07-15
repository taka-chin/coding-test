#pragma once
#include <string>
#include <chrono>
#include <optional>

using namespace std;
using namespace std::chrono;

// ユーザー情報を表すクラス
class UserInfo {
  private:
    User user;
    string email;
    string phone;
    
  public:
    UserInfo() : user(), email(""), phone("") {}
    
    UserInfo(int id, const string& name, const string& email, const string& phone)
        : user(id,name), email(email), phone(phone) {}
};

// ユーザー更新リクエスト
struct UpdateUserRequest {
    optional<string> name;
    optional<string> email;
    optional<string> phone;
};


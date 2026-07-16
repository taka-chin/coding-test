#pragma once
#include <string>

using namespace std;

// ユーザーを表すクラス
class User {
 private:
  int id;
  string name;

 public:
  User() : id(0), name("") {}

  User(int id, const string& name) : id(id), name(name) {}
};

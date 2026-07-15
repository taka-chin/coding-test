#pragma once
#include <stdexcept>
#include <cctype>
#include <string>

class Email {
 private:
  std::string value;

 public:
  explicit Email(const std::string& value) : value(value) { validate(value); }

  const std::string& getValue() const { return value; }

 private:
  void validate(const std::string& value) {
    if (value.empty()) {
      throw std::invalid_argument("Email is empty");
    }

    if (value.find('@') == std::string::npos) {
      throw std::invalid_argument("Invaild email");
    }
  }
};

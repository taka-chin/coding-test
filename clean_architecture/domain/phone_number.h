#pragma once
#include <cctype>
#include <stdexcept>
#include <string>

class PhoneNumber {
 private:
  std::string value;

 public:
  explicit PhoneNumber(const std::string& value) : value(value) {
    validate(value);
  }

  const std::string& getValue() const { return value; }

 private:
  void validate(const std::string& value) {
    if (value.empty()) {
      throw std::invalid_argument("Phone number is empty");
    }

    if (value.length() != 10 && value.length() != 11) {
      throw std::invalid_argument("Invalid phone number");
    }
  }
};

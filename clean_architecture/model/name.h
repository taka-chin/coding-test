#pragma once
#include <cctype>
#include <stdexcept>
#include <string>

// name value object
class Name {
 private:
   std::string value;

 public:
  explicit Name(const std::string& value) : value(value) { validate(value); }

  const std::string& getValue() const { return value; }

 private:
  bool allDigit(const std::string& value) {
    for (char c : value)
      if (!isdigit(c)) return false;
    return true;
  };

  void validate(const std::string& value) {
    if (value.empty()) {
      throw std::invalid_argument("Name is empty");
    }

    if (allDigit(value)) {
      throw std::invalid_argument("Name cannot be only digit");
    }
  }
};

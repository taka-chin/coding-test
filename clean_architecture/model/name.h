#pragma once
#include <cctype>
#include <stdexcept>
#include <string>

using namespace std;

// name value object
class Name {
 private:
  string value;

 public:
  explicit Name(const string& value) : value(value) { validate(value); }

  const string& getValue() const { return value; }

 private:
  bool allDigit(const string& value) {
    for (char c : value)
      if (!isdigit(c)) return false;
    return true;
  };

  void validate(const string& value) {
    if (value.empty()) {
      throw invalid_argument("Name is empty");
    }

    if (allDigit(value)) {
      throw invalid_argument("Name cannot be only digit");
    }
  }
};

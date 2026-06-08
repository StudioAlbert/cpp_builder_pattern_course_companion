// 01 - A dedicated builder class with mutators (not yet chained).
//
// Each optional field gets a named setter, so call sites read as prose
// instead of a row of positional arguments. Setters return void here; the
// fluent (chained) version comes in example 03.

#include <iostream>
#include <string>
#include <utility>

class Person {
 public:
  Person(std::string name, int age, std::string email, bool premium)
      : name_(std::move(name)),
        age_(age),
        email_(std::move(email)),
        premium_(premium) {}

  void Print() const {
    std::cout << name_ << " (" << age_ << ") <" << email_ << ">"
              << (premium_ ? " [premium]" : "") << '\n';
  }

 private:
  std::string name_;
  int age_;
  std::string email_;
  bool premium_;
};

class PersonBuilder {
 public:
  explicit PersonBuilder(std::string name) : name_(std::move(name)) {}

  // Named mutators: the field is obvious at the call site.
  void SetAge(int age) { age_ = age; }
  void SetEmail(std::string email) { email_ = std::move(email); }
  void SetPremium(bool premium) { premium_ = premium; }

  Person Build() const { return Person{name_, age_, email_, premium_}; }

 private:
  std::string name_;
  int age_ = 0;            // defaults make every optional field truly optional
  std::string email_;
  bool premium_ = false;
};

int main() {
  PersonBuilder builder{"Bo"};
  builder.SetAge(25);
  builder.SetEmail("bo@example.com");
  builder.SetPremium(true);
  // No way to swap two flags by accident: each one is named.

  Person bo = builder.Build();
  bo.Print();
}

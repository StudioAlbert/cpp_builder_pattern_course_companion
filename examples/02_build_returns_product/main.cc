// 02 - build() returns the product, and is the single place to validate.
//
// An object only comes to life inside Build(), so that is the one place to
// check invariants. While no Build() has succeeded, you hold a *builder*,
// never a half-constructed Person.

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Person {
 public:
  Person(std::string name, int age, std::string email)
      : name_(std::move(name)), age_(age), email_(std::move(email)) {}

  void Print() const {
    std::cout << name_ << " (" << age_ << ") <" << email_ << ">\n";
  }

 private:
  std::string name_;
  int age_;
  std::string email_;
};

class PersonBuilder {
 public:
  explicit PersonBuilder(std::string name) : name_(std::move(name)) {}

  void SetAge(int age) { age_ = age; }
  void SetEmail(std::string email) { email_ = std::move(email); }

  Person Build() const {
    // Validate once, here, before any Person can exist.
    if (name_.empty()) throw std::invalid_argument("name is required");
    if (age_ < 0) throw std::invalid_argument("age cannot be negative");
    return Person{name_, age_, email_};
  }

 private:
  std::string name_;
  int age_ = 0;
  std::string email_;
};

int main() {
  PersonBuilder builder{"Ana"};
  builder.SetAge(30);
  builder.SetEmail("ana@example.com");
  Person ana = builder.Build();
  ana.Print();

  try {
    PersonBuilder bad{"Bo"};
    bad.SetAge(-1);
    Person bo = bad.Build();  // throws: an invalid state never becomes a Person
    bo.Print();
  } catch (const std::exception& e) {
    std::cout << "rejected: " << e.what() << '\n';
  }
}

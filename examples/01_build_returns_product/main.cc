// 01 - build() returns the product, and is the single place to validate.
//
// An object only comes to life inside Build(), so that is the one place to
// check invariants. While no Build() has succeeded, you hold a *builder*,
// never a half-constructed Person.

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

class Person {
  friend class PersonBuilder;

 public:
  void Print() const {
    std::cout << name_ << " (" << age_ << ") <" << email_ << ">\n";
  }

 private:
  std::string name_;
  int age_ = 0;            // defaults make every optional field truly optional
  std::string email_;
  bool premium_ = false;

};

class PersonBuilder {
  Person product_;

public:
  [[nodiscard]] Person Build() const {
    // Validate once, here, before any Person can exist.
    // if (name_.empty()) throw std::invalid_argument("name is required");
    if (product_.age_ < 0) throw std::invalid_argument("age cannot be negative");
    return product_;
  }

  void WithAge(int age) { product_.age_ = age; }
  void WithName(const std::string_view name) { product_.name_ = name; }
  void WithEmail(const std::string_view email) { product_.email_ = email; }
  void WithPremium(bool premium) { product_.premium_ = premium; }

};

int main() {

  Person Tom;
  Tom.Print();

  PersonBuilder builder;
  builder.WithName("Ana");
  builder.WithAge(30);
  Person ana = builder.Build();
  ana.Print();

  try {
    PersonBuilder bad;
    bad.WithAge(-1);
    Person bo = bad.Build();  // throws: an invalid state never becomes a Person
    bo.Print();
  } catch (const std::exception& e) {
    std::cout << "rejected: " << e.what() << '\n';
  }
}

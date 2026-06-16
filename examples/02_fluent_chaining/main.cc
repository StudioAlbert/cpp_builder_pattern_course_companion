// 02 - Fluent chaining: every mutator returns *this.
//
// Same embedded-product + friend design as example 01. The only change that
// turns the verbose API into a fluent one: each mutator returns a reference to
// the builder, so the whole configuration reads as a single expression.

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

class Person {
  friend class PersonBuilder;

 public:
  void Print() const {
    std::cout << name_ << " (" << age_ << ") <" << email_ << ">"
              << (premium_ ? " [premium]" : "") << '\n';
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
  // return *this; is the single line that makes the mutators chainable.
  PersonBuilder& WithName(std::string_view name) {
    product_.name_ = name;
    return *this;
  }
  PersonBuilder& WithAge(int age) {
    product_.age_ = age;
    return *this;
  }
  PersonBuilder& WithEmail(std::string_view email) {
    product_.email_ = email;
    return *this;
  }
  PersonBuilder& WithPremium(bool premium = true) {
    product_.premium_ = premium;
    return *this;
  }

  [[nodiscard]] Person Build() const {
    if (product_.name_.empty()) throw std::invalid_argument("name is required");
    return product_;
  }
};

int main() {
  Person ana = PersonBuilder{}
                   .WithName("Ana")
                   .WithAge(30)
                   .WithEmail("ana@example.com")
                   .WithPremium()
                   .Build();
  ana.Print();
}

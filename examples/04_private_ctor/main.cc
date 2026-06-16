// 04 - Make the builder the only path to a Person.
//
// Same embedded-product + friend design as example 01, now locked down: even
// the default constructor is private. No code can create a Person directly -
// not even an empty one. Every Person that exists has passed through Build().

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

class Person {
  friend class PersonBuilder;  // the only code allowed to create a Person

 public:
  void Print() const { std::cout << name_ << " (" << age_ << ")\n"; }

 private:
  // Private: only PersonBuilder may construct a Person (even a default one).
  Person() = default;

  std::string name_;
  int age_ = 0;
};

class PersonBuilder {
  // Default-constructing this member calls Person's private ctor - allowed
  // because PersonBuilder is a friend.
  Person product_;

 public:
  PersonBuilder& WithName(std::string_view name) {
    product_.name_ = name;
    return *this;
  }
  PersonBuilder& WithAge(int age) {
    product_.age_ = age;
    return *this;
  }

  [[nodiscard]] Person Build() const {
    if (product_.name_.empty()) throw std::invalid_argument("name is required");
    return product_;
  }
};

int main() {
  Person ana = PersonBuilder{}.WithName("Ana").WithAge(30).Build();
  ana.Print();

  // Person impossible;  // <- would not compile: default constructor is private
}

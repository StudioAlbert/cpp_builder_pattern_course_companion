// 05 - Make the builder the only path to a Person.
//
// The constructor is private and the builder is a friend, so no code can skip
// validation by constructing a Person directly. Every Person that exists has
// passed through Build().

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class PersonBuilder;  // forward declaration

class Person {
 public:
  void Print() const { std::cout << name_ << " (" << age_ << ")\n"; }

 private:
  // Private: only PersonBuilder may construct a Person.
  Person(std::string name, int age) : name_(std::move(name)), age_(age) {}
  friend class PersonBuilder;

  std::string name_;
  int age_;
};

class PersonBuilder {
 public:
  explicit PersonBuilder(std::string name) : name_(std::move(name)) {}
  PersonBuilder& WithAge(int age) {
    age_ = age;
    return *this;
  }

  Person Build() const {
    if (name_.empty()) throw std::invalid_argument("name is required");
    return Person{name_, age_};
  }

 private:
  std::string name_;
  int age_ = 0;
};

int main() {
  Person ana = PersonBuilder{"Ana"}.WithAge(30).Build();
  ana.Print();

  // Person impossible{"x", 1};  // <- would not compile: constructor is private
}

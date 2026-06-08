// 00 - The telescoping constructor problem.
//
// As Person grows, constructors multiply and call sites become a row of
// anonymous arguments. This file compiles cleanly - which is exactly the
// danger: the bug on line `c` below is invisible to the compiler.

#include <iostream>
#include <string>
#include <utility>

class Person {
 public:
  // The cascade of telescoping constructors: each delegates to the next.
  explicit Person(std::string name) : Person(std::move(name), 0) {}

  Person(std::string name, int age)
      : Person(std::move(name), age, "") {}

  Person(std::string name, int age, std::string email)
      : Person(std::move(name), age, std::move(email), false) {}

  Person(std::string name, int age, std::string email, bool premium)
      : Person(std::move(name), age, std::move(email), premium, false) {}

  Person(std::string name, int age, std::string email, bool premium,
         bool newsletter)
      : name_(std::move(name)),
        age_(age),
        email_(std::move(email)),
        premium_(premium),
        newsletter_(newsletter) {}

  void Print() const {
    std::cout << name_ << " (" << age_ << ") <" << email_ << ">"
              << (premium_ ? " [premium]" : "")
              << (newsletter_ ? " [newsletter]" : "") << '\n';
  }

 private:
  std::string name_;
  int age_;
  std::string email_;
  bool premium_;
  bool newsletter_;
};

int main() {
  // Readable enough...
  Person a{"Ana", 30};

  // ...but what do these trailing flags mean at the call site?
  Person b{"Bo", 25, "bo@example.com", true, false};

  // The two trailing bools are SWAPPED here (premium/newsletter). It still
  // compiles. That silent error is the bug class the Builder removes.
  Person c{"Cy", 40, "cy@example.com", false, true};

  a.Print();
  b.Print();
  c.Print();
}

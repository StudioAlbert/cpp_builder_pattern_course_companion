// 04 - When the product is polymorphic or heap-owned, build() can return a
// smart pointer.
//
// Prefer returning by value (RVO copies nothing). The unique_ptr is justified
// only when the caller must OWN a polymorphic object - not to do a free `new`.

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Person {
 public:
  explicit Person(std::string name) : name_(std::move(name)) {}
  virtual ~Person() = default;
  virtual void Print() const { std::cout << "Person " << name_ << '\n'; }

 protected:
  std::string name_;
};

class Character : public Person {
 public:
  Character(std::string name, int level)
      : Person(std::move(name)), level_(level) {}
  void Print() const override {
    std::cout << "Character " << name_ << " (lvl " << level_ << ")\n";
  }

 private:
  int level_;
};

class CharacterBuilder {
 public:
  explicit CharacterBuilder(std::string name) : name_(std::move(name)) {}
  CharacterBuilder& WithLevel(int level) {
    level_ = level;
    return *this;
  }

  // unique_ptr<Person> hands the caller ownership of a polymorphic product.
  std::unique_ptr<Person> Build() const {
    return std::make_unique<Character>(name_, level_);
  }

 private:
  std::string name_;
  int level_ = 1;
};

int main() {
  std::unique_ptr<Person> hero = CharacterBuilder{"Mage"}.WithLevel(7).Build();
  hero->Print();  // virtual dispatch: prints as a Character
}

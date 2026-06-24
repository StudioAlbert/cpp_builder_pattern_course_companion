#ifndef SANDWICH_SHOP_SOLUTION_SANDWICH_H_
#define SANDWICH_SHOP_SOLUTION_SANDWICH_H_

#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// SOLUTION - Sandwich is built only through SandwichBuilder.
//
// Embedded-product + friend design: the builder holds the Sandwich it is
// assembling and writes its private fields directly; Build() validates once and
// returns it.
class Sandwich {
 public:
  std::string Content() const {
    std::ostringstream os;
    os << (toasted_ ? "toasted " : "") << bread_ << " sandwich with "
       << filling_;
    if (cheese_) os << " + cheese";
    for (const auto& s : sauces_) os << ", " << s;
    os << (takeaway_ ? " (takeaway)" : " (eat in)");
    return os.str();
  }

 private:
  // Step 5: private default constructor - the builder is the only path.
  Sandwich() = default;
  friend class SandwichBuilder;

  std::string bread_;
  std::string filling_ = "plain";
  std::vector<std::string> sauces_;
  bool cheese_ = false;
  bool toasted_ = false;
  bool takeaway_ = false;
};

class SandwichBuilder {
 public:
  // Steps 1 + 4: named mutators write into the embedded product, chained.
  SandwichBuilder& WithBread(std::string_view bread) {
    sandwich_.bread_ = bread;
    return *this;
  }
  SandwichBuilder& WithFilling(std::string_view filling) {
    sandwich_.filling_ = filling;
    return *this;
  }
  SandwichBuilder& AddSauce(std::string_view sauce) {
    sandwich_.sauces_.emplace_back(sauce);
    return *this;
  }
  SandwichBuilder& WithCheese(bool cheese = true) {
    sandwich_.cheese_ = cheese;
    return *this;
  }
  SandwichBuilder& Toasted(bool toasted = true) {
    sandwich_.toasted_ = toasted;
    return *this;
  }
  SandwichBuilder& Takeaway(bool takeaway = true) {
    sandwich_.takeaway_ = takeaway;
    return *this;
  }

  // Steps 2 + 3: build() returns the product and is the single place to validate.
  Sandwich Build() const {
    if (sandwich_.bread_.empty())
      throw std::invalid_argument("bread is required");
    return sandwich_;
  }

  // Step 6: encapsulate recurring recipes (the Director role).
  static Sandwich Blt() {
    return SandwichBuilder{}
        .WithBread("baguette")
        .WithFilling("bacon")
        .WithFilling("tomato")
        .WithFilling("lettuce")
        .Build();
  }
  static Sandwich Vegan() {
    return SandwichBuilder{}
        .WithBread("wholewheat")
        .WithFilling("falafel")
        .AddSauce("hummus")
        .AddSauce("harissa")
        .Build();
  }

 private:
  Sandwich sandwich_;  // the product in progress
};

#endif  // SANDWICH_SHOP_SOLUTION_SANDWICH_H_

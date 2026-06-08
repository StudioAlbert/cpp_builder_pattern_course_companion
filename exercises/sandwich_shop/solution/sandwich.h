#ifndef SANDWICH_SHOP_SOLUTION_SANDWICH_H_
#define SANDWICH_SHOP_SOLUTION_SANDWICH_H_

#include <sstream>
#include <string>
#include <utility>
#include <vector>

// SOLUTION - Sandwich is now built only through SandwichBuilder.
class SandwichBuilder;  // forward declaration

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
  // Step 5: private constructor - the builder is the only path.
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
  explicit SandwichBuilder(std::string bread) {
    sandwich_.bread_ = std::move(bread);
  }

  // Steps 3 + 4: chained mutators grouped by topic.
  SandwichBuilder& WithFilling(std::string filling) {
    sandwich_.filling_ = std::move(filling);
    return *this;
  }
  SandwichBuilder& AddSauce(std::string sauce) {
    sandwich_.sauces_.push_back(std::move(sauce));
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

  // Step 2: build() returns the product (validate invariants here if needed).
  Sandwich Build() const { return sandwich_; }

  // Step 6: encapsulate recurring recipes (the Director role).
  static Sandwich Blt() {
    return SandwichBuilder{"baguette"}
        .WithFilling("bacon")
        .AddSauce("mayo")
        .WithCheese()
        .Toasted()
        .Build();
  }
  static Sandwich Vegan() {
    return SandwichBuilder{"wholewheat"}
        .WithFilling("falafel")
        .AddSauce("hummus")
        .AddSauce("harissa")
        .Build();
  }

 private:
  Sandwich sandwich_;
};

#endif  // SANDWICH_SHOP_SOLUTION_SANDWICH_H_

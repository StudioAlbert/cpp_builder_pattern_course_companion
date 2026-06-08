#ifndef SANDWICH_SHOP_SANDWICH_H_
#define SANDWICH_SHOP_SANDWICH_H_

#include <sstream>
#include <string>
#include <utility>
#include <vector>

// STARTING POINT - a telescoping-constructor Sandwich.
//
// Your job (see ../README.md) is to refactor this into a SandwichBuilder.
// Keep Content() working at every step: it is your test harness.
class Sandwich {
 public:
  explicit Sandwich(std::string bread) : Sandwich(std::move(bread), "plain") {}

  Sandwich(std::string bread, std::string filling)
      : Sandwich(std::move(bread), std::move(filling), {}) {}

  Sandwich(std::string bread, std::string filling,
           std::vector<std::string> sauces)
      : Sandwich(std::move(bread), std::move(filling), std::move(sauces),
                 false) {}

  Sandwich(std::string bread, std::string filling,
           std::vector<std::string> sauces, bool cheese)
      : Sandwich(std::move(bread), std::move(filling), std::move(sauces),
                 cheese, false) {}

  Sandwich(std::string bread, std::string filling,
           std::vector<std::string> sauces, bool cheese, bool toasted)
      : Sandwich(std::move(bread), std::move(filling), std::move(sauces),
                 cheese, toasted, false) {}

  Sandwich(std::string bread, std::string filling,
           std::vector<std::string> sauces, bool cheese, bool toasted,
           bool takeaway)
      : bread_(std::move(bread)),
        filling_(std::move(filling)),
        sauces_(std::move(sauces)),
        cheese_(cheese),
        toasted_(toasted),
        takeaway_(takeaway) {}

  // Lists the sandwich content. Use it to test your refactor.
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
  std::string bread_;
  std::string filling_;
  std::vector<std::string> sauces_;
  bool cheese_;
  bool toasted_;
  bool takeaway_;
};

#endif  // SANDWICH_SHOP_SANDWICH_H_

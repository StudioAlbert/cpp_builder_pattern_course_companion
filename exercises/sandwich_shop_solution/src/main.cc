#include <cassert>
#include <iostream>
#include <stdexcept>

#include "sandwich.h"

int main() {
  // Rebuilt with the fluent, named API (steps 1-4).
  Sandwich blt = SandwichBuilder{}
                     .WithBread("baguette")
                     .WithFilling("bacon")
                     .WithFilling("tomato")
                     .WithFilling("lettuce")
                     .Build();
  std::cout << blt.Content() << '\n';
  assert(blt.Content() ==
         "baguette sandwich with lettuce (eat in)");

  // Step 3: Build() validates - a sandwich with no bread is rejected.
  try {
    Sandwich none = SandwichBuilder{}.WithFilling("cheese").Build();
    (void)none;
    assert(false && "expected Build() to throw on empty bread");
  } catch (const std::invalid_argument& e) {
    std::cout << "rejected: " << e.what() << '\n';
  }

  // Step 6: Director recipes.
  Sandwich vegan = SandwichBuilder::Vegan();
  std::cout << vegan.Content() << '\n';
  assert(vegan.Content() ==
         "wholewheat sandwich with falafel, hummus, harissa (eat in)");

  // Sandwich impossible;  // <- would not compile: default constructor is private.

  std::cout << "all assertions passed\n";
  return 0;
}

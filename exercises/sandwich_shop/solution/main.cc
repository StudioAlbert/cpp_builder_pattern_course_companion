#include <cassert>
#include <iostream>

#include "sandwich.h"

int main() {
  // Rebuilt with the fluent, named API.
  Sandwich blt = SandwichBuilder{"baguette"}
                     .WithFilling("bacon")
                     .AddSauce("mayo")
                     .WithCheese()
                     .Toasted()
                     .Build();
  std::cout << blt.Content() << '\n';
  assert(blt.Content() ==
         "toasted baguette sandwich with bacon + cheese, mayo (eat in)");

  // Director recipes (step 6).
  Sandwich vegan = SandwichBuilder::Vegan();
  std::cout << vegan.Content() << '\n';
  assert(vegan.Content() ==
         "wholewheat sandwich with falafel, hummus, harissa (eat in)");

  // Sandwich impossible;  // <- would not compile: constructor is private.

  std::cout << "all assertions passed\n";
  return 0;
}

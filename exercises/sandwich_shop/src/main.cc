#include <iostream>

#include "sandwich.h"

int main() {
  // STARTING POINT: building a sandwich with the telescoping constructor.
  // Notice the row of anonymous arguments - that is what you will fix.
  Sandwich blt{"baguette", "bacon", {"mayo"}, true, true, false};
  std::cout << blt.Content() << '\n';

  // TODO (see ../README.md): refactor Sandwich behind a SandwichBuilder, then
  // rebuild this BLT with a fluent, named API, e.g.:
  //
  //   Sandwich blt = SandwichBuilder{"baguette"}
  //                      .WithFilling("bacon")
  //                      .AddSauce("mayo")
  //                      .WithCheese()
  //                      .Toasted()
  //                      .Build();
  //
  // The finished solution lives on the `solution/sandwich-shop` branch
  // (mirrored here under ./solution/ for convenience).
}

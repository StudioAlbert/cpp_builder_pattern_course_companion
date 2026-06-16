# Exercise — Sandwich shop

Refactor a telescoping-constructor `Sandwich` into a fluent **Builder**.

## Starting point

- `include/sandwich.h` — a `Sandwich` built only through a cascade of
  telescoping constructors. It exposes `Content()`, which lists the sandwich;
  use it as your test harness at every step.
- `src/main.cc` — builds a BLT the painful way and prints it.

Build and run the starting point:

```bash
cmake -S ../../.. -B build && cmake --build build
./build/exercises/sandwich_shop/sandwich_shop
```

## Your task

1. **A builder that writes into the product** — declare
   `friend class SandwichBuilder;` in `Sandwich`, then create a
   `SandwichBuilder` that *holds* the sandwich it is assembling
   (`Sandwich sandwich_;`). Give it named mutators (`WithBread`, `WithFilling`,
   `AddSauce`, `WithCheese`, `Toasted`, `Takeaway`) that write straight into
   `sandwich_`'s private fields. Assemble the BLT through these named calls
   instead of the telescoping constructor; verify with `Content()`.
2. **`Build()` returns the product** — add `Sandwich Build()` that returns the
   embedded `sandwich_`. The call site now gets its `Sandwich` from the builder.
3. **Validate in `Build()`** — make `Build()` the single place that checks
   invariants: throw `std::invalid_argument` if `bread` is empty. Confirm a
   builder with no bread is rejected.
4. **Chaining** — make each mutator `return *this;`, so the whole sandwich is
   configured in one fluent expression.
5. **Lock the only path** — give `Sandwich` a **private default constructor**
   (`Sandwich() = default;`). Because the builder is a `friend`, it stays the
   only way to create *any* `Sandwich` — even `Sandwich s;` won't compile.
6. **Director recipes** — encapsulate recurring builds behind static factory
   methods, each returning a ready-to-serve `Sandwich` by driving the fluent
   API. Implement at least:
   - `SandwichBuilder::Blt()` → bread `baguette`, filling `bacon`, sauce
     `mayo`, with cheese, toasted
     → `"toasted baguette sandwich with bacon + cheese, mayo (eat in)"`
   - `SandwichBuilder::Vegan()` → bread `wholewheat`, filling `falafel`,
     sauces `hummus` + `harissa`
     → `"wholewheat sandwich with falafel, hummus, harissa (eat in)"`

   A recipe is *just* a chain of mutators ending in `Build()` — that is the
   Director role. Bonus: add one of your own, e.g. a takeaway variant
   `ClubToGo()` reusing `.AddSauce(...)`, `.WithCheese()`, `.Takeaway()`.

## Target call site

```cpp
Sandwich blt = SandwichBuilder{}
                   .WithBread("baguette")
                   .WithFilling("bacon")
                   .AddSauce("mayo")
                   .WithCheese()
                   .Toasted()
                   .Build();
```

## Solution

The completed solution lives on the **`solution/sandwich-shop`** branch.
It is also mirrored as a sibling project
[`../sandwich_shop_solution/`](../sandwich_shop_solution/) for convenience
(`include/sandwich.h` + `src/main.cc`, the latter asserting the expected
`Content()` strings).

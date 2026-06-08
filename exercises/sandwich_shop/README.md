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

1. **Accessors** — replace the telescoping constructor with named setters;
   verify with `Content()`.
2. **`Build()`** — add a method that returns the finished `Sandwich` (and is
   the single place to validate, e.g. bread must not be empty).
3. **`SandwichBuilder`** — extract a dedicated builder class holding the
   mutators.
4. **Chaining** — make each mutator return `*this`, grouped by topic
   (`box` / takeaway, `bread`, `filling`, `sauces`, `cheese`, `toasted`).
5. **Private constructor** — make `Sandwich`'s constructor private and the
   builder a `friend`, so the builder is the only path to a `Sandwich`.
6. **Director recipes** — encapsulate recurring builds behind public methods,
   e.g. `SandwichBuilder::Blt()` and `SandwichBuilder::Vegan()`.

## Target call site

```cpp
Sandwich blt = SandwichBuilder{"baguette"}
                   .WithFilling("bacon")
                   .AddSauce("mayo")
                   .WithCheese()
                   .Toasted()
                   .Build();
```

## Solution

The completed solution lives on the **`solution/sandwich-shop`** branch.
It is also mirrored here under [`solution/`](solution/) for convenience
(`solution/sandwich.h` + `solution/main.cc`, the latter asserting the
expected `Content()` strings).

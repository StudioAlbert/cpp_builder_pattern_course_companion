# CPlusPlus_Course_Builder

Companion code for the **C++ Builder** lecture (SAE Geneve, C++ Advanced).
Each example is a small, self-contained program; the folder name matches the
lecture slide that references it.

> The lecture (`cpp_builder_lecture.md`) walks from the telescoping-constructor
> problem to a validated, fluent Builder. This repo is the runnable backing.

## Objectives

By the end you can:

- recognise the **telescoping constructor** smell and name its four pains;
- write a dedicated **builder class** with named mutators;
- make `build()` the single place that **validates** and returns the product;
- chain mutators into a **fluent** interface (`return *this;`);
- return a **`std::unique_ptr`** when (and only when) the product is polymorphic;
- lock construction behind a **private constructor + `friend`**;
- factor recurring builds into **Director** recipes.

## Prerequisites

- A **C++17** compiler (C++20 only for the designated-initializers aside in the
  lecture). Tested with GCC 13.
- **CMake ≥ 3.16**.
- Assumed background (earlier modules of the course):
  classes & constructors, overloading, references, `const`-correctness,
  `std::unique_ptr` / `std::make_unique`, basic inheritance & polymorphism.
- No third-party dependencies.

## Build & run

```bash
cmake -S . -B build
cmake --build build

# run any example, e.g.:
./build/examples/03_fluent_chaining/03_fluent_chaining
./build/exercises/sandwich_shop/sandwich_shop_solution
```

## Examples

| Folder | Lecture module | Shows |
|---|---|---|
| `examples/00_telescoping_constructor` | 1 | the problem: anonymous args, silent swap bug |
| `examples/01_builder_setters` | 3 | a dedicated builder with named (void) setters |
| `examples/02_build_returns_product` | 4 | `build()` returns the product **and** validates |
| `examples/03_fluent_chaining` | 5 | mutators return `*this` → fluent API |
| `examples/04_smart_pointer_product` | 6 | `build()` → `unique_ptr` for a polymorphic product |
| `examples/05_private_ctor` | 6 | private ctor + `friend` → builder is the only path |

## Exercise

`exercises/sandwich_shop/` — refactor a telescoping `Sandwich` into a Builder
in six steps. See its [README](C++%20Advanced/companions/CPlusPlus_Course_Builder/exercises/sandwich_shop/README.md).

- **`main`** branch: the starting point (telescoping constructor only).
- **`solution/sandwich-shop`** branch: the completed refactor. For convenience
  it is also mirrored under `exercises/sandwich_shop/solution/`, whose
  `main.cc` asserts the expected `Content()` output.

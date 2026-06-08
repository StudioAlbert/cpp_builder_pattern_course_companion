# Starter: students edit include/sandwich.h and src/main.cc.
add_executable(sandwich_shop src/main.cc)
target_include_directories(sandwich_shop PRIVATE include)

# Mirrored solution (also the `solution/sandwich-shop` branch).
add_executable(sandwich_shop_solution solution/main.cc)
target_include_directories(sandwich_shop_solution PRIVATE solution)

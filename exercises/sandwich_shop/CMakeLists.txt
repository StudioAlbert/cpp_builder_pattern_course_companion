# Exercice starter: students edit include/sandwich.h and src/main.cc.
add_executable(sandwich_shop src/main.cc)
target_include_directories(sandwich_shop PRIVATE include)

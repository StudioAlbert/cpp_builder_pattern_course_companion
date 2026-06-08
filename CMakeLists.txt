cmake_minimum_required(VERSION 3.16)
project(CPlusPlus_Course_Builder CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# One standalone executable per example folder (folder name == slide title).
add_subdirectory(examples/00_telescoping_constructor)
add_subdirectory(examples/01_builder_setters)
add_subdirectory(examples/02_build_returns_product)
add_subdirectory(examples/03_fluent_chaining)
add_subdirectory(examples/04_smart_pointer_product)
add_subdirectory(examples/05_private_ctor)

# Exercise: starter + mirrored solution.
add_subdirectory(exercises/sandwich_shop)

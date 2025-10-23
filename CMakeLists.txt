cmake_minimum_required(VERSION 3.15)
project(FiguresLab VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(figures_app
    main.cpp
    src/figure.cpp
    src/trapezoid.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/array.cpp
)

add_executable(figures_tests
    test/tests.cpp
    src/figure.cpp
    src/trapezoid.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/array.cpp
)

target_link_libraries(figures_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(figures_tests)

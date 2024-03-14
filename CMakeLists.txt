cmake_minimum_required(VERSION 3.21.2)
project(libzork)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -Werror -pedantic -std=c++20 -Wold-style-cast)

add_library(libzork SHARED)
set_target_properties(libzork PROPERTIES OUTPUT_NAME zork)

find_library(VAR yaml-cpp)

target_include_directories(libzork PUBLIC "include")
target_link_libraries(libzork PUBLIC yaml-cpp)

add_subdirectory(src)

# Create test executable

add_executable(zorkxplorer
               "zorkxplorer/src/main.cc"
               "zorkxplorer/src/options.cc")

target_include_directories(zorkxplorer PUBLIC "zorkxplorer/src")
target_link_libraries(zorkxplorer PUBLIC libzork)


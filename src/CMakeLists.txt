set(CMAKE_CXX_STANDARD 20)

target_include_directories(libzork PRIVATE ".")

add_subdirectory(runner)
add_subdirectory(store)
add_subdirectory(story)
add_subdirectory(vars)

target_sources(libzork PRIVATE exceptions.cc)

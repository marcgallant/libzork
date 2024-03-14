# libzork

Zork is a text-based adventure game first released in 1977.
This project has the objective to re-implement the latter in C++.

## Project Description

This project was made as my first C++ project during my third year (ING1) at EPITA after a week of learning this (wonderful) language. It was originaly a one day project but due to the difficulty of the tasks it was extends to another day.

## CMakeLists

- Compile the project and create a dynamic library libzork.so
```sh
cmake -B build
cmake --build build --target libzork
```
- Compile the project and create a zorkxplorer binary to play
```sh
cmake -B build
cmake --build build --target zorkxplorer
```
- Start the game with the Story in path/to/story.yml and default runner (Choice runner)
```
./zorkxplorer --story [ path/to/story.yml ]
```
- Start the game with Story in path/to/story.yml and smart runner
```
./zorkxplorer --story [ path/to/story.yml ] --smart [ path/to/synonyms.yml ]
```
- Start the game with Story in path/to/story.yml and HTML runner
```
./zorkxplorer --story [ path/to/story.yml ] --html [ directory ]
```

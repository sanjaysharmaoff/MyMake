# mymake

A minimal, custom C++ Makefile engine for Windows and Linux.

## Overview

`mymake` is a lightweight build tool that reads a Makefile and builds C++ projects by resolving dependencies and executing build commands in the correct order. It is designed to mimic the essential behavior of GNU Make, with a focus on simplicity and cross-platform compatibility.

## Features

- Parses Makefile-style dependency rules
- Supports both tab and 4+ spaces for command lines
- Full topological sort for correct build order
- Detects out-of-date targets based on file timestamps
- Windows and Linux compatible (clean command adapts automatically)
- Minimal dependencies, easy to understand and extend

## Usage

```
Usage: mymake <Makefile> [target]
```

- `<Makefile>`: Path to your Makefile (e.g., `Makefile.txt`)
- `[target]`: (Optional) Target to build (default: `all`)

### Example

Suppose you have a `Makefile.txt` like this:

```
all: app
app: main.o lib.o
	g++ -o app main.o lib.o
main.o: main.cpp
	g++ -c main.cpp
lib.o: lib.cpp
	g++ -c lib.cpp
clean:
	del /Q *.o app 2>nul
```

To build the default target:

```
./mymake Makefile.txt
```

To build a specific target:

```
./mymake Makefile.txt lib.o
```

To clean build artifacts:

```
./mymake Makefile.txt clean
```

## How It Works

- Parses the Makefile and builds a dependency graph
- Performs a topological sort to determine build order
- Checks timestamps to rebuild only out-of-date targets
- Executes commands for each target as needed

## Project Structure

- `src/` — Source code for the build engine
- `Makefile.txt` — Example Makefile for this project
- `main.cpp`, `lib.cpp`, `util.cpp`, `common.h` — Example source files for building

## Building mymake

You can build `mymake` using any C++17 compiler. For example, with g++:

```
g++ -std=c++17 -o mymake src/*.cpp
```

## License

This project is released under the MIT License.

# Advent of Code Solutions

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

```
 ________  ________  ________
|\   __  \|\   __  \|\   ____\
\ \  \|\  \ \  \|\  \ \  \___|
 \ \   __  \ \  \\\  \ \  \
  \ \  \ \  \ \  \\\  \ \  \____
   \ \__\ \__\ \_______\ \_______\
    \|__|\|__|\|_______|\|_______|
```

A collection of my solutions to [Advent of Code](https://adventofcode.com/) challenges, organized by year, day, and part. This project features a modern C++20 codebase and an interactive terminal UI for exploring and running solutions.

---

## Table of Contents

- [Prerequisites](#prerequisites)
- [Setup & Usage](#setup--usage)
- [Adding New Solutions](#adding-new-solutions)
- [Contribution](#contribution)
- [Acknowledgements](#acknowledgements)

---

## Prerequisites

- C++20 compatible compiler (e.g., `g++`, `clang++`)
- [CMake](https://cmake.org/) (version 3.14+ recommended)
- Unix-like environment (Linux or macOS)
- Internet connection (for first-time FTXUI dependency fetch)

---

## Setup & Usage

### 1. Clone this repository

```bash
git clone https://github.com/Shayan1503/AoC.git
cd AoC
```

### 2. Build the Project

Using CMake (recommended):

```bash
cmake -S . -B build
cmake --build build
```

Or, compile directly (for quick testing):

```bash
g++ src/main.cpp -o aoc_runner -std=c++20
```

### 3. Run the Solution Navigator

```bash
cd build
./aoc
# or, if compiled directly:
./aoc_runner
```

### 4. Using the UI

- Select the **year**, **day**, and **part** using the menu.
- Press **Verify Selection** to run the chosen solution.
- View the result and execution time in the terminal.

---

## Adding New Solutions

1. Create a new header (e.g. [part1.hpp](./src/solutions/2023/Day1/par1.hpp)) in the appropriate `DayX` folder.
1. Inherit from the `Solution` base class and implement the `solve()` method.
1. Register your solution using the `REGISTER_SOLUTION` macro.
1. Include your header in [utils/all_solutions.hpp](./src/utils/all_solutions.hpp).

---

## Contribution

Contributions are welcome! To contribute:

1. **Fork** this repository.
1. **Create a branch** for your feature or fix.
1. **Add your solution** or improvement, following the project structure.
1. **Test** your changes.
1. **Open a Pull Request** with a clear description of your changes.
   If you have suggestions, bug reports, or want to discuss ideas, feel free to open an issue.

---

## Acknowledgements

- [Advent of Code](https://adventofcode.com/) by Eric Wastl
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI) for the terminal UI

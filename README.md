# Advent of Code Solutions

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A collection of my solutions to [Advent of Code](https://adventofcode.com/) challenges across different years.

```
 ________  ________  ________
|\   __  \|\   __  \|\   ____\
\ \  \|\  \ \  \|\  \ \  \___|
 \ \   __  \ \  \\\  \ \  \
  \ \  \ \  \ \  \\\  \ \  \____
   \ \__\ \__\ \_______\ \_______\
    \|__|\|__|\|_______|\|_______| by Shayan1503
```

## Prerequisites

- C++20 compiler (g++ or clang++)
- Standard C++ libraries
- Unix-like environment (Linux or macOS)

## Setup

1. Clone this repository
   ```bash
   git clone https://github.com/Shayan1503/AoC.git
   cd AoC
   ```

2. Compile the main runner
   ```bash
   g++ -std=c++20 main.cpp -o aoc_runner
   ```

3. Run the solution navigator
   ```bash
   ./aoc_runner
   ```

## Project Structure

```
.
├── main.cpp                 # Main navigation interface
├── 2023                     # Solutions organized by year
│   ├── Day1
│   │   ├── part1.cpp        # Solution for Day 1, Part 1
│   │   └── part2.cpp        # Solution for Day 1, Part 2
│   ├── Day2
│   │   ├── part1.cpp
│   │   └── part2.cpp
│   └── ...
├── 2022
│   └── ...
└── ...
```

## Usage

1. Start the navigator by running `./aoc_runner`
2. Enter the year, day, and part number when prompted
3. The solution will be compiled and executed automatically
4. Results will be displayed in the terminal
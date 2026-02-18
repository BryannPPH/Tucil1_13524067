# Linkedin's Queens Solver

## Description
A desktop application that solves a modified N-Queens problem with color and adjacency constraints using both pure brute-force and optimized backtracking approaches. This solver follows the generic rule of the puzzle queens.
The application is built using Python (Tkinter) for the graphical interface and a C++ backend solver for high-performance computation. The solving process is visualized live with adaptive update control for smooth rendering.

## Features
- Two algorithms available
    - Pure Brute Force (exhaustive search)
    - Optimized Backtracking (with pruning)
- Live solving visualization
- Displays execution time and number of cases checked
- Board file input, load custom board configurations from .txt files
- Save the solution to .txt and .png
- Smooth and responsive GUI

## Project Structure
```
├── assets/
│   └── ...
├── docs/
│   └── Laporan_Tucil1.pdf
├── src/
│   ├── app.py
│   ├── bindings.cpp
│   ├── board.cpp
│   ├── board.h
│   ├── queens.cpp
│   ├── queens.h
│   ├── queensSolver.cpp
│   └── queensSolver.h
├── test/
│   ├── input/
│   │   └── ...
│   └── output/
│       └── ...
├── CMakeList.txt
├── doc/
└── README.md
```

## System Requirements
- Python: Version 3.8 or higher
- C++ Compiler (with C++17 support):
    - MinGW / GCC 9+ (Windows / Linux)
    - Clang (macOS)
- CMake: Version 3.15 or higher

## Installation
- Clone the Repository
```bash
git clone https://github.com/BryannPPH/Tucil1_13524067.git
cd Tucil1_13524067
```

- Build the C++ Backend
The solver must be compiled into a shared library before running the GUI.
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
```

- Running the Application
## MacOS / Linux
```bash
PYTHONPATH=build python3 src/app.py
```
## Windows
```bash
set PYTHONPATH=build
python src/app.py
```

## Authors
| Nama                           | NIM      |
| ------------------------------ | -------- |
| Bryan Pratama Putra Hendra     | 13524067 |
# CADEX C++ Assignment — 3D Geometric Curves

Implementation of a small C++ program supporting three types of 3D parametric curves: circles, ellipses, and 3D helixes.

## Features

- **Circle** — planar curve in XoY, defined by radius
- **Ellipse** — planar curve in XoY, defined by two radii (Rx, Ry)
- **Helix** — spatial curve, defined by radius and step (displacement along Z per full revolution)

Each curve supports:
- `getPoint3D(t)` — returns a 3D point on the curve at parameter `t`
- `getDerivative(t)` — returns the first derivative (3D vector) at parameter `t`

## Project Structure

```
.
├── Curves.h       # Class declarations (library API)
├── Curves.cpp     # Class implementations (library)
├── main.cpp       # Executable entry point
└── CMakeLists.txt # Build configuration
```

The implementation is split into a **shared library** (`libcurves`) and an **executable** (`cadex_curves`), as per optional requirement 7.

## Build Instructions

Requires: CMake 3.10+, C++17 compiler (gcc / clang / MSVC)

```bash
mkdir build
cd build
cmake ..
make
./cadex_curves
```

On Windows (Visual Studio): open the folder via *File → Open → CMake*, then build and run from the IDE.

## What the program does

1. Populates a container with randomly generated curves of all three types
2. Prints 3D points and derivatives for all curves at `t = PI/4`
3. Populates a second container with circles only (shared pointers, not clones)
4. Sorts circles by radius in ascending order
5. Computes the total sum of all circles' radii

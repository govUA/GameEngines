# Assignment 1 - Toolchain setup

## Development Environment

* **Code Editor / IDE**: CLion.
* **Compiler**: MinGW-w64 for Windows.
* **Build System**: CMake.
* **Language Standard**: C++20.
* **Version Control**: Git.

## Frameworks and Libraries

The following frameworks and libraries were selected and integrated into the project using CMake (see `CMakeLists.txt`):

* **GLM**: A header-only C++ maths library allowing vector and matrix operations.
* **SDL2**: A cross-platform library for handling window creation, rendering and input.
* **SDL2_ttf**: An SDL extension library for TrueType font rendering.

## Showcase Program

The showcase program (`main.cpp`) demonstrates:

1. **Math Operation**: Vector addition using GLM (`vec1 + vec2`).
2. **Rendering Framework**: SDL2 initialises a window and renderer.
3. **Font Rendering**: SDL2_ttf to load a font and render yellow text *"Windows XP gang"* onto blue screen inside the window.
4. **Event Handling**: Program maintains a running loop until user closes the window.
5. **Cleanup**: Proper resource management and shutdown of SDL subsystems.

Toolchain, math library, rendering framework and font rendering extension should all be correctly configured and functional.

## Conclusion

The environment has been established with a working toolchain, framework and version control. The test program verifies integration of math operations and rendering, as was requested in the requirement list for this assignment.

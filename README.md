# Computer Graphics Project

A Linux C++20 OpenGL project for computer graphics coursework. The `shapes`
application opens an 800 × 600 window and renders a colored triangle, circle,
and square. Press **Esc** to close the window.

## Project layout

| Path | Purpose |
| --- | --- |
| `CMakeLists.txt` | Root CMake project configuration and build entry point. |
| `shapes/` | The example application. Its `CMakeLists.txt` defines the `shapes` executable; `src/` contains the program, `include/` contains application headers, and `assets/shaders/` contains the GLSL shaders. |
| `third_party/` | CMake targets and bundled dependencies used by the project. |
| `third_party/glad/` | GLAD OpenGL function loader. |
| `third_party/glfw/` | GLFW headers and prebuilt static library for creating a window and handling input. |
| `third_party/glm/` | GLM headers for vector and matrix math. |
| `third_party/stbi/` | stb_image header for image loading. |

GLM and stb_image are available as CMake include targets but are not currently
used by the application.

## Requirements

- Linux with a working desktop session and graphics drivers that can create an
  OpenGL 4.6 core-profile context.
- CMake 3.10 or newer.
- A C and C++ compiler (the project uses C++20).
- OpenGL development libraries.

On Debian or Ubuntu, install the common build tools and OpenGL development
package with:

```sh
sudo apt update
sudo apt install build-essential cmake libgl1-mesa-dev
```

The GLFW archive and the other dependency headers are already included in
`third_party/`, so a separate GLFW installation is not needed.

## Configure, build, and run

Run these commands from the project root:

```sh
cmake -S . -B build
cmake --build build
./build/shapes/shapes
```

The program opens a window titled **Triangle** and displays the shapes. Press
**Esc** to close it.

## Troubleshooting

- If CMake cannot find OpenGL, install your distribution's OpenGL development
  package and configure again.
- If the application reports that it failed to create the GLFW window, check
  that you are running inside a graphical desktop session and that your GPU
  driver supports OpenGL 4.6 core.

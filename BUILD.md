# Build and run

## Requirements

- CMake 3.16 or later
- A C++20 compiler
- SFML 3 with the Graphics, Window and System components
- libconfig++ and pkg-config

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

The CMake project writes the `raytracer` binary to the repository root.

## Run

```sh
./raytracer scenes/showcase.cfg
```

The renderer opens an SFML preview window. Close the window to save the image as
`output.ppm` in the current directory.

Other included scenes:

```sh
./raytracer scenes/primitives.cfg
./raytracer scenes/materials.cfg
./raytracer scenes/tangle.cfg
./raytracer scenes/reflections.cfg
./raytracer scenes/lighting.cfg
./raytracer scenes/antialiasing-on.cfg
```

The scenes use the libconfig syntax; see [`scenes/README.md`](scenes/README.md)
for a short overview.

# music-visualizer

## About

This is a fairly simple cross-platform system for visualizing music using a [Fourier Transform](https://en.wikipedia.org/wiki/Fourier_transform). Mostly a fun little project for me to learn OpenGL and modern C++. Currently very early in development and very much a bowl of spaghetti code.

### My plans include:

 - [x] Build a renderer
 - [x] Create transform data display
 - [ ] Hook into audio streams (currently only random noise)
 - [ ] ?

## Getting started

### Build the repository

**If you are having trouble please try updating the submodules with `git submodule update`**

Before you build make sure you have the following:
- [CMake](https://cmake.org/) (v3.8 or newer)
- A build system for C++ 20 like Visual Studio, Make, [Ninja](https://ninja-build.org/), etc.
- Up-to-date graphics drivers for your system (preferred)

To build
1. Open a terminal and navigate to the repository directory
1. Find the correct generator for you build system by running `cmake --help` and scrolling down to the list of generators. For this example we will be using `Ninja`.
    - If using Ninja you can run `cmake --list-presets` to find any available presets to run with `cmake --preset <preset>`. `<output_dir>` will be `out/build/<preset>`. 
1. Otherwise run `cmake -B <output_dir> -G <generator>`
    - if specifying an output dir make sure it exists by running `mkdir <output_dir>` first
    - `<output_dir` is where the build files will go if you don't want to clutter up the root dir
    - `<generator>` is the generator found in step 2
    - Example: `cmake -B .\out\ -G Ninja`
1. Move to your `<output_dir>` with `cd <output_dir>` or equivalent
1. Run your build tools and then the resulting executable
    - Example: `Ninja` then run `<output_dir>/MusicVisualizer/MusicVisualizer.exe`

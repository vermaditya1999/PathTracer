# Path Tracer

### Features
- Unbiased Monte Carlo Path tracer.
- Lambertian, Dielectric and Mirror BRDF.
- Antialiasing via jittered supersampling.

### Build Instructions
The project uses CMake for generating build files. The minimum version required us CMake 3.5
For building the project:
- Clone the repository (or download the zip file)  
  ```
  git clone https://github.com/vermaditya1999/PathTracer.git
  ```
- With CMake it generally recommended to create an [out-of-source build](https://gitlab.kitware.com/cmake/community/wikis/FAQ#out-of-source-build-trees), and so do we. Create a folder `build` in the root directory 
  ```
  cd PathTracer
  mkdir build
  cd build
  ```
- By default, CMake will build in Release mode (optimized). To build in Debug mode add the `-DCMAKE_BUILD_MODE` flag with the `cmake` command.
  ```
  cmake ..
  ```
- Now run `make` to create the executable  
  ```
  make
  ```
An executable `PathTracer` should be created in the `build` directory.

### Running the program
Run the program using `./PathTracer` while being in the build directory.
The scene will be rendered as an `image.ppm` file in the build directory.

### Setting the parameters
- __Antialiasing__: Change `jg_size` variable in the function `void RealisticRenderer::render(Scene scene)` in file `src/RealisticRenderer.cpp` 
- __Samples per pixel__: Change `n_samples` variable in the function `void RealisticRenderer::render(Scene scene)` in file `src/RealisticRenderer.cpp`

### Changing the scene
There are two sample scenes provided in the code:
- Luminaire on the top of diffused ball. [SCENE ID = 1]
- Cornell Box. [SCENE ID = 0]

The scenes can be switched by changing the `scene_id` variable in `src/main.cpp`.

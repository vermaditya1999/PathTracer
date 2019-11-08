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

### Running the program

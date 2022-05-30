# the target operating system
set(CMAKE_SYSTEM_NAME Linux)

# the compilers to use
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# Don't run the linker on compiler check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# the root path of the compiler toolchain
set(CMAKE_FIND_ROOT_PATH "C:/Programs/gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf")

# Search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# For libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
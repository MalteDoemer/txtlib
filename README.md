# TXT Lib

### Tools you need

- [cmake](https://cmake.org/download/)
- [ninja](https://github.com/ninja-build/ninja/releases)
- arm-linux-gnueabihf-gcc ([windows](https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf.tar.xz)) ([linux](https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf.tar.xz))
- [.Net 6](https://dotnet.microsoft.com/en-us/download/dotnet/6.0)

### Build the TXT App

Create a build directory:

```mkdir build```

Run cmake to initialize the build files:

```cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build```

Switch to the build directory:

```cd build```

Run ninja to build the project:

```ninja```

Then copy the resulting binary to the TXT over ssh:

```ninja upload```

If you are using WLAN or Bluetooth not USB then you need to define the TXT_IP variable before running cmake
```cmake -DTXT_IP=192.168.8.2 -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build```

### References

Documentation of the Fischertechnik libraries: https://github.com/fischertechnik/txt_demo_c_download
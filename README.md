# TXT Lib

This is a library and an example application that interacts with the Fischertechnik ROBOTICS TXT controller.

## Tools you need

- [cmake](https://cmake.org/download/)
- [ninja](https://github.com/ninja-build/ninja/releases)
- arm-linux-gnueabihf-gcc ([windows](https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-i686-mingw32_arm-linux-gnueabihf.tar.xz)) ([linux](https://releases.linaro.org/components/toolchain/binaries/7.2-2017.11/arm-linux-gnueabihf/gcc-linaro-7.2.1-2017.11-x86_64_arm-linux-gnueabihf.tar.xz))

## Building the TXT App

Create a build directory:

```mkdir build```

Run cmake to initialize the build files:

```cmake -D CMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build```

Change to the build directory:

```cd build```

Run ninja to build the project:

```ninja```

Then copy the resulting binary to the TXT over ssh:

```ninja upload```

### Specifiying the IP address

If you are using WLAN or Bluetooth not USB to connect to the TXT you will need to define the TXT_IP variable before running cmake:

```cmake -D TXT_IP=192.168.8.2 -D CMAKE_TOOLCHAIN_FILE=toolchain.cmake -G Ninja  -S . -B build```

The IP's are specified in [this](https://github.com/fischertechnik/txt_demo_c_download/blob/master/HowToUseTxtWeb.md) document.

## References

Documentation of the Fischertechnik TXT controller and the libraries: https://github.com/fischertechnik/txt_demo_c_download

## License

Licensed under the MIT license ([LICENSE](LICENSE) or http://opensource.org/licenses/MIT)
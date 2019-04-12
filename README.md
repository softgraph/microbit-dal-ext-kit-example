
# microbit-dal-ext-kit-example

An example for using `microbit-dal-ext-kit`

### Structure

<table>
<tr><td align="center">`microbit-dal-ext-kit-example`</td></tr>
<tr><td align="center">`microbit-dal-ext-kit`</td></tr>
<tr><td align="center">`microbit` and `microbit-dal` <br> (micro:bit runtime)</td></tr>
<tr><td align="center">Arm Mbed OS</td></tr>
<tr><td align="center">BBC micro:bit device</td></tr>
<tr><td align="center">Extension board and/or Hardware module (optional)</td></tr>
<tr><td align="center">Inputs/Outputs (optional)</td></tr>
</table>

### Module Outlines

+ `microbit-dal-ext-kit-example` <br>
	An example for using `microbit-dal-ext-kit`

+ `microbit-dal-ext-kit` <br>
	The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime) with or without `microbit`

+ `microbit-dal` <br>
	The core set of drivers, mechanisms and types that make up the micro:bit runtime.

+ `microbit` <br>
	A collection of the commonly used components of the micro:bit runtime with a standard configuration, to provide an easy to use interface for programming the micro:bit in C/C++.
	
## Install, Build and Run

### Development Tools

+ To install offline development tools, follow the instructions at [Yotta</b> (lancaster-university.github.io)](https://lancaster-university.github.io/microbit-docs/offline-toolchains).

### Build Target

+ Before building, you need to set the build target to the micro:bit platform. Run the following yotta command (`yotta` or `yt`) at the project root of `microbit-dal-ext-kit-example`.

		$ yt target bbc-microbit-classic-gcc
		...
		$ ls yotta_targets
		bbc-microbit-classic-gcc	mbed-gcc

	The files required for the target are automatically downloaded to `yotta_targets` directory. Also, the target name is recorded in `.yotta.json` file in the project root.

### Install Required Modules

+ To install the required modules, run the following yotta command at the project root of `microbit-dal-ext-kit-example`.

		$ yt install
		...
		$ ls yotta_modules
		ble  ble-nrf51822  mbed-classic  microbit  microbit-dal  microbit-dal-ext-kit  nrf51-sdk

	The files required for the modules are automatically downloaded to `yotta_modules` directory.


+ After installing `microbit-dal-ext-kit`, run Doxygen again to generate the documentation including both `microbit-dal-ext-kit-example` and `microbit-dal-ext-kit`.

### Build Modules

+ To build all modules and the executable, run the following yotta command at the project root of `microbit-dal-ext-kit-example`.

		$ yt build
		...
		$ ls build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex
		build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex

	The files are built in `build/bbc-microbit-classic-gcc` directory.

+ To flash the executable file to your micro:bit device, just copy the `combined.hex` file to the device. Here is an example for Terminal on Mac OS.

		$ cp build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex /Volumes/MICROBIT

## Documentation

Run [Doxygen (doxygen.nl)](http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.

The documentation for both `microbit-dal-ext-kit-example` and `microbit-dal-ext-kit` are generated if you run Doxygen after installing the required modules described above.

## License

MIT

## Dependencies

Module                 | URL
---------------------- | ---
`microbit-dal-ext-kit` | https://github.com/softgraph/microbit-dal-ext-kit

## External Resources

### Build Environment

+ [Offline development tools (lancaster-university.github.io)](https://lancaster-university.github.io/microbit-docs/offline-toolchains/)

### micro:bit runtime

+ [Introduction (lancaster-university.github.io)](https://lancaster-university.github.io/microbit-docs/)

### Arm Mbed OS

+ [BBC micro:bit (os.mbed.com)](https://os.mbed.com/platforms/Microbit/)

### BBC micro:bit

+ [Micro:bit Educational Foundation (microbit.org)](https://microbit.org)

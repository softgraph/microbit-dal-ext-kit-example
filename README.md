
# microbit-dal-ext-kit-example

An example for using `microbit-dal-ext-kit`

### Structure

<table>
<tr><td align="center"><code>microbit-dal-ext-kit-example</code></td></tr>
<tr><td align="center"><code>microbit-dal-ext-kit</code></td></tr>
<tr><td align="center"><code>microbit</code> and <code>microbit-dal</code> <br> (micro:bit runtime)</td></tr>
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

### Install Development Tools

+ To install offline development tools, follow the instructions at [Yotta</b> (lancaster-university.github.io)](https://lancaster-university.github.io/microbit-docs/offline-toolchains).

### Install Required Targets and Modules

+ Before starting the build, run the following yotta command (`yotta` or `yt`) at the project root of `microbit-dal-ext-kit-example`.

		$ yt install
		...

+ The target files required for the module are automatically downloaded to `yotta_targets` directory as below.

		$ ls yotta_targets
		bbc-microbit-classic-gcc  mbed-gcc

+ The other module files required for the module are automatically downloaded to `yotta_modules` directory as below.

		$ ls yotta_modules
		ble  ble-nrf51822  mbed-classic  microbit  microbit-dal  microbit-dal-ext-kit  nrf51-sdk

### Build Executable

+ To build all required modules and the executable, run the following yotta command at the project root of `microbit-dal-ext-kit-example`.

		$ yt build
		...

+ The files are built in `build/bbc-microbit-classic-gcc` directory as below.

		$ ls build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex
		build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex

### Run Executable

+ To flash the executable file to your micro:bit device, just copy the `combined.hex` file to the device mounted as a usb storage. Here is an example for Terminal on Mac OS.

		$ cp build/bbc-microbit-classic-gcc/source/microbit-dal-ext-kit-example-combined.hex /Volumes/MICROBIT

+ The executable starts automatically after it has been copied into the device.
+ The scrolling '`--`' characters are shown on the device's 5 x 5 LEDs display. Then, '`T`' is shown as a candidate for the App Mode.
+ By default, the following candidates are available for the App Mode. Press A button to switch among these modes and press B button to select the mode.
	+ App Mode '`T`' (Generic Transmitter mode using micro:bit only)
	+ App Mode '`R`' (Generic Receiver mode using micro:bit only)
	+ App Mode '`Z`' (Zip Halo mode using micro:bit and Kitronik's Zip Halo board)

## Documentation

Run [Doxygen (doxygen.nl)](http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.

The generated document contains both `microbit-dal-ext-kit-example` and `microbit-dal-ext-kit`, if `microbit-dal-ext-kit` has been installed to `yotta_modules` directory.

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

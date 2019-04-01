/// Doxygen Topics
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

/**	@page	microbit-dal-ext-kit-example	microbit-dal-ext-kit-example
		- @subpage	AppKit_AppModes
		- @subpage	AppKit_Headers
*/

/**	@page	AppKit_AppModes	App Modes - the set of components specific to a micro:bit setup and usage

	@section	AppKit_AppModes_1	App Mode for ElecFreaks' Joystick:bit
		The following App Mode is automatically selected if Joystick:bit board is connected to the micro:bit.
		- App Mode 'J' (`appMode::kJoystickController`) <br>
			`AppModeJoystickController` provides a transmitter using ElecFreaks' Joystick:bit.
		.

	@section	AppKit_AppModes_2	App Mode for SparkFun's moto:bit
		The following App Mode is automatically selected if moto:bit board is connected to the micro:bit.
		- App Mode 'M' (`appMode::kMotors`) <br>
			`AppModeMotors` provides a receiver using SparkFun's moto:bit.
		.

	@section	AppKit_AppModes_3	App Modes for Waveshare's Mini Piano Module
		The following App Modes are available if Mini Piano Module is connected to the micro:bit.
		- App Mode 'P' (`appMode::kPianoPlayer`) <br>
			`AppModePianoPlayer provides a stand-alone piano player using Waveshare's Mini Piano Module
		- App Mode 'K' (`appMode::kPianoKeyController`) <br>
			`AppModePianoKeyController` provides a transmitter using Waveshare's Mini Piano Module.
		.

	@section	AppKit_AppModes_4	App Modes for Kitronik's Zip Halo with a buzzer connected to port P2
		The following App Mode is automatically selected if a buzzer is connected to port P2 on the micro:bit.
		- App Mode 'O' (`appMode::kNeoPixelRing`) <br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo with a Buzzer.
		.

	@section	AppKit_AppModes_5	App Modes for no auto-detection
		The following App Modes are available if all of detections above are failed.
		- App Mode 'R' (`appMode::kGenericReceiver`) <br>
			`AppModeGenericReceiver` provides a generic receiver using micro:bit only.
		- App Mode 'T' (`appMode::kGenericTransmitter`) <br>
			AppModeGenericTransmitter` provides a generic transmitter using micro:bit only.
		- App Mode 'Z' (`appMode::kZipHalo`) <br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo.
		.
*/

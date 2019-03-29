/// AppKit Generic Header - A handy header file to include all microbit-dal-ext-kit-example interfaces
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

/**	@page	AppKit_Headers	Header files of microbit-dal-ext-kit-example
	The interfaces of `microbit-dal-ext-kit-example` are provided by the following header files.

	# App Modes
		- AppMode.h <br>
			App Mode values
		- AppModeBase.h <br>
			the base class
		- AppModeGenericReceiver.h <br>
			a generic receiver using micro:bit only
		- AppModeGenericTransmitter.h <br>
			a generic transmitter using micro:bit only
		- AppModeJoystickController.h <br>
			a transmitter using ElecFreaks' Joystick:bit
		- AppModeMotors.h <br>
			a receiver using SparkFun's moto:bit
		- AppModeNeoPixelRing.h <br>
			a receiver using Kitronik's Zip Halo with or without a Buzzer
		- AppModePianoKeyController.h <br>
			a transmitter using Waveshare's Mini Piano Module
		- AppModePianoPlayer.h <br>
			a player using Waveshare's Mini Piano Module
		.
	# Utilities
		- AppKitError.h
		- AppKitEvent.h
		- AppKitRemoteState.h
		- AppKitSerialDebugger.h
		.
	# Others
		- AppKit_Common.h
		- AppKit_Config.h
		- AppKit_Doxygen.h
		- AppKit.h
		.
*/

#ifndef APP_KIT_H
#define APP_KIT_H

#include "ExtKit.h"

// include this first

#include "AppKit_Common.h"

// include these as you like

#include "AppKitError.h"
#include "AppKitEvent.h"
#include "AppKitRemoteState.h"
#include "AppKitSerialDebugger.h"
#include "AppMode.h"
#include "AppModeBase.h"
#include "AppModeGenericReceiver.h"
#include "AppModeGenericTransmitter.h"
#include "AppModeJoystickController.h"
#include "AppModeMotors.h"
#include "AppModeNeoPixelRing.h"
#include "AppModePianoKeyController.h"
#include "AppModePianoPlayer.h"

#endif	// APP_KIT_H

/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// AppKit Generic Header - a handy header file to include all microbit-dal-ext-kit-example interfaces
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_H
#define APP_KIT_H

namespace microbit_dal_app_kit {

/**	@page	AppKit_Headers	Header File Structure of microbit-dal-ext-kit-example
	The interfaces of `microbit-dal-ext-kit-example` are provided by the following header files.

	# App Modes
		See also @ref	AppKit_AppMode.
		- AppMode.h
		- AppModeGenericReceiver.h
		- AppModeGenericTransmitter.h
		- AppModeJoystickController.h
		- AppModeMotors.h
		- AppModeNeoPixelRing.h
		- AppModePianoKeyController.h
		- AppModePianoPlayer.h

	# Utilities
		- AppKitError.h
		- AppKitEvent.h
		- AppKitRemoteState.h
		- AppKitSerialDebugger.h

	# Others
		- AppKit_Common.h
		- AppKit_Config.h
		- AppKit_Doxygen.h
		- AppKit.h
		- AppModeBase.h
*/

}	// microbit_dal_app_kit

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

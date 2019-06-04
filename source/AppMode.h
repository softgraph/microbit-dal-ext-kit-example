/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_H
#define APP_MODE_H

#include "ExtKitAppMode.h"

#include "AppModeBase.h"

namespace microbit_dal_app_kit {

namespace feature {

/// Auto detection for the extension board is not available.
const microbit_dal_ext_kit::AppMode kNoAutoDetection	= (1 << 0);

/// The device is mounted upside down. micro:bit's button A is on the right.
const microbit_dal_ext_kit::AppMode kInverted			= (1 << 1);

/// Remote State Transmitter is supported.
const microbit_dal_ext_kit::AppMode kRemoteStateTx	= (1 << 3);

/// Remote State Receiver is supported.
const microbit_dal_ext_kit::AppMode kRemoteStateRx	= (1 << 4);

/// Generic NeoPixel strip module is equipped optionally.
const microbit_dal_ext_kit::AppMode kNeoPixel			= (1 << 6);

/// Generic buzzer module is equipped optionally.
const microbit_dal_ext_kit::AppMode kBuzzer			= (1 << 7);

/// Generic sonar module is equipped optionally.
const microbit_dal_ext_kit::AppMode kSonar			= (1 << 8);

/// Accelerometer.
const microbit_dal_ext_kit::AppMode kAccelerometer	= (1 << 24);

/// Generic Servo Motors for L and R are equipped optionally.
const microbit_dal_ext_kit::AppMode kServoMotorsLR	= (1 << 9);

/// ElecFreaks' Joystick:bit board is connected.
const microbit_dal_ext_kit::AppMode kJoystickBit		= (1 << 11);

/// SparkFun's moto:bit board is connected.
const microbit_dal_ext_kit::AppMode kMotoBit			= (1 << 12);

/// Waveshare's Mini Piano Module for micro:bit also known as TouchPiano board is connected.
const microbit_dal_ext_kit::AppMode kTouchPiano		= (1 << 13);

/// Kitronik's Zip Halo board is connected.
const microbit_dal_ext_kit::AppMode kZipHalo			= (1 << 14);

/// Check whether a feature is configured or not
bool isConfigured(microbit_dal_ext_kit::AppMode feature);

/// Check Avaiable Hardware
microbit_dal_ext_kit::AppMode checkAvaiableHardware();

}	// feature

/// App Mode Describer
class AppModeDescriber : public microbit_dal_ext_kit::AppModeDescriberProtocol
{
public:
	/// Inherited
	/* AppModeDescriberProtocol */ const char* const * hints() const;

	/// Inherited
	/* AppModeDescriberProtocol */ const char* menuKeyFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ const char* descriptionFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ int /* count */ appModesFor(microbit_dal_ext_kit::AppMode condition, const char* menuKeyFilter, microbit_dal_ext_kit::AppMode** /* OUT new[] */ outAppModes) const;

};	// AppModeDescriber

/// Instantiate App Mode
/* new */ AppModeBase* instantiateAppMode();

}	// microbit_dal_app_kit

#endif	// APP_MODE_H

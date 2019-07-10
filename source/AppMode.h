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

/*
	Manually configured options.
*/

/// The device is mounted back to front, i.e., left and right are inverted.
const microbit_dal_ext_kit::AppMode kBackToFront	= (1 << 0);

/// The device is mounted upside down, i.e. top and bottom are inverted.
const microbit_dal_ext_kit::AppMode kUpsideDown		= (1 << 1);

/// The device is an accelerometer.
const microbit_dal_ext_kit::AppMode kAccelerometer	= (1 << 2);

/// The device is a remote state transmitter.
const microbit_dal_ext_kit::AppMode kRemoteStateTx	= (1 << 3);

/// The device is a remote state receiver.
const microbit_dal_ext_kit::AppMode kRemoteStateRx	= (1 << 4);

/// The device has no remote capability.
const microbit_dal_ext_kit::AppMode kNoRemote		= (1 << 5);

/*
	Manually configured hardware modules.
*/

/// Optional `microbit_dal_ext_kit::NeoPixel` is  available.
const microbit_dal_ext_kit::AppMode kNeoPixel		= (1 << 6);

/// Optional `microbit_dal_ext_kit::Buzzer` is  available.
const microbit_dal_ext_kit::AppMode kBuzzer			= (1 << 7);

/// Optional `microbit_dal_ext_kit::Sonar` is  available.
const microbit_dal_ext_kit::AppMode kSonar			= (1 << 8);

/*
	Auto-detectable extension boards.
*/

/// Auto-detection for the extension board is not available.
const microbit_dal_ext_kit::AppMode kNoAutoDetection	= (1 << 10);

/// `microbit_dal_ext_kit::JoystickBit` is available.
const microbit_dal_ext_kit::AppMode kJoystickBit		= (1 << 11);

/// `microbit_dal_ext_kit::MotoBit` is available.
const microbit_dal_ext_kit::AppMode kMotoBit			= (1 << 12);

/// `microbit_dal_ext_kit::TouchPiano` is available.
const microbit_dal_ext_kit::AppMode kTouchPiano			= (1 << 13);

/*
	Manually configured extension boards.
*/

/// `microbit_dal_ext_kit::ZipHalo` is  available.
const microbit_dal_ext_kit::AppMode kZipHalo			= (1 << 14);

/// `microbit_dal_app_kit::RingBitCar` is available.
const microbit_dal_ext_kit::AppMode kRingBitCar			= (1 << 15);

/// Check whether a feature is configured or not
bool isConfigured(microbit_dal_ext_kit::AppMode feature);

/// Check Avaiable Hardware
microbit_dal_ext_kit::AppMode checkAvaiableHardware();

}	// feature

/// App Mode Describer
class AppModeDescriber : public microbit_dal_ext_kit::appMode::DescriberProtocol
{
public:
	/// Inherited
	/* appMode::DescriberProtocol */ const char* const * hints() const;

	/// Inherited
	/* appMode::DescriberProtocol */ const char* menuKeyFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* appMode::DescriberProtocol */ const char* descriptionFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* appMode::DescriberProtocol */ int /* count */ appModesFor(microbit_dal_ext_kit::AppMode condition, const char* menuKeyFilter, microbit_dal_ext_kit::AppMode** /* OUT new[] */ outAppModes) const;

};	// AppModeDescriber

/// Instantiate App Mode
/* new */ AppModeBase* instantiateAppMode();

}	// microbit_dal_app_kit

#endif	// APP_MODE_H

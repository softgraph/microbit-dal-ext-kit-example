/// An example for using microbit-dal-ext-kit
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

namespace microbit_dal_app_kit {

/// App Mode
namespace appMode {

///	App Mode 'J' for a transmitter using ElecFreaks' Joystick:bit.
const microbit_dal_ext_kit::AppMode kJoystickController =
	( microbit_dal_ext_kit::feature::kRemoteTx
	| microbit_dal_ext_kit::feature::kJoystickBit
	);

///	App Mode 'M' for a receiver using SparkFun's moto:bit.
const microbit_dal_ext_kit::AppMode kMotors =
	( microbit_dal_ext_kit::feature::kRemoteRX
	| microbit_dal_ext_kit::feature::kMotoBit
	| microbit_dal_ext_kit::feature::kSonar
	| microbit_dal_ext_kit::feature::kInverted
	);

///	App Mode 'P' for a player using Waveshare's Mini Piano Module.
const microbit_dal_ext_kit::AppMode kPianoPlayer =
	( microbit_dal_ext_kit::feature::kTouchPiano
	| microbit_dal_ext_kit::feature::kNeoPixel
	| microbit_dal_ext_kit::feature::kBuzzer
	);

///	App Mode 'K' for a transmitter using Waveshare's Mini Piano Module.
const microbit_dal_ext_kit::AppMode kPianoKeyController =
	( microbit_dal_ext_kit::feature::kRemoteTx
	| microbit_dal_ext_kit::feature::kTouchPiano
	| microbit_dal_ext_kit::feature::kNeoPixel
	| microbit_dal_ext_kit::feature::kBuzzer
	);

///	App Mode 'O' for a receiver using Kitronik's Zip Halo with a Buzzer on port P2.
const microbit_dal_ext_kit::AppMode kNeoPixelRing =
	( microbit_dal_ext_kit::feature::kRemoteRX
	| microbit_dal_ext_kit::feature::kZipHalo
	| microbit_dal_ext_kit::feature::kNeoPixel
	| microbit_dal_ext_kit::feature::kBuzzer
	| microbit_dal_ext_kit::feature::kReservedForApp2	// Buzzer on port P2
	);

///	App Mode 'B' for a receiver with a Buzzer on port P1.
const microbit_dal_ext_kit::AppMode kBuzzer =
	( microbit_dal_ext_kit::feature::kRemoteRX
	| microbit_dal_ext_kit::feature::kBuzzer
	| microbit_dal_ext_kit::feature::kReservedForApp1	// Buzzer on port P1
	);

///	App Mode 'Z' for a receiver using Kitronik's Zip Halo.
const microbit_dal_ext_kit::AppMode kZipHalo =
	( microbit_dal_ext_kit::feature::kRemoteRX
	| microbit_dal_ext_kit::feature::kZipHalo
	| microbit_dal_ext_kit::feature::kNeoPixel
	| microbit_dal_ext_kit::feature::kNoAutoDetection
	);

///	App Mode 'T' for a generic transmitter using micro:bit only.
const microbit_dal_ext_kit::AppMode kGenericTransmitter =
	( microbit_dal_ext_kit::feature::kRemoteTx
	| microbit_dal_ext_kit::feature::kMicroBitOnly
	| microbit_dal_ext_kit::feature::kNoAutoDetection
	);

///	App Mode 'R' for a generic receiver using micro:bit only.
const microbit_dal_ext_kit::AppMode kGenericReceiver =
	( microbit_dal_ext_kit::feature::kRemoteRX
	| microbit_dal_ext_kit::feature::kMicroBitOnly
	| microbit_dal_ext_kit::feature::kNoAutoDetection
	);

}	// appMode

/// App Mode Describer
class AppModeDescriber : public microbit_dal_ext_kit::AppModeDescriberProtocol
{
public:
	/* AppModeDescriberProtocol */ char charFor(microbit_dal_ext_kit::AppMode appMode) const;
	/* AppModeDescriberProtocol */ const char* nameFor(microbit_dal_ext_kit::AppMode appMode) const;
	/* AppModeDescriberProtocol */ int /* count */ appModesFor(microbit_dal_ext_kit::Features condition, microbit_dal_ext_kit::AppMode** /* OUT new[] */ appModes) const;

};	// AppModeDescriber

}	// microbit_dal_app_kit

#endif	// APP_MODE_H

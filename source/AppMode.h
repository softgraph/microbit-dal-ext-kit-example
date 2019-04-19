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

/**	@page	AppKit_AppMode	App Mode - the set of components specific to a micro:bit setup and usage

	# App Modes with auto-detection

	## App Mode for ElecFreaks' Joystick:bit
		The following App Mode is selected automatically if Joystick:bit board is connected to the micro:bit.
			- App Mode J (`appMode::kJoystickController`) <br>
				`AppModeJoystickController` provides a transmitter using ElecFreaks' Joystick:bit.

	## App Mode for SparkFun's moto:bit
		The following App Mode is selected automatically if moto:bit board is connected to the micro:bit.
			- App Mode M (`appMode::kMotors`) <br>
				`AppModeMotors` provides a receiver using SparkFun's moto:bit.

	## App Modes for Waveshare's Mini Piano Module
		The following App Modes are selectable if Mini Piano Module is connected to the micro:bit.
			- App Mode P (`appMode::kPianoPlayer`) <br>
				`AppModePianoPlayer` provides a stand-alone piano player using Waveshare's Mini Piano Module.
			- App Mode K (`appMode::kPianoKeyController`) <br>
				`AppModePianoKeyController` provides a transmitter using Waveshare's Mini Piano Module.

	## App Modes for Kitronik's Zip Halo with a buzzer connected to port P2
		The following App Mode is selected automatically if a buzzer is connected to port P2 on the micro:bit.
			- App Mode O (`appMode::kNeoPixelRing`) <br>
				`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo with a buzzer.

	## App Modes for a receiver with a buzzer connected to port P1
		The following App Mode is selected automatically if a buzzer is connected to port P1 on the micro:bit.
			- App Mode B (`appMode::kBuzzer`) <br>
				`AppModeGenericReceiver` provides a receiver with a buzzer.

	# App Modes without auto-detection

	## App Modes for Kitronik's Zip Halo
		The following App Modes is selectable if any auto-detection listed here is not available.
			- App Mode Z (`appMode::kZipHalo`) <br>
				`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo.

	## App Modes for micro:bit only
		The following App Modes are selectable if any auto-detection listed here is not available.
			- App Mode G (`appMode::kGravitySensor`) <br>
				`AppModeGravitySensor` provides a gravity sensor using micro:bit only.
			- App Mode R (`appMode::kGenericReceiver`) <br>
				`AppModeGenericReceiver` provides a generic receiver using micro:bit only.
			- App Mode T (`appMode::kGenericTransmitter`) <br>
				`AppModeGenericTransmitter` provides a generic transmitter using micro:bit only.
*/

/**	@page	AppKit_RemoteStateCategory	Remote State Category - the set of remote states sent from the transmiiter to the reciver over radio

	# Remote State Category For Buttons
		The category sends and receives states of `Buttons` and `Direction`. <br>
		The following App Modes support the category using `RemoteStateTransmitterCategoryForButtons` and `RemoteStateReceiverCategoryForButtons`.
			<table><tr><td>
				Transmitter
			</td><td>
				Receiver
			</td></tr><tr><td>
				App Mode J (`appMode::kJoystickController`) <br>
				App Mode T (`appMode::kGenericTransmitter`)
			</td><td>
				App Mode M (`appMode::kMotors`) <br>
				App Mode O (`appMode::kNeoPixelRing`) <br>
				App Mode Z (`appMode::kZipHalo`) <br>
				App Mode R (`appMode::kGenericReceiver`)
			</td></tr></table>

	# Remote State Category For PianoKeys
		The category sends and receives states of `PianoKeys` and `Octave`. <br>
		The following App Modes support the category using `RemoteStateTransmitterCategoryForPianoKeys` and `RemoteStateReceiverCategoryForPianoKeys`.
			<table><tr><td>
				Transmitter
			</td><td>
				Receiver
			</td></tr>
			<tr><td>
				App Mode K (`appMode::kPianoKeyController`)
			</td><td>
				App Mode O (`appMode::kNeoPixelRing`) <br>
				App Mode B (`appMode::kBuzzer`)
			</td></tr></table>
*/

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

///	App Mode 'G' for a gravity sensor using micro:bit only.
const microbit_dal_ext_kit::AppMode kGravitySensor =
	( microbit_dal_ext_kit::feature::kMicroBitOnly
	| microbit_dal_ext_kit::feature::kReservedForApp3	// Gravity Sensor
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
	/// Inherited
	/* AppModeDescriberProtocol */ char charFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ const char* nameFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ int /* count */ appModesFor(microbit_dal_ext_kit::Features condition, microbit_dal_ext_kit::AppMode** /* OUT new[] */ appModes) const;

};	// AppModeDescriber

/// Check Avaiable Hardware
microbit_dal_ext_kit::Features checkAvaiableHardware();

/// Instantiate App Mode
/* new */ AppModeBase* instantiateAppMode();

}	// microbit_dal_app_kit

#endif	// APP_MODE_H

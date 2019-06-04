/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppMode.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

bool feature::isConfigured(AppMode feature)
{
	return (appMode() & feature) == feature;
}

AppMode feature::checkAvaiableHardware()
{
	if(JoystickBit::isAvaiable()) {
		return feature::kJoystickBit;
	}
	if(MotoBit::isAvaiable()) {
		return feature::kMotoBit;
	}
	if(TouchPiano::isAvaiable()) {
		return feature::kTouchPiano;
	}
	return feature::kNoAutoDetection;
}

namespace appMode {

/**	@page	AppKit_AppMode	App Mode - the set of components specific to a micro:bit setup and usage

	# App Modes with auto-detection

	## App Mode for ElecFreaks' Joystick:bit
		The following App Mode is selected automatically if Joystick:bit board is connected to the micro:bit.
		- App Mode `J` (a transmitter using ElecFreaks' Joystick:bit) using `AppModeJoystickController`

	## App Mode for SparkFun's moto:bit
		The following App Mode is selected automatically if moto:bit board is connected to the micro:bit.
		- App Mode `M` (a receiver using SparkFun's moto:bit) using `AppModeMotors`

	## App Modes for Waveshare's Mini Piano Module
		The following App Modes are selectable if Mini Piano Module is connected to the micro:bit.
		- App Mode `P` (a stand-alone piano player using Waveshare's Mini Piano Module) using `AppModePianoPlayer`
		- App Mode `K` (a transmitter using Waveshare's Mini Piano Module) using `AppModePianoKeyController`

	# App Modes without auto-detection
		The following App Modes are selectable if any auto-detection listed here is not available.

	## App Modes for micro:bit only
		- App Mode `GA` (a generic accelerometer) using `AppModeGenericAccelerometer`
		- App Mode `GT` (a generic transmitter) using `AppModeGenericTransmitter`
		- App Mode `GRb` (a generic receiver with a buzzer) using `AppModeGenericReceiver`
		- App Mode `GR-` (a generic receiver) using `AppModeGenericReceiver`

	## App Modes for ElecFreaks' ring:bit car (v2)
		- App Mode `C` (a receiver using ElecFreaks' ring:bit car (v2)) using `AppModeMotors`

	## App Modes for Kitronik's Zip Halo
		- App Mode `Zb` (a receiver using Kitronik's Zip Halo with a buzzer) using `AppModeNeoPixelRing`
		- App Mode `Z-` (a receiver using Kitronik's Zip Halo) using `AppModeNeoPixelRing`

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
				App Mode `J` (a transmitter using ElecFreaks' Joystick:bit)<br>
				App Mode `GT` (a generic transmitter)
			</td><td>
				App Mode `M` (a receiver using SparkFun's moto:bit)<br>
				App Mode `C` (a receiver using ElecFreaks' ring:bit car (v2))<br>
				App Mode `Zb` (a receiver using Kitronik's Zip Halo with a buzzer)<br>
				App Mode `Z-` (a receiver using Kitronik's Zip Halo)<br>
				App Mode `GRb` (a generic receiver with a buzzer)<br>
				App Mode `GR-` (a generic receiver)
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
				App Mode `K` (a transmitter using Waveshare's Mini Piano Module)
			</td><td>
				App Mode `Zb` (a receiver using Kitronik's Zip Halo with a buzzer)<br>
				App Mode `GRb` (a generic receiver using micro:bit with a buzzer)
			</td></tr></table>
*/

/*
	App Modes with `feature::kJoystickBit`
*/

///	App Mode `J` using `AppModeJoystickController`
static const AppMode kJoystickController =
	feature::kJoystickBit |
	feature::kRemoteStateTx;

/*
	App Modes with `feature::kMotoBit`
*/

///	App Mode `M` using `AppModeMotors`
static const AppMode kMotoBit =
	feature::kMotoBit |
	feature::kInverted |
	feature::kRemoteStateRx;

/*
	App Modes with `feature::kTouchPiano`
*/

///	App Mode `P` using `AppModePianoPlayer`
static const AppMode kPianoPlayer =
	feature::kTouchPiano;

///	App Mode `K` using `AppModePianoKeyController`
static const AppMode kPianoKeyController =
	feature::kTouchPiano |
	feature::kRemoteStateTx;

/*
	App Modes with `feature::kNoAutoDetection`
*/

///	App Mode `GA` using `AppModeGenericAccelerometer`
static const AppMode kGenericAccelerometer =
	feature::kNoAutoDetection |
	feature::kAccelerometer;

///	App Mode `GT` using `AppModeGenericTransmitter`
static const AppMode kGenericTransmitter =
	feature::kNoAutoDetection |
	feature::kRemoteStateTx;

///	App Mode `GR?` using `AppModeGenericReceiver`
static const AppMode kGenericReceiver =
	feature::kNoAutoDetection |
	feature::kRemoteStateRx;

/// App Mode `C?` using `AppModeMotors`
static const AppMode kRingBitCar =
	feature::kNoAutoDetection |
	feature::kServoMotorsLR |
	feature::kRemoteStateRx;

///	App Mode `Z?` using `AppModeNeoPixelRing`
static const AppMode kZipHalo =
	feature::kNoAutoDetection |
	feature::kZipHalo |
	feature::kRemoteStateRx;

}	// appMode

/**	@class AppModeDescriber
*/

struct AppModeDef {
	AppMode mode;
	const char* menuKey;
	const char* description;
};

static const AppModeDef sAppModeTable[] = {
	{
		appMode::kJoystickController,
		"J",
		"Joystick Controller"
	},
	{
		appMode::kMotoBit,
		"M",
		"moto:bit"
	},
	{
		appMode::kPianoPlayer,
		"P",
		"Piano Player"
	},
	{
		appMode::kPianoKeyController,
		"K",
		"Piano Keyboard Controller"
	},
	{
		appMode::kGenericAccelerometer,
		"GA",
		"Generic Accelerometer"
	},
	{
		appMode::kGenericTransmitter,
		"GT",
		"Generic Transmitter"
	},
	{
		appMode::kGenericReceiver | feature::kBuzzer,
		"GRb",
		"Generic Receiver with a buzzer"
	},
	{
		appMode::kGenericReceiver,
		"GR-",
		"Generic Receiver"
	},
	{
		appMode::kRingBitCar | feature::kNeoPixel,
		"Cl",
		"ring:bit Car with optional 8 LEDs"
	},
	{
		appMode::kRingBitCar,
		"C-",
		"ring:bit Car with no options"
	},
	{
		appMode::kZipHalo | feature::kBuzzer,
		"Zb",
		"Zip Halo with a buzzer"
	},
	{
		appMode::kZipHalo,
		"Z-",
		"Zip Halo"
	},

	/*
		Not yet selected
	*/
	{
		0,
		"-",
		"Not yet selected"
	}
};

static const char* const sHints[] = {
	"AAcc",
	"CCar",
	"GGen",
	"JJoy",
	"KKey",
	"MMot",
	"PPia",
	"RRx",
	"TTx",
	"ZZip",
	"bBuz",
	"lLED",
	"-Fin",
	0
};

/* AppModeDescriberProtocol */ const char * const * AppModeDescriber::hints() const
{
	return sHints;
}

/* AppModeDescriberProtocol */ const char* AppModeDescriber::menuKeyFor(AppMode appMode) const
{
	const AppModeDef* p = sAppModeTable;
	while(p->mode) {
		if(p->mode == appMode) {
			break;
		}
		p++;
	}
	return p->menuKey;
}

/* AppModeDescriberProtocol */ const char* AppModeDescriber::descriptionFor(AppMode appMode) const
{
	const AppModeDef* p = sAppModeTable;
	while(p->mode) {
		if(p->mode == appMode) {
			break;
		}
		p++;
	}
	return p->description;
}

/* AppModeDescriberProtocol */ int /* count */ AppModeDescriber::appModesFor(AppMode condition, const char* menuKeyFilter, AppMode** /* OUT new[] */ outAppModes) const
{
	EXT_KIT_ASSERT(outAppModes);

	#define COUNT_OF(x)		sizeof(x)/sizeof(x[0])	// Count of table elements

	AppMode* appModes = new AppMode[COUNT_OF(sAppModeTable)];
	int count = 0;
	for(const AppModeDef* p = sAppModeTable; p->mode; p++) {
		if((p->mode & condition) != condition) {
			continue;
		}
		if(!string::beginsWith(menuKeyFilter, p->menuKey)) {
			continue;
		}
		appModes[count++] = p->mode;
	}
	appModes[count] = 0;

	*outAppModes = appModes;
	return count;
}

/* new */ AppModeBase* instantiateAppMode()
{
	AppModeBase* appMode = 0;
	if(feature::isConfigured(appMode::kJoystickController)) {
		//	App Mode `J` using `AppModeJoystickController`
		appMode = new AppModeJoystickController();
	}
	else if(feature::isConfigured(appMode::kMotoBit)) {
		//	App Mode `M` using `AppModeMotors`
		appMode = new AppModeMotors();
	}
	else if(feature::isConfigured(appMode::kPianoKeyController)) {	// `K` should be checked before `P`
		//	App Mode `K` using `AppModePianoKeyController`
		appMode = new AppModePianoKeyController();
	}
	else if(feature::isConfigured(appMode::kPianoPlayer)) {
		//	App Mode `P` using `AppModePianoPlayer`
		appMode = new AppModePianoPlayer();
	}
	else if(feature::isConfigured(appMode::kGenericAccelerometer)) {
		//	App Mode `GA` using `AppModeGenericAccelerometer`
		appMode = new AppModeGenericAccelerometer();
	}
	else if(feature::isConfigured(appMode::kGenericTransmitter)) {
		//	App Mode `GT` using `AppModeGenericTransmitter`
		appMode = new AppModeGenericTransmitter();
	}
	else if(feature::isConfigured(appMode::kGenericReceiver)) {
		//	App Mode `GR` using `AppModeGenericReceiver`
		appMode = new AppModeGenericReceiver();
	}
	else if(feature::isConfigured(appMode::kZipHalo)) {
		//	App Mode `Z` using `AppModeNeoPixelRing`
		appMode = new AppModeNeoPixelRing();
	}
	else {
		EXT_KIT_ASSERT(!"Invalid App Mode");
	}
	return appMode;
}

}	// microbit_dal_app_kit

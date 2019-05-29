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
namespace appMode {

/**	@page	AppKit_AppMode	App Mode - the set of components specific to a micro:bit setup and usage

	# App Modes with auto-detection

	## App Mode for ElecFreaks' Joystick:bit
		The following App Mode is selected automatically if Joystick:bit board is connected to the micro:bit.
		- App Mode "J"<br>
			`AppModeJoystickController` provides a transmitter using ElecFreaks' Joystick:bit.

	## App Mode for SparkFun's moto:bit
		The following App Mode is selected automatically if moto:bit board is connected to the micro:bit.
		- App Mode "M"<br>
			`AppModeMotors` provides a receiver using SparkFun's moto:bit.

	## App Modes for Waveshare's Mini Piano Module
		The following App Modes are selectable if Mini Piano Module is connected to the micro:bit.
		- App Mode "P"<br>
			`AppModePianoPlayer` provides a stand-alone piano player using Waveshare's Mini Piano Module.
		- App Mode "K<br>
			`AppModePianoKeyController` provides a transmitter using Waveshare's Mini Piano Module.

	# App Modes without auto-detection
		The following App Modes are selectable if any auto-detection listed here is not available.

	## App Modes for Kitronik's Zip Halo
		- App Mode "Zb"<br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo with a buzzer.
		- App Mode "Z-"<br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo.

	## App Modes for micro:bit only
		- App Mode "GA"<br>
			`AppModeGenericAccelerometer` provides a generic accelerometer using micro:bit only.
		- App Mode "GT"<br>
			`AppModeGenericTransmitter` provides a generic transmitter using micro:bit only.
		- App Mode "GRb"<br>
			`AppModeGenericReceiver` provides a generic receiver using micro:bit with a buzzer.
		- App Mode "GR-"<br>
			`AppModeGenericReceiver` provides a generic receiver using micro:bit only.
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
				App Mode "J"<br>
				App Mode "GT"
			</td><td>
				App Mode "M"<br>
				App Mode "Zb"<br>
				App Mode "Z-"<br>
				App Mode "GRb"<br>
				App Mode "GR-"
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
				App Mode "K"
			</td><td>
				App Mode "Zb"<br>
				App Mode "GRb"
			</td></tr></table>
*/

/*
	App Modes with `feature::kJoystickBit`
*/

///	App Mode "J" for `AppModeJoystickController`
static const AppMode kJoystickController =
	feature::kRemoteStateTx |
	feature::kJoystickBit;

/*
	App Modes with `feature::kMotoBit`
*/

///	App Mode "M" for `AppModeMotors`
static const AppMode kMotors =
	feature::kRemoteStateRx |
	feature::kMotoBit |
	feature::kSonar |
	feature::kInverted;

/*
	App Modes with `feature::kTouchPiano`
*/

///	App Mode "P" for `AppModePianoPlayer`
static const AppMode kPianoPlayer =
	feature::kTouchPiano |
	feature::kNeoPixel |
	feature::kBuzzer;

///	App Mode "K" for `AppModePianoKeyController`
static const AppMode kPianoKeyController =
	feature::kRemoteStateTx |
	feature::kTouchPiano |
	feature::kNeoPixel |
	feature::kBuzzer;

/*
	App Modes with `feature::kNoAutoDetection`
*/

///	App Mode "GA" for `AppModeGenericAccelerometer`
static const AppMode kGenericAccelerometer =
	feature::kMicroBitOnly |
	feature::kReservedForApp0 |	// Use Accelerometer
	feature::kNoAutoDetection;

///	App Mode "GT" for `AppModeGenericTransmitter`
static const AppMode kGenericTransmitter =
	feature::kRemoteStateTx |
	feature::kMicroBitOnly |
	feature::kNoAutoDetection;

///	App Mode "GR?" for `AppModeGenericReceiver`
static const AppMode kGenericReceiver =
	feature::kRemoteStateRx |
	feature::kMicroBitOnly |
	feature::kNoAutoDetection;

///	App Mode "Z?" for `AppModeNeoPixelRing`
static const AppMode kZipHalo =
	feature::kRemoteStateRx |
	feature::kZipHalo |
	feature::kNeoPixel |
	feature::kNoAutoDetection;

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
		appMode::kMotors,
		"M",
		"Motors"
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
	"GGen",
	"JJoy",
	"KKey",
	"MMot",
	"PPia",
	"RRx",
	"TTx",
	"ZZip",
	"bBuz",
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

/* AppModeDescriberProtocol */ int /* count */ AppModeDescriber::appModesFor(Features condition, const char* menuKeyFilter, AppMode** /* OUT new[] */ outAppModes) const
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

Features checkAvaiableHardware()
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

/* new */ AppModeBase* instantiateAppMode()
{
	AppModeBase* appMode = 0;
	if(feature::isConfigured(appMode::kJoystickController)) {
		//	App Mode "J" for `AppModeJoystickController`
		appMode = new AppModeJoystickController();
	}
	else if(feature::isConfigured(appMode::kMotors)) {
		//	App Mode "M" for `AppModeMotors`
		appMode = new AppModeMotors();
	}
	else if(feature::isConfigured(appMode::kPianoPlayer)) {
		//	App Mode "P" for `AppModePianoPlayer`
		appMode = new AppModePianoPlayer();
	}
	else if(feature::isConfigured(appMode::kPianoKeyController)) {
		//	App Mode "K" for `AppModePianoKeyController`
		appMode = new AppModePianoKeyController();
	}
	else if(feature::isConfigured(appMode::kGenericAccelerometer)) {
		//	App Mode "GA" for `AppModeGenericAccelerometer`
		appMode = new AppModeGenericAccelerometer();
	}
	else if(feature::isConfigured(appMode::kGenericTransmitter)) {
		//	App Mode "GT" for `AppModeGenericTransmitter`
		appMode = new AppModeGenericTransmitter();
	}
	else if(feature::isConfigured(appMode::kGenericReceiver)) {
		//	App Mode "GR?" for `AppModeGenericReceiver`
		appMode = new AppModeGenericReceiver();
	}
	else if(feature::isConfigured(appMode::kZipHalo)) {
		//	App Mode "Z?" for `AppModeNeoPixelRing`
		appMode = new AppModeNeoPixelRing();
	}
	else {
		EXT_KIT_ASSERT(!"Invalid App Mode");
	}
	return appMode;
}

}	// microbit_dal_app_kit

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
	return (appMode::activeMode() & feature) == feature;
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
		The following App Modes are selectable if any auto-detection listed above is not available.

	## App Modes for micro:bit only
		- App Mode `GA` (a generic accelerometer) using `AppModeGenericAccelerometer`
		- App Mode `GT` (a generic transmitter) using `AppModeGenericTransmitter`
		- App Mode `GRB` (a generic receiver with a buzzer) using `AppModeGenericReceiver`
		- App Mode `GR-` (a generic receiver) using `AppModeGenericReceiver`

	## App Modes for ElecFreaks' ring:bit car (v2)
		- App Mode `CL` (a receiver using ElecFreaks' ring:bit car (v2) with optional 8 LEDs) using `AppModeMotors`
		- App Mode `C-` (a receiver using ElecFreaks' ring:bit car (v2)) using `AppModeMotors`

	## App Modes for Kitronik's Zip Halo
		- App Mode `ZB` (a receiver using Kitronik's Zip Halo with a buzzer) using `AppModeNeoPixelRing`
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
				App Mode `CL` (a receiver using ElecFreaks' ring:bit car (v2) with optional 8 LEDs)<br>
				App Mode `C-` (a receiver using ElecFreaks' ring:bit car (v2))<br>
				App Mode `ZB` (a receiver using Kitronik's Zip Halo with a buzzer)<br>
				App Mode `Z-` (a receiver using Kitronik's Zip Halo)<br>
				App Mode `GRB` (a generic receiver with a buzzer)<br>
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
				App Mode `ZB` (a receiver using Kitronik's Zip Halo with a buzzer)<br>
				App Mode `GRB` (a generic receiver using micro:bit with a buzzer)
			</td></tr></table>
*/

namespace appMode {

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
	feature::kRemoteStateRx;

/*
	App Modes with `feature::kTouchPiano`
*/

///	App Mode `P` using `AppModePianoPlayer`
static const AppMode kPianoPlayer =
	feature::kTouchPiano |
	feature::kNoRemote;

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
	feature::kAccelerometer |
	feature::kNoRemote;

///	App Mode `GT` using `AppModeGenericTransmitter`
static const AppMode kGenericTransmitter =
	feature::kNoAutoDetection |
	feature::kRemoteStateTx;

///	App Mode `GR` using `AppModeGenericReceiver`
static const AppMode kGenericReceiver =
	feature::kNoAutoDetection |
	feature::kRemoteStateRx;

/// App Mode `C` using `AppModeMotors`
static const AppMode kRingBitCar =
	feature::kNoAutoDetection |
	feature::kRingBitCar |
	feature::kRemoteStateRx;

/// App Mode `B` using `AppModeMotors`
static const AppMode kPanTiltBracket =
	feature::kNoAutoDetection |
	feature::kPanTiltBracket |
	feature::kRemoteStateRx;

///	App Mode `Z` using `AppModeNeoPixelRing`
static const AppMode kZipHalo =
	feature::kNoAutoDetection |
	feature::kZipHalo |
	feature::kRemoteStateRx;

}	// appMode

/**	@class AppModeDescriber
*/

// App Mode Definition
struct AppModeDef {
	AppMode mode;	// Full App Mode definition - one of main App Mode (`appMode::k...`) plus optional features
	const char* menuKey;	// A short menu key string uniquely summarizes the App Mode
	const char* description;	// A description for the App Mode
};

// Menu Key Hints
/*
	For the details, see also `microbit_dal_ext_kit::appMode::DescriberProtocol::hints()`.
*/
static const char* const sHints[] = {
	/*
		The following menu key characters intend to describe the main extension board used by the App Mode. They are only available at sub-menu depth 0, i.e., they should be placed at the first character of any menu key string.
	*/
	"B0Brc",	// Pan/Tilt Bracket
	"C0Car",	// ring:bit Car
	"G0Gen",	// Generic (no extension board)
	"J0Joy",	// Joystick:bit
	"K0Key",	// TouchPiano for Piano Keyboard Controller
	"M0Mot",	// moto:bit
	"P0Ply",	// TouchPiano for Piano Player
	"Z0Zip",	// Zip Halo
	/*
		The following menu key characters intend to describe optional features used by the App Mode. They are available at any sub-menu depth.
	*/
	"A*Acc",	// Accelerometer
	"B*Buz",	// Buzzer
	"L*Led",	// LED
	"R*Rx",		// Receiver
	"S*Son",	// Sonar
	"T*Tx",		// Transmitter
	"-*Fin",	// Finish (No more options)
	0			// End of table
};

// App Mode Definition Table
static const AppModeDef sAppModeTable[] = {
	{
		appMode::kJoystickController,
		"J",
		"Joystick:bit"
	},
	{
		appMode::kMotoBit | feature::kUpsideDown,
		"M",
		"moto:bit"
	},
	{
		appMode::kPianoPlayer,
		"P",
		"TouchPiano for Piano Player"
	},
	{
		appMode::kPianoKeyController,
		"K",
		"TouchPiano for Piano Keyboard Controller"
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
		"GRB",
		"Generic Receiver with a buzzer"
	},
	{
		appMode::kGenericReceiver,
		"GR-",
		"Generic Receiver"
	},
	{
		appMode::kRingBitCar | feature::kBackToFront | feature::kNeoPixel,
		"CL",
		"ring:bit Car with optional 8 LEDs"
	},
	{
		appMode::kRingBitCar | feature::kSonar,
		"CS",
		"ring:bit Car with a sonar"
	},
	{
		appMode::kRingBitCar | feature::kBackToFront,
		"C-",
		"ring:bit Car"
	},
	{
		appMode::kPanTiltBracket,
		"B",
		"Pan/Tilt Bracket"
	},
	{
		appMode::kZipHalo | feature::kBuzzer,
		"ZB",
		"Zip Halo with a buzzer"
	},
	{
		appMode::kZipHalo,
		"Z-",
		"Zip Halo"
	},
	{
		0,
		"-",
		"Not yet selected"
	}
};

/* appMode::DescriberProtocol */ const char * const * AppModeDescriber::hints() const
{
	return sHints;
}

/* appMode::DescriberProtocol */ const char* AppModeDescriber::menuKeyFor(AppMode appMode) const
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

/* appMode::DescriberProtocol */ const char* AppModeDescriber::descriptionFor(AppMode appMode) const
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

/* appMode::DescriberProtocol */ int /* count */ AppModeDescriber::appModesFor(AppMode condition, const char* menuKeyFilter, AppMode** /* OUT new[] */ outAppModes) const
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
	else if(feature::isConfigured(appMode::kRingBitCar)) {
		//	App Mode `C` using `AppModeMotors`
		appMode = new AppModeMotors();
	}
	else if(feature::isConfigured(appMode::kPanTiltBracket)) {
		//	App Mode `B` using `AppModeMotors`
		appMode = new AppModeMotors();
	}
	else if(feature::isConfigured(appMode::kPianoPlayer)) {
		//	App Mode `P` using `AppModePianoPlayer`
		appMode = new AppModePianoPlayer();
	}
	else if(feature::isConfigured(appMode::kPianoKeyController)) {
		//	App Mode `K` using `AppModePianoKeyController`
		appMode = new AppModePianoKeyController();
	}
	else if(feature::isConfigured(appMode::kZipHalo)) {
		//	App Mode `Z` using `AppModeNeoPixelRing`
		appMode = new AppModeNeoPixelRing();
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
	else {
		EXT_KIT_ASSERT(!"Invalid App Mode");
	}
	return appMode;
}

}	// microbit_dal_app_kit

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

/**	@class AppModeDescriber
*/

struct AppModeDef {
	AppMode mode;
	char modeChar;
	const char* modeName;
};

static const AppModeDef sAppModeTable[] = {

	//	[App Modes for kJoystickBit]

	//	App Mode 'J' for a transmitter using ElecFreaks' Joystick:bit.
	{ appMode::kJoystickController,		'J', "Joystick Controller" },

	//	[App Modes for kMotoBit]

	//	App Mode 'M' for a receiver using SparkFun's moto:bit.
	{ appMode::kMotors,					'M', "Motors" },

	//	[App Modes for kTouchPiano]

	//	App Mode 'P' for a player using Waveshare's Mini Piano Module.
	{ appMode::kPianoPlayer,			'P', "Piano Player" },

	//	App Mode 'K' for a transmitter using Waveshare's Mini Piano Module.
	{ appMode::kPianoKeyController,		'K', "Piano Key Controller" },

	//	[App Modes for kBuzzer + kReservedForApp2]

	//	App Mode 'O' for a receiver using Kitronik's Zip Halo with a Buzzer on port P2.
	{ appMode::kNeoPixelRing,			'O', "NeoPixel Ring" },

	//	[App Modes for kBuzzer + kReservedForApp1]

	//	App Mode 'B' for a receiver with a Buzzer on port P1.
	{ appMode::kBuzzer,					'B', "Buzzer" },

	//	[App Modes for kNoAutoDetection]

	//	App Mode 'G' for a gravity sensor using micro:bit only.
	{ appMode::kGravitySensor,			'G', "Gravity Sensor" },

	//	App Mode 'T' for a generic transmitter using micro:bit only.
	{ appMode::kGenericTransmitter,		'T', "Generic Transmitter" },

	//	App Mode 'R' for a generic receiver using micro:bit only.
	{ appMode::kGenericReceiver,		'R', "Generic Receiver" },

	//	App Mode 'Z' for a receiver using Kitronik's Zip Halo.
	{ appMode::kZipHalo,				'Z', "Zip Halo" },

	//	[Not yet selected]

	{ 0,								'-', "Not yet selected" }
};

/* AppModeDescriberProtocol */ char AppModeDescriber::charFor(AppMode appMode) const
{
	const AppModeDef* p = sAppModeTable;
	while(p->mode) {
		if(p->mode == appMode) {
			break;
		}
		p++;
	}
	return p->modeChar;
}

/* AppModeDescriberProtocol */ const char* AppModeDescriber::nameFor(AppMode appMode) const
{
	const AppModeDef* p = sAppModeTable;
	while(p->mode) {
		if(p->mode == appMode) {
			break;
		}
		p++;
	}
	return p->modeName;
}

/* AppModeDescriberProtocol */ int /* count */ AppModeDescriber::appModesFor(Features condition, AppMode** /* OUT new[] */ appModes) const
{
	EXT_KIT_ASSERT(appModes);

	#define COUNT_OF(x)		sizeof(x)/sizeof(x[0])	// Count of table elements

	AppMode* selection = new AppMode[COUNT_OF(sAppModeTable)];
	const AppModeDef* p = sAppModeTable;
	int count = 0;
	while(p->mode) {
		if((p->mode & condition) == condition) {
			selection[count++] = p->mode;
		}
		p++;
	}
	selection[count] = 0;

	*appModes = selection;
	return count;
}

Features checkAvaiableHardware()
{
	Features result;
	result = JoystickBit::avaiableFeatures();
	if(result) {
		return result;
	}
	result = MotoBit::avaiableFeatures();
	if(result) {
		return result;
	}
	result = TouchPiano::avaiableFeatures();
	if(result) {
		return result;
	}
	ExtKit& g = ExtKit::global();
	result = Buzzer::avaiableFeatures(g.p2());
	if(result) {
		return result | feature::kReservedForApp2;	// Buzzer on port P2
	}
	result = Buzzer::avaiableFeatures(g.p1());
	if(result) {
		return result | feature::kReservedForApp1;	// Buzzer on port P1
	}
	return feature::kNoAutoDetection;
}

/* new */ AppModeBase* instantiateAppMode()
{
	AppModeBase* appMode = 0;
	if(AppModeMotors::isConfigured()) {						// selected AppMode: 'M'
		appMode = new AppModeMotors();
	}
	else if(AppModeJoystickController::isConfigured()) {	// selected AppMode: 'J'
		appMode = new AppModeJoystickController();
	}
	else if(AppModePianoPlayer::isConfigured()) {			// selected AppMode: 'P'
		appMode = new AppModePianoPlayer();
	}
	else if(AppModePianoKeyController::isConfigured()) {	// selected AppMode: 'K'
		appMode = new AppModePianoKeyController();
	}
	else if(AppModeNeoPixelRing::isConfigured()) {			// selected AppMode: 'O' or 'Z'
		appMode = new AppModeNeoPixelRing();
	}
	else if(AppModeGravitySensor::isConfigured()) {			// selected AppMode: 'G'
		appMode = new AppModeGravitySensor();
	}
	else if(AppModeGenericTransmitter::isConfigured()) {	// selected AppMode: 'T'
		appMode = new AppModeGenericTransmitter();
	}
	else if(AppModeGenericReceiver::isConfigured()) {		// selected AppMode: 'B' or 'R'
		appMode = new AppModeGenericReceiver();
	}
	else {
		EXT_KIT_ASSERT(!"Invalid App Mode");
	}
	return appMode;
}

}	// microbit_dal_app_kit

/// An example for using microbit-dal-ext-kit
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

/* AppModeDescriberProtocol */ int /* count */ AppModeDescriber::appModesFor(Features condition, AppMode** /* OUT new */ appModes) const
{
	#define COUNT_OF(x)		sizeof(x)/sizeof(x[0])

	EXT_KIT_ASSERT(appModes);

	AppMode* selection = new AppMode[COUNT_OF(sAppModeTable)];
	const AppModeDef* p = sAppModeTable;
	int count = 0;
	while(p->mode) {
		if((p->mode & condition) == condition) {
			selection[count++] = p->mode;
		}
		p++;
	}
	if(0 < count) {
		*appModes = selection;
	}
	return count;
}

}	// microbit_dal_app_kit

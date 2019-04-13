/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// AppKit Main
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKit.h"

using namespace microbit_dal_app_kit;
using namespace microbit_dal_ext_kit;

#define	ENABLE_ALL_MICROBIT_FEATURES	0	// Enable all `MicroBit` features if true

#if ENABLE_ALL_MICROBIT_FEATURES

/// Device class
static MicroBitExtKit	uBit;

#else	// ENABLE_ALL_MICROBIT_FEATURES

class AppExtKit : public PrimitiveExtKit
{
public:
	AppExtKit();
	void init();

private:
	MicroBitAccelerometer&	accelerometer;
	MicroBitRadio	radio;
};

AppExtKit::AppExtKit()
	: PrimitiveExtKit()
	, accelerometer(MicroBitAccelerometer::autoDetect(i2c))
{
}

void AppExtKit::init()
{
	PrimitiveExtKit::init();
	mExtKit.registerAccelerometer(accelerometer);
	mExtKit.registerRadio(radio);
}

/// Device class
static AppExtKit	uBit;

#endif	// ENABLE_ALL_MICROBIT_FEATURES

/// Serial Debugger
static AppSerialDebugger	sDebugger;

/// App Mode Describer
static AppModeDescriber		sDescriber;

/// Periodic Observer
static PeriodicObserver		sPeriodicObserver;

static Features checkAvaiableHardware();
static /* new */ AppModeBase* instantiateAppMode();

// main function
int main()
{
	// Initialize the device.
	uBit.init();

	// Start the Serial Debugger service first. After this call, the debugger is prepared but not yet activated.
	// To acivate it, you need to press any key on the terminal conected to the USB seria port.
	sDebugger.start();

	// Show the bootup string and give a chance to acivate the debugger via the USB serial port.
	display::scrollString(APP_STRING_BOOTUP);

	// Check Avaiable Hardware.
	Features condition = checkAvaiableHardware();
	EXT_KIT_ASSERT(condition);

	// Repeat indefinitely.
	while (true) {

		// Select an App Mode automatically or manually. After ths call, the character for the selected App Mode is shown on the display.
		selectAppModeFor(condition, sDescriber);
		EXT_KIT_ASSERT(feature::configured());

		// Set display rotation.
		bool inverted = feature::isConfigured(feature::kInverted);
		display::setDisplayRotation(inverted ? MICROBIT_DISPLAY_ROTATION_180 : MICROBIT_DISPLAY_ROTATION_0);

		// Start the corresponding App Mode Component.
		AppModeBase* appMode = instantiateAppMode();
		EXT_KIT_ASSERT_OR_PANIC(appMode, kPanicOutOfMemory);
		appMode->start();

		// Clear the App Mode character on the display.
		time::sleep(500 /* milliseconds */);
		display::clear();

		// Fire the App Stared event.
		MicroBitEvent(messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted);	// CREATE_AND_FIRE

		// Start the Periodic Observer and wait for the completion.
		sPeriodicObserver.start();
		sPeriodicObserver.waitForCompletion();

		/// Stop services.
		sPeriodicObserver.stop();
		appMode->stop();
		delete appMode;
	}

// exit:
	EXT_KIT_ASSERT_OR_PANIC(!"App Main is Aborted", kAppMainAborted);
	return 0;
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

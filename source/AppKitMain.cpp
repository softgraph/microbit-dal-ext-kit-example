/// AppKit Main
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKit.h"

using namespace microbit_dal_ext_kit;

#define	ENABLE_ALL_MICROBIT_FEATURES	0

#if ENABLE_ALL_MICROBIT_FEATURES

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

static AppExtKit	uBit;

#endif	// ENABLE_ALL_MICROBIT_FEATURES

static AppSerialDebugger	sDebugger;
static AppModeDescriber		sDescriber;
static PeriodicObserver		sPeriodicObserver;

static Features checkAvaiableHardware();
static /* new */ AppModeBase* instantiateAppMode();

int main()
{
	// Initialize the device.
	uBit.init();

	// Start the Serial Debugger service first. The debugger is ready, but not yet activated at this point. To acivate it, you need to press any key on the terminal conected to the seria port.
	sDebugger.start();

	// Show the bootup string and give a chance to enable the debugger via the serial port.
	display::scrollString(APP_STRING_BOOTUP);

	// Check Avaiable Hardware.
	Features condition = checkAvaiableHardware();
	EXT_KIT_ASSERT(condition != 0);

	// Select an App Mode automatically or manually. After ths call, the character for the selected App Mode will be shown on the display.
	selectAppModeFor(condition, sDescriber);
	EXT_KIT_ASSERT(feature::configured() != 0);

	// Check whether the device is inverted or not.
	bool inverted = feature::isConfigured(feature::kInverted);
	if(inverted) {
		display::setUpsideDown();
	}

#if 0	//	@todo
	// Prepare other core modules if required
	prepareCoreRadio();
#endif

	// Start a corresponding App Mode Component.
	AppModeBase* appMode = instantiateAppMode();
	EXT_KIT_ASSERT_OR_PANIC(appMode, kPanicOutOfMemory);
	appMode->start();

	// Clear the App Mode character on the display.
	time::sleep(500 /* milliseconds */);
	display::clear();

	// Fire an App Stared event.
	MicroBitEvent(messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted);	// CREATE_AND_FIRE

	// Start the Periodic Observer.
	sPeriodicObserver.start();

	// Sleep forever.
	time::sleep();

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
		return result | feature::kZipHalo;	// the device might be a ZipHalo with a buzzer on P2
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
	else if(AppModeGenericReceiver::isConfigured()) {		// selected AppMode: 'R'
		appMode = new AppModeGenericReceiver();
	}
	else {
		EXT_KIT_ASSERT(!"Invalid App Mode");
	}
	return appMode;
}

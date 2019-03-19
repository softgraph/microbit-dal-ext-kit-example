/// App Mode for Joystick Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeJoystickController.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeJoystickController
*/

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

struct DirectionState {
	Direction	latest	= direction::kCenter;
	Direction	last	= direction::kCenter;
};

static const Features kAppMode = appMode::kJoystickController;

static ButtonsState		localButtons;
static DirectionState	localDirection;

/* Component */ bool AppModeJoystickController::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeJoystickController::AppModeJoystickController()
	: AppModeBase("AppModeJoystickController")
{
}

/* Component */ void AppModeJoystickController::start()
{
	AppModeBase::start();
	mJoystickBit.start();
	mRadio.start();

	if(feature::isConfigured(feature::kRemoteEventTx)) {
		// observe local events to trigger remote events
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT);
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT);
	}
}

/* Component */ void AppModeJoystickController::stop()
{
	mRadio.stop();
	mJoystickBit.stop();
	AppModeBase::stop();
}

/* AppModeBase */ void AppModeJoystickController::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			display::showButton(button::kNone);
		}
	}
	else if(source == MICROBIT_ID_GESTURE) {
		if(value == gesture::microBitGestureEventTiltLeft()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedLeft);	// CREATE_AND_FIRE
			display::flashChar('<');
		}
		else if(value == gesture::microBitGestureEventTiltRight()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedRight);	// CREATE_AND_FIRE
			display::flashChar('>');
		}
	}
}

/* AppModeBase */ void AppModeJoystickController::doHandlePeriodic100ms(uint32_t /* count */)
{
	//	check local buttons and direction
	{
		ButtonsState& b = localButtons;
		DirectionState& d = localDirection;
		b.latest = mJoystickBit.readJoystickButtons();
		d.latest = mJoystickBit.readJoystickDirection();
		if((b.last != b.latest) || (d.last != d.latest)) {
			updateRemoteButtonsToRadio(b.latest, d.latest);
			if(b.last != b.latest) {
				display::showButton(b.latest);
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Buttons: 0x", string::hex(b.latest).toCharArray());
			}
			if(d.last != d.latest) {
				display::showDirection(d.latest);
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Direction: 0x", string::hex(d.latest).toCharArray());
			}
			b.last = b.latest;
			d.last = d.latest;
		}
	}
}

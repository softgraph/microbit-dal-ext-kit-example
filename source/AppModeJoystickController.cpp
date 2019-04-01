/// App Mode for Joystick Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeJoystickController.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/**	@class	AppModeJoystickController
*/

static const Features kAppMode = appMode::kJoystickController;

/* Component */ bool AppModeJoystickController::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeJoystickController::AppModeJoystickController()
	: AppModeBase("AppModeJoystickController")
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	static const EventDef radioEvents[] = {
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedRight },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);
	selectRadioEvents(radioEvents);

	addChild(mJoystickBit);
	addChild(mTransmitter);
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
	// Update Remote Buttons and Direction
	{
		Buttons b = mJoystickBit.readJoystickButtons();
		if(mTransmitterCategoryForButtons.buttons.set(b)) {
			display::showButton(b);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Buttons: 0x", string::hex(b).toCharArray());
		}
		Direction d = mJoystickBit.readJoystickDirection();
		if(mTransmitterCategoryForButtons.direction.set(d)) {
			display::showDirection(d);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Direction: 0x", string::hex(d).toCharArray());
		}
		mTransmitterCategoryForButtons.updateRemoteState();
	}
}

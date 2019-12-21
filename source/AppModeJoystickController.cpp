/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Joystick Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeJoystickController.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeJoystickController
*/

AppModeJoystickController::AppModeJoystickController()
	: AppModeBase("AppModeJoystickController")
	, mJoystickBit(feature::isConfigured(feature::kVariant1) ? JoystickBit::V2 : JoystickBit::V1)
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_UP },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_DOWN },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT },
		{ MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	static const EventDef radioEvents[] = {
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kN },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kE },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kW },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kS },
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
		for(int i = 0; i < 4; i++) {
			Direction d = direction::kFour[i];
			if(value == gesture::microBitGestureEventTilt(d)) {
				MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + d, CREATE_AND_FIRE);
				display::showDirection(d, display::kSolidTriangle, 500 /* milliseconds */);
				break;
			}
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

}	// microbit_dal_app_kit

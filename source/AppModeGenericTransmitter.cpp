/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Generic Transmitter
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeGenericTransmitter.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeGenericTransmitter
*/

AppModeGenericTransmitter::AppModeGenericTransmitter()
	: AppModeBase("AppModeGenericTransmitter")
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
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);
	selectRadioEvents(radioEvents);

	addChild(mTransmitter);
}

/* AppModeBase */ void AppModeGenericTransmitter::doHandleEvent(const MicroBitEvent& event)
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
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft);	// CREATE_AND_FIRE
			display::showDirection(direction::kW, display::kSolidTriangle, 500 /* milliseconds */);
		}
		else if(value == gesture::microBitGestureEventTiltTop()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop);	// CREATE_AND_FIRE
			display::showDirection(direction::kN, display::kSolidTriangle, 500 /* milliseconds */);
		}
		else if(value == gesture::microBitGestureEventTiltRight()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight);	// CREATE_AND_FIRE
			display::showDirection(direction::kE, display::kSolidTriangle, 500 /* milliseconds */);
		}
		else if(value == gesture::microBitGestureEventTiltBottom()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom);	// CREATE_AND_FIRE
			display::showDirection(direction::kS, display::kSolidTriangle, 500 /* milliseconds */);
		}
	}
}

/* AppModeBase */ void AppModeGenericTransmitter::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Update Remote Buttons
	{
		Buttons b = button::readMicroBitButtons();
		if(mTransmitterCategoryForButtons.buttons.set(b)) {
			display::showButton(b);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Buttons: 0x", string::hex(b).toCharArray());
		}
		mTransmitterCategoryForButtons.updateRemoteState();
	}
}

}	// microbit_dal_app_kit

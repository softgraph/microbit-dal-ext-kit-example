/// App Mode for Generic Transmitter
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeGenericTransmitter.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeGenericTransmitter
*/

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

static const Features kAppMode = appMode::kGenericTransmitter;

static ButtonsState		localButtons;

/* Component */ bool AppModeGenericTransmitter::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeGenericTransmitter::AppModeGenericTransmitter()
	: AppModeBase("AppModeGenericTransmitter")
{
}

/* Component */ void AppModeGenericTransmitter::start()
{
	AppModeBase::start();
	mRadio.start();
}

/* Component */ void AppModeGenericTransmitter::stop()
{
	mRadio.stop();
	AppModeBase::stop();
}

/* AppModeBase */ void AppModeGenericTransmitter::doStart()
{
	if(feature::isConfigured(feature::kRemoteEventTx)) {
		// observe local events to trigger remote events
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT);
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT);
	}
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
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedLeft);	// CREATE_AND_FIRE
			display::flashChar('<');
		}
		else if(value == gesture::microBitGestureEventTiltRight()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedRight);	// CREATE_AND_FIRE
			display::flashChar('>');
		}
	}
}

/* AppModeBase */ void AppModeGenericTransmitter::doHandlePeriodic100ms(uint32_t /* count */)
{
	//	check local buttons
	{
		ButtonsState& b = localButtons;
		b.latest = button::readMicroBitButtons();
		if(b.last != b.latest) {
			updateRemoteButtonsToRadio(b.latest, direction::kCenter);
			display::showButton(b.latest);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}
}

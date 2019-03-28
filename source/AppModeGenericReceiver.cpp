/// App Mode for Generic Receiver
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeGenericReceiver.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeGenericReceiver
*/

static const Features kAppMode = appMode::kGenericReceiver;

/* Component */ bool AppModeGenericReceiver::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeGenericReceiver::AppModeGenericReceiver()
	: AppModeBase("AppModeGenericReceiver")
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedRight },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	addChild(mReceiver);
}

/* AppModeBase */ void AppModeGenericReceiver::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			display::showButton(button::kNone);
		}
	}
	else if(source == messageBusID::kRemoteEvent) {
		if(value == messageBusEvent::kRemoteTiltedLeft) {
			display::flashChar('<');
		}
		else if(value == messageBusEvent::kRemoteTiltedRight) {
			display::flashChar('>');
		}
	}
}

/* AppModeBase */ void AppModeGenericReceiver::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Remote Buttons
	{
		Buttons b;
		if(mReceiverForButtons.buttons.read(b)) {
			display::showButton(b);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
		}
	}
}

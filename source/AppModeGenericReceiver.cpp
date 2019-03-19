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

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

static const Features kAppMode = appMode::kGenericReceiver;

static ButtonsState		remoteButtons;

/* Component */ bool AppModeGenericReceiver::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeGenericReceiver::AppModeGenericReceiver()
	: AppModeBase("AppModeGenericReceiver")
{
}

/* Component */ void AppModeGenericReceiver::start()
{
	AppModeBase::start();
	mRadio.start();
}

/* Component */ void AppModeGenericReceiver::stop()
{
	mRadio.stop();
	AppModeBase::stop();
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

/* AppModeBase */ void AppModeGenericReceiver::doHandleRadioDatagramReceived(const ManagedString& /* received */)
{
	Buttons buttons = checkLatestRemoteButtons();
	if(buttons != button::kInvalid) {
		remoteButtons.latest = buttons;
	}
}

/* AppModeBase */ void AppModeGenericReceiver::doHandlePeriodic100ms(uint32_t /* count */)
{
	//	check remote buttons
	{
		ButtonsState& b = remoteButtons;
		if(b.last != b.latest) {
			display::showButton(b.latest);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}
}

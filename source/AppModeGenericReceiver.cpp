/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Generic Receiver
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeGenericReceiver.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeGenericReceiver
*/

AppModeGenericReceiver::AppModeGenericReceiver()
	: AppModeBase("AppModeGenericReceiver")
	, mBuzzer(0)
{
	if(feature::isConfigured(feature::kBuzzer)) {
		ExtKit& g = ExtKit::global();
		mBuzzer = new Buzzer("BuzzerForNeoPixelRing", /* analogPort */ g.p1());
		EXT_KIT_ASSERT_OR_PANIC(mBuzzer, panic::kOutOfMemory);
	}

	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kN },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kE },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kW },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kS },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	addChild(mReceiver);
	if(mBuzzer) {
		addChild(*mBuzzer);
	}
}

AppModeGenericReceiver::~AppModeGenericReceiver()
{
	delete mBuzzer;
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
		for(int i = 0; i < 4; i++) {
			Direction d = direction::kFour[i];
			if(value == messageBusEvent::kRemoteTiltBase + d) {
				display::showDirection(d, display::kSolidTriangle, 500 /* milliseconds */);
				break;
			}
		}
	}
}

/* AppModeBase */ void AppModeGenericReceiver::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Remote Buttons
	{
		Buttons b;
		if(mReceiverCategoryForButtons.buttons.read(b)) {
			display::showButton(b);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
		}
	}

	// Check Remote PianoKeys and Octave
	{
		PianoKeys p;
		Octave o;
		bool pChanged = mReceiverCategoryForPianoKeys.pianoKeys.read(/* OUT */ p);
		bool oChanged = mReceiverCategoryForPianoKeys.octave.read(/* OUT */ o);
		if(pChanged || oChanged) {
			if(mBuzzer) {
				mBuzzer->playTone(/* INOUT */ p, o);
			}
			display::showBits(p);
		//	if(pChanged) {
		//		debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Piano Keys: 0x", string::hex(p).toCharArray());
		//	}
		//	if(oChanged) {
		//		debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Octave: 0x", string::hex(o).toCharArray());
		//	}
		}
	}
}

}	// microbit_dal_app_kit

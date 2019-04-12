/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Piano Key Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModePianoKeyController.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModePianoKeyController
*/

static const Features kAppMode = appMode::kPianoKeyController;

/* Component */ bool AppModePianoKeyController::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModePianoKeyController::AppModePianoKeyController()
	: AppModeBase("AppModePianoKeyController")
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

	addChild(mTouchPiano);
	addChild(mNeoPixel);
	addChild(mTransmitter);
}

/* AppModeBase */ void AppModePianoKeyController::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			mNeoPixel.setColorMapForIndicator(Color::black, Color::white);
			mNeoPixel.fillColorWithIndicatorRange(octave::kCenter);
			display::showBits(pianoKey::kNone);
		}
	}
	else if(source == MICROBIT_ID_GESTURE) {
		if(value == gesture::microBitGestureEventTiltLeft()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft);	// CREATE_AND_FIRE
			display::flashChar('<');
		}
		else if(value == gesture::microBitGestureEventTiltTop()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop);	// CREATE_AND_FIRE
			display::flashChar('^');
		}
		else if(value == gesture::microBitGestureEventTiltRight()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight);	// CREATE_AND_FIRE
			display::flashChar('>');
		}
		else if(value == gesture::microBitGestureEventTiltBottom()) {
			MicroBitEvent(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom);	// CREATE_AND_FIRE
			display::flashChar('v');
		}
	}
}

/* AppModeBase */ void AppModePianoKeyController::doHandlePeriodic100ms(uint32_t /* count */)
{
	// The current Octave
	Octave o = mTransmitterCategoryForPianoKeys.octave.value();

	// Check Local Buttons and update the latest Octave
	{
		Buttons b = button::readMicroBitButtons();
		if(mButtons.set(b)) {
			if((b & button::kLR) == button::kLR) {
				o = octave::kCenter;
			}
			else if(b & button::kL) {
				if(octave::kLowest < o) {
					o--;
				}
			}
			else if(b & button::kR) {
				if(o < octave::kHighest) {
					o++;
				}
			}
		}
	}

	// Update Remote PianoKeys and Octave
	{
		PianoKeys p;
		mTouchPiano.read(/* OUT */ &p);
		if(mTransmitterCategoryForPianoKeys.pianoKeys.set(p)) {
			display::showBits(p);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote PianoKeys: 0x", string::hex(p).toCharArray());
		}
		if(mTransmitterCategoryForPianoKeys.octave.set(o)) {
			mNeoPixel.fillColorWithIndicatorRange(o);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Octave: 0x", string::hex(o).toCharArray());
		}
		mTransmitterCategoryForPianoKeys.updateRemoteState();
	}
}

}	// microbit_dal_app_kit

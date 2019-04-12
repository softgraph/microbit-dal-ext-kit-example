/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Piano Player
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModePianoPlayer.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModePianoPlayer
*/

static const Features kAppMode = appMode::kPianoPlayer;

/* Component */ bool AppModePianoPlayer::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModePianoPlayer::AppModePianoPlayer()
	: AppModeBase("AppModePianoPlayer")
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	addChild(mTouchPiano);
	addChild(mNeoPixel);
}

/* AppModeBase */ void AppModePianoPlayer::doHandleEvent(const MicroBitEvent& event)
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
}

/* AppModeBase */ void AppModePianoPlayer::doHandlePeriodic100ms(uint32_t /* count */)
{
	// The current Octave
	Octave o = mOctave.value();

	// Check Buttons and update the latest Octave
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

	// Check PianoKeys and Octave
	{
		PianoKeys p;
		mTouchPiano.read(/* OUT */ &p);
		bool changedP = mPianoKeys.set(p);
		bool changedO = mOctave.set(o);
		if(changedP || changedO) {
			mBuzzer.playTone(/* INOUT */ p, o);
			if(changedP) {
				display::showBits(p);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Piano Keys: 0x", string::hex(p).toCharArray());
			}
			if(changedO) {
				mNeoPixel.fillColorWithIndicatorRange(o);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Octave: 0x", string::hex(o).toCharArray());
			}
		}
	}
}

}	// microbit_dal_app_kit

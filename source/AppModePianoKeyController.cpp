/// App Mode for Piano Key Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModePianoKeyController.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModePianoKeyController
*/

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

struct PianoKeysState {
	PianoKeys	latest	= pianoKey::kNone;
	PianoKeys	last	= pianoKey::kNone;
};

struct OctaveState {
	Octave	latest		= octave::kCenter;
	Octave	last		= octave::kCenter;
};

static const Features kAppMode = appMode::kPianoKeyController;

static ButtonsState		localButtons;
static PianoKeysState	localPianoKeys;
static OctaveState		localOctave;

/* Component */ bool AppModePianoKeyController::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModePianoKeyController::AppModePianoKeyController()
	: AppModeBase("AppModePianoKeyController")
{
}

/* Component */ void AppModePianoKeyController::start()
{
	AppModeBase::start();
	mTouchPiano.start();
	mNeoPixel.start();
	mRadio.start();

	if(feature::isConfigured(feature::kRemoteEventTx)) {
		// observe local events to trigger remote events
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT);
		listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT);
	}
}

/* Component */ void AppModePianoKeyController::stop()
{
	mRadio.stop();
	mNeoPixel.stop();
	mTouchPiano.stop();
	AppModeBase::stop();
}

/* AppModeBase */ void AppModePianoKeyController::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			mNeoPixel.setColorMapForIndicator(Color::black, Color::white);
			mNeoPixel.fillColorWithIndicatorRange(localOctave.latest);
			display::showBits(localPianoKeys.latest);
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

/* AppModeBase */ void AppModePianoKeyController::doHandlePeriodic100ms(uint32_t /* count */)
{
	//	check local buttons for local octave
	{
		ButtonsState& b = localButtons;
		OctaveState& o = localOctave;
		b.latest = button::readMicroBitButtons();
		if(b.last != b.latest) {
			//	check octave
			Octave octave = o.last;
			if((b.latest & button::kLR) == button::kLR) {
				octave = octave::kCenter;
			}
			else if(b.latest & button::kL) {
				if(octave::kLowest < octave) {
					octave--;
				}
			}
			else if(b.latest & button::kR) {
				if(octave < octave::kHighest) {
					octave++;
				}
			}
			o.latest = octave;
			b.last = b.latest;
		}
	}

	//	check local piano keys and octave
	{
		PianoKeysState& p = localPianoKeys;
		OctaveState& o = localOctave;
		mTouchPiano.read(/* OUT */ &p.latest);
		if((p.last != p.latest) || (o.last != o.latest)) {
			updateRemotePianoKeysToRadio(p.latest, o.latest);
			if(p.last != p.latest) {
				display::showBits(p.latest);
				p.last = p.latest;
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Piano Keys: 0x", string::hex(p.latest).toCharArray());
			}
			if(o.last != o.latest) {
				mNeoPixel.fillColorWithIndicatorRange(o.latest);
				o.last = o.latest;
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Octave: 0x", string::hex(o.latest).toCharArray());
			}
		}
	}
}

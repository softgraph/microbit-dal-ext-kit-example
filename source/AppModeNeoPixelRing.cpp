/// App Mode for NeoPixel Ring
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeNeoPixelRing.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeNeoPixelRing
*/

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

struct DirectionState {
	Direction	latest	= direction::kCenter;
	Direction	last	= direction::kCenter;
};

struct PianoKeysState {
	PianoKeys	latest	= pianoKey::kNone;
	PianoKeys	last	= pianoKey::kNone;
};

struct OctaveState {
	Octave	latest		= octave::kCenter;
	Octave	last		= octave::kCenter;
};

static const Features kAppMode1	= appMode::kNeoPixelRing;
static const Features kAppMode2	= appMode::kZipHalo;

static ButtonsState		localButtons;
static ButtonsState		remoteButtons;
static DirectionState	remoteDirection;
static PianoKeysState	remotePianoKeys;
static OctaveState		remoteOctave;

/* Component */ bool AppModeNeoPixelRing::isConfigured()
{
	Features configured = feature::configured();
	return (configured == kAppMode1) || (configured == kAppMode2);
}

AppModeNeoPixelRing::AppModeNeoPixelRing()
	: AppModeBase("AppModeNeoPixelRing")
	, mBuzzer(0)
{
	if(feature::isConfigured(feature::kBuzzer)) {
		ExtKit& g = ExtKit::global();
		mBuzzer = new Buzzer("BuzzerForNeoPixelRing", /* analogPort */ g.p2());
	}
}

AppModeNeoPixelRing::~AppModeNeoPixelRing()
{
	delete mBuzzer;
}

/* Component */ void AppModeNeoPixelRing::start()
{
	AppModeBase::start();
	mZipHalo.start();
	mNeoPixel.start();
	if(mBuzzer) {
		mBuzzer->start();
	}
	mRadio.start();
}

/* Component */ void AppModeNeoPixelRing::stop()
{
	mRadio.stop();
	if(mBuzzer) {
		mBuzzer->stop();
	}
	mNeoPixel.stop();
	mZipHalo.stop();
	AppModeBase::stop();
}

/* AppModeBase */ void AppModeNeoPixelRing::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			mNeoPixel.fillColorWithRainbow();
			mNeoPixel.show();
			setNeoPixelMode('F');
			display::showButton(button::kNone);
		}
	}
	else if(source == messageBusID::kRemoteEvent) {
		if(value == messageBusEvent::kRemoteTiltedLeft) {
			mNeoPixel.rotateLeft();
			mNeoPixel.show();
			display::flashChar('<');
		}
		else if(value == messageBusEvent::kRemoteTiltedRight) {
			mNeoPixel.rotateRight();
			mNeoPixel.show();
			display::flashChar('>');
		}
	}
}

/* AppModeBase */ void AppModeNeoPixelRing::doHandleRadioDatagramReceived(const ManagedString& /* received */)
{
	Buttons buttons = checkLatestRemoteButtons();
	if(buttons != button::kInvalid) {
		remoteButtons.latest = buttons;
	}

	Direction direction = checkLatestRemoteDirection();
	if(direction != direction::kInvalid) {
		remoteDirection.latest = direction;
	}

	PianoKeys pianoKeys = checkLatestRemotePianoKeys();
	if(pianoKeys != pianoKey::kInvalid) {
		remotePianoKeys.latest = pianoKeys;
	}

	Octave octave = checkLatestRemoteOctave();
	if(octave != octave::kInvalid) {
		remoteOctave.latest = octave;
	}
}

/* AppModeBase */ void AppModeNeoPixelRing::doHandlePeriodic100ms(uint32_t /* count */)
{
	//	check local buttons
	{
		ButtonsState& b = localButtons;
		b.latest = button::readMicroBitButtons();
		if(b.last != b.latest) {
			if(b.latest & button::kL) {
				mNeoPixel.rotateLeft();
				mNeoPixel.show();
			}
			else if(b.latest & button::kR) {
				mNeoPixel.rotateRight();
				mNeoPixel.show();
			}
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Loclal Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}

	//	check remote buttons
	{
		ButtonsState& b = remoteButtons;
		if(b.last != b.latest) {
			if((b.latest & button::kLR) == button::kLR) {
				mNeoPixel.resetMaxBrightness();
				mNeoPixel.show();
			}
			else if(b.latest & button::kL) {
				mNeoPixel.changeMaxBrightness(-5);
				mNeoPixel.show();
			}
			else if(b.latest & button::kR) {
				mNeoPixel.changeMaxBrightness(5);
				mNeoPixel.show();
			}
			else if(b.latest & button::kA) {
				setNeoPixelMode('A');
			}
			else if(b.latest & button::kB) {
				setNeoPixelMode('B');
			}
			else if(b.latest & button::kC) {
				setNeoPixelMode('C');
			}
			else if(b.latest & button::kD) {
				setNeoPixelMode('D');
			}
			else if(b.latest & button::kE) {
				setNeoPixelMode('E');
			}
			else if(b.latest & button::kF) {
				setNeoPixelMode('F');
			}
			display::showButton(b.latest);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}

	//	check remote direction
	{
		DirectionState& d = remoteDirection;
		if(d.last != d.latest) {
			{
				mNeoPixel.fillColorWithFocusDirection(d.latest);
				mNeoPixel.show();
			}
			display::showDirection(d.latest);
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Direction: 0x", string::hex(d.latest).toCharArray());
			d.last = d.latest;
		}
	}

	//	check remote piano keys
	{
		PianoKeysState& p = remotePianoKeys;
		OctaveState& o = remoteOctave;
		if((p.last != p.latest) || (o.last != o.latest)) {
			if(mBuzzer) {
				mBuzzer->playTone(/* INOUT */ p.latest, o.latest);
			}
			display::showBits(p.latest);
			if(p.last != p.latest) {
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Piano Keys: 0x", string::hex(p.latest).toCharArray());
			}
			if(o.last != o.latest) {
				debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Octave: 0x", string::hex(o.latest).toCharArray());
			}
			p.last = p.latest;
			o.last = o.latest;
		}
	}
}

void AppModeNeoPixelRing::setNeoPixelMode(char mode)
{
	switch(mode) {
		case 'A': {		// red focus
			mNeoPixel.setColorMapForFocus(Color::black, Color::red, Color::red, Color::red);
			break;
		}
		case 'B': {		// green focus
			mNeoPixel.setColorMapForFocus(Color::black, Color::lime, Color::lime, Color::lime);
			break;
		}
		case 'C': {		// blue focus
			mNeoPixel.setColorMapForFocus(Color::black, Color::blue, Color::blue, Color::blue);
			break;
		}
		case 'D': {		// fuchsia (magenta) focus
			mNeoPixel.setColorMapForFocus(Color::black, Color::fuchsia, Color::fuchsia, Color::fuchsia);
			break;
		}
		case 'E': {		// white focus
			mNeoPixel.setColorMapForFocus(Color::black, Color::white, Color::white, Color::white);
			break;
		}
		case 'F': {		// rainbow focus
			mNeoPixel.setRainbowMapForFocus();
			break;
		}
		default: {		// no operation
			return;
		}
	}
	mNeoPixel.show();
}

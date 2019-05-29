/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for NeoPixel Ring
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeNeoPixelRing.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeNeoPixelRing
*/

AppModeNeoPixelRing::AppModeNeoPixelRing()
	: AppModeBase("AppModeNeoPixelRing")
	, mBuzzer(0)
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	addChild(mZipHalo);
	addChild(mNeoPixel);
	addChild(mReceiver);
	if(feature::isConfigured(feature::kBuzzer)) {
		ExtKit& g = ExtKit::global();
		mBuzzer = new Buzzer("BuzzerForNeoPixelRing", /* analogPort */ g.p2());
		EXT_KIT_ASSERT_OR_PANIC(mBuzzer, kPanicOutOfMemory);

		addChild(*mBuzzer);
	}
}

AppModeNeoPixelRing::~AppModeNeoPixelRing()
{
	delete mBuzzer;
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
		if(value == messageBusEvent::kRemoteTiltLeft) {
			mNeoPixel.rotateLeft();
			mNeoPixel.show();
			display::flashChar('<');
		}
		else if(value == messageBusEvent::kRemoteTiltTop) {
			mNeoPixel.rotateLeft();
			mNeoPixel.show();
			display::flashChar('^');
		}
		else if(value == messageBusEvent::kRemoteTiltRight) {
			mNeoPixel.rotateRight();
			mNeoPixel.show();
			display::flashChar('>');
		}
		else if(value == messageBusEvent::kRemoteTiltBottom) {
			mNeoPixel.rotateRight();
			mNeoPixel.show();
			display::flashChar('v');
		}
	}
}

/* AppModeBase */ void AppModeNeoPixelRing::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Local Buttons
	{
		Buttons b = button::readMicroBitButtons();
		if(mButtons.set(b)) {
			if(b & button::kL) {
				mNeoPixel.rotateLeft();
				mNeoPixel.show();
			}
			else if(b & button::kR) {
				mNeoPixel.rotateRight();
				mNeoPixel.show();
			}
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Loclal Buttons: 0x", string::hex(b).toCharArray());
		}
	}

	// Check Remote Buttons
	{
		Buttons b;
		if(mReceiverCategoryForButtons.buttons.read(/* OUT */ b)) {
			if((b & button::kLR) == button::kLR) {
				mNeoPixel.resetMaxBrightness();
				mNeoPixel.show();
			}
			else if(b & button::kL) {
				mNeoPixel.changeMaxBrightness(-5);
				mNeoPixel.show();
			}
			else if(b & button::kR) {
				mNeoPixel.changeMaxBrightness(5);
				mNeoPixel.show();
			}
			else if(b & button::kA) {
				setNeoPixelMode('A');
			}
			else if(b & button::kB) {
				setNeoPixelMode('B');
			}
			else if(b & button::kC) {
				setNeoPixelMode('C');
			}
			else if(b & button::kD) {
				setNeoPixelMode('D');
			}
			else if(b & button::kE) {
				setNeoPixelMode('E');
			}
			else if(b & button::kF) {
				setNeoPixelMode('F');
			}
			display::showButton(b);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
		}
	}

	// Check Remote Direction
	{
		Direction d;
		if(mReceiverCategoryForButtons.direction.read(/* OUT */ d)) {
			mNeoPixel.fillColorWithFocusDirection(d);
			mNeoPixel.show();
			display::showDirection(d);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Direction: 0x", string::hex(d).toCharArray());
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

}	// microbit_dal_app_kit

/// App Mode for Piano Player
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_PIANO_PLAYER_H
#define APP_MODE_PIANO_PLAYER_H

#include "ExtKitTouchPiano.h"
#include "ExtKitButton.h"
#include "ExtKitOctave.h"
#include "ExtKitPianoKey.h"

#include "AppModeBase.h"

/// App Mode for Piano Player
class AppModePianoPlayer : public AppModeBase
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModePianoPlayer();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	/// Touch Piano board
	microbit_dal_ext_kit::TouchPiano	mTouchPiano;

	/// NeoPixel For Touch Piano board
	microbit_dal_ext_kit::NeoPixelForTouchPiano	mNeoPixel;

	/// Buzzer For Touch Piano board
	microbit_dal_ext_kit::BuzzerForTouchPiano	mBuzzer;

	/// State For Buttons
	microbit_dal_ext_kit::StateForButtons	mButtons;

	/// State For Piano Keys
	microbit_dal_ext_kit::StateForPianoKeys	mPianoKeys;

	/// State For Octave
	microbit_dal_ext_kit::StateForOctave	mOctave;

};	// AppModePianoPlayer

#endif	// APP_MODE_PIANO_PLAYER_H

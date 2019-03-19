/// App Mode for Piano Player
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_PIANO_PLAYER_H
#define APP_MODE_PIANO_PLAYER_H

#include "ExtKitTouchPiano.h"
#include "AppModeBase.h"

/// App Mode for Piano Player
class AppModePianoPlayer : public AppModeBase
{
public:
	/// Inherited.
	static /* Component */ bool isConfigured();

	/// Constructor.
	AppModePianoPlayer();

	/// Inherited.
	/* Component */ void start();

	/// Inherited.
	/* Component */ void stop();

protected:
	/// Inherited.
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited.
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	microbit_dal_ext_kit::TouchPiano			mTouchPiano;
	microbit_dal_ext_kit::NeoPixelForTouchPiano	mNeoPixel;
	microbit_dal_ext_kit::BuzzerForTouchPiano	mBuzzer;

};	// AppModePianoPlayer

#endif	// APP_MODE_PIANO_PLAYER_H

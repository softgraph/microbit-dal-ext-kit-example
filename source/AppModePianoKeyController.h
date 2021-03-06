/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Piano Key Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_PIANO_KEY_CONTROLLER_H
#define APP_MODE_PIANO_KEY_CONTROLLER_H

#include "ExtKitRemoteState.h"
#include "ExtKitTouchPiano.h"

#include "AppKitRemoteState.h"
#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode for Piano Key Controller
class AppModePianoKeyController : public AppModeBase
{
public:
	/// Constructor
	AppModePianoKeyController();

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

	/// Remote State Transmitter
	microbit_dal_ext_kit::remoteState::Transmitter	mTransmitter;

	/// Remote State Transmitter Category For Piano Keys
	RemoteStateTransmitterCategoryForPianoKeys	mTransmitterCategoryForPianoKeys;

	/// State For Buttons
	microbit_dal_ext_kit::StateForButtons	mButtons;

};	// AppModePianoKeyController

}	// microbit_dal_app_kit

#endif	// APP_MODE_PIANO_KEY_CONTROLLER_H

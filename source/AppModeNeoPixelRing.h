/// An example for using microbit-dal-ext-kit
/**	@package	microbit_dal_app_kit
*/

/// App Mode for NeoPixel Ring
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_NEOPIXEL_RING_H
#define APP_MODE_NEOPIXEL_RING_H

#include "ExtKitButton.h"
#include "ExtKitBuzzer.h"
#include "ExtKitDirection.h"
#include "ExtKitRemoteState.h"
#include "ExtKitZipHalo.h"

#include "AppKitRemoteState.h"
#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode for NeoPixel Ring
class AppModeNeoPixelRing : public AppModeBase
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModeNeoPixelRing();

	/// Destructor
	~AppModeNeoPixelRing();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	/// Set NeoPixel Mode
	void setNeoPixelMode(char mode);

	/// Zip Halo board
	microbit_dal_ext_kit::ZipHalo	mZipHalo;

	/// NeoPixel For Zip Halo board
	microbit_dal_ext_kit::NeoPixelForZipHalo	mNeoPixel;

	/// Generic Buzzer
	microbit_dal_ext_kit::Buzzer*	mBuzzer;

	/// Remote State Receiver
	microbit_dal_ext_kit::remoteState::Receiver	mReceiver;

	/// Remote State Receiver Category For Buttons
	RemoteStateReceiverCategoryForButtons	mReceiverCategoryForButtons;

	/// Remote State Receiver Category For Piano Keys
	RemoteStateReceiverCategoryForPianoKeys	mReceiverCategoryForPianoKeys;

	/// State For Buttons
	microbit_dal_ext_kit::StateForButtons	mButtons;

};	// AppModeNeoPixelRing

}	// microbit_dal_app_kit

#endif	// APP_MODE_NEOPIXEL_RING_H

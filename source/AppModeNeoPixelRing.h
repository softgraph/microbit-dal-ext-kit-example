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
#include "AppKitState.h"
#include "AppModeBase.h"

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
	/* AppModeBase */ void doHandleRadioDatagramReceived(const ManagedString& received);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	void setNeoPixelMode(char mode);

	microbit_dal_ext_kit::ZipHalo	mZipHalo;

	microbit_dal_ext_kit::NeoPixelForZipHalo	mNeoPixel;

	microbit_dal_ext_kit::Buzzer*	mBuzzer;

	microbit_dal_ext_kit::RemoteState::Receiver	mReceiver;

	RemoteStateReceiverForButtons	mReceiverForButtons;

	RemoteStateReceiverForPianoKeys	mReceiverForPianoKeys;

	StateForButtons	mButtons;

};	// AppModeNeoPixelRing

#endif	// APP_MODE_NEOPIXEL_RING_H

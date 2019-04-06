/// An example for using microbit-dal-ext-kit
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Generic Receiver
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_GENERIC_RECEIVER_H
#define APP_MODE_GENERIC_RECEIVER_H

#include "ExtKitRemoteState.h"
#include "ExtKitBuzzer.h"

#include "AppKitRemoteState.h"
#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode for Generic Receiver
class AppModeGenericReceiver : public AppModeBase
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModeGenericReceiver();

	/// Destructor
	~AppModeGenericReceiver();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	/// Generic Buzzer
	microbit_dal_ext_kit::Buzzer*	mBuzzer;

	/// Remote State Receiver
	microbit_dal_ext_kit::remoteState::Receiver	mReceiver;

	/// Remote State Receiver Category For Buttons
	RemoteStateReceiverCategoryForButtons	mReceiverCategoryForButtons;

	/// Remote State Receiver Category For Piano Keys
	RemoteStateReceiverCategoryForPianoKeys	mReceiverCategoryForPianoKeys;

};	// AppModeGenericReceiver

}	// microbit_dal_app_kit

#endif	// APP_MODE_GENERIC_RECEIVER_H

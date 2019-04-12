/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Joystick Controller
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_JOYSTICK_CONTROLLER_H
#define APP_MODE_JOYSTICK_CONTROLLER_H

#include "ExtKitJoystickBit.h"
#include "ExtKitRemoteState.h"

#include "AppKitRemoteState.h"
#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode for Joystick Controller
class AppModeJoystickController : public AppModeBase
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModeJoystickController();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

private:
	/// Joystick:bit board
	microbit_dal_ext_kit::JoystickBit	mJoystickBit;

	/// Remote State Transmitter
	microbit_dal_ext_kit::remoteState::Transmitter	mTransmitter;

	/// Remote State Transmitter Category For Buttons
	RemoteStateTransmitterCategoryForButtons	mTransmitterCategoryForButtons;

};	// AppModeJoystickController

}	// microbit_dal_app_kit

#endif	// APP_MODE_JOYSTICK_CONTROLLER_H

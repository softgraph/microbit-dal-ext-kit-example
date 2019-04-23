/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Motors
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_MOTORS_H
#define APP_MODE_MOTORS_H

#include "ExtKitDirection.h"
#include "ExtKitMotoBit.h"
#include "ExtKitRemoteState.h"
#include "ExtKitSonar.h"

#include "AppKitRemoteState.h"
#include "AppModeBase.h"

namespace microbit_dal_app_kit {

///	%Sonar Distance in centimeters
typedef uint16_t	SonarDistance;

/// `StateChange` specialization for `#SonarDistance`
class StateChangeForSonarDistance : public microbit_dal_ext_kit::StateChange<SonarDistance>
{
public:
	/// Constructor
	StateChangeForSonarDistance();

};	// StateChangeForSonarDistance

/// App Mode for Motors
class AppModeMotors : public AppModeBase, protected microbit_dal_ext_kit::Sonar::HandlerProtocol
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModeMotors();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

	/// Inherited
	/* Sonar::HandlerProtocol */ void handleSonarEcho(uint32_t duration /* in microseconds*/);

private:
	/// Control Moto:bit Using Direction
	bool controlMotoBitUsingDirection(microbit_dal_ext_kit::Direction direction);

	/// Moto:bit board
	microbit_dal_ext_kit::MotoBit	mMotoBit;

	/// Generic Sonar
	microbit_dal_ext_kit::Sonar	mSonar;

	/// Remote State Receiver
	microbit_dal_ext_kit::remoteState::Receiver	mReceiver;

	/// Remote State Receiver Category For Buttons
	RemoteStateReceiverCategoryForButtons	mReceiverCategoryForButtons;

	/// State For Local Buttons
	microbit_dal_ext_kit::StateForButtons	mButtons;

	/// State Change For Sonar Distance
	StateChangeForSonarDistance	mSonarDistance;

};	// AppModeMotors

}	// microbit_dal_app_kit

#endif	// APP_MODE_MOTORS_H

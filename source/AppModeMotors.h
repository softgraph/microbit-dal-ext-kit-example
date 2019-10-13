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
#include "ExtKitMotorsLR.h"
#include "ExtKitNeoPixel.h"
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
	/// Control Motors Using Direction
	bool controlMotorsUsingDirection(microbit_dal_ext_kit::Direction direction);

	/// Motors LR
	microbit_dal_ext_kit::MotorsLR*	mMotorsLR;

	/// NeoPixel
	microbit_dal_ext_kit::NeoPixel*	mNeoPixel;

	/// Generic Sonar
	microbit_dal_ext_kit::Sonar*	mSonar;

	/// Remote State Receiver
	microbit_dal_ext_kit::remoteState::Receiver	mReceiver;

	/// Remote State Receiver Category For Buttons
	RemoteStateReceiverCategoryForButtons	mReceiverCategoryForButtons;

	/// State For Local Buttons
	microbit_dal_ext_kit::StateForButtons	mButtons;

	/// State Change For Sonar Distance
	StateChangeForSonarDistance	mSonarDistance;

};	// AppModeMotors

/// An Component which provides the support for ElecFreaks' ring:bit car (v2) board
/**
	@reference	ElecFreaks ring:bit car (v2) for micro:bit
		- https://www.elecfreaks.com/estore/elecfreaks-ring-bit-car-v2-for-micro-bit-without-micro-bit.html
		- https://www.elecfreaks.com/learn-en/microbitKit/ring_bit_v2/index.html
*/
class RingBitCar : public microbit_dal_ext_kit::MotorsLR
{
public:
	/// Constructor
	RingBitCar();

protected:
	/// Inherited
	/* MotorsLR */ int /* ErrorCode */ setMotorSpeed(microbit_dal_ext_kit::MotorsLR::Motor motor, microbit_dal_ext_kit::MotorsLR::MotorDirection direction, int speedInPercent);

private:
	/// Servo Left
	MicroBitPin&	mServoL;

	/// Servo Right
	MicroBitPin&	mServoR;

};	// RingBitCar

}	// microbit_dal_app_kit

#endif	// APP_MODE_MOTORS_H

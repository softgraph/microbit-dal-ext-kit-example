/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Motors
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeMotors.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	StateChangeForSonarDistance
*/

StateChangeForSonarDistance::StateChangeForSonarDistance()
	: StateChange<SonarDistance>(0)
{
}

/**	@class	AppModeMotors
*/

AppModeMotors::AppModeMotors()
	: AppModeBase("AppModeMotors")
	, mMotorsLR(0)
	, mMotorsPT(0)
	, mNeoPixel(0)
	, mSonar(0)
{
	if(feature::isConfigured(feature::kMotoBit)) {
		mMotorsLR = new MotoBit(false);
		EXT_KIT_ASSERT_OR_PANIC(mMotorsLR, panic::kOutOfMemory);
	}
	else if(feature::isConfigured(feature::kRingBitCar)) {
		mMotorsLR = new RingBitCar();
		EXT_KIT_ASSERT_OR_PANIC(mMotorsLR, panic::kOutOfMemory);

		if(feature::isConfigured(feature::kNeoPixel)) {
			ExtKit& g = ExtKit::global();
			mNeoPixel = new NeoPixel("NeoPixelForRingBitCar",
									 /* ledPort */ g.p0(),
									 /* ledCount */ 10);
			EXT_KIT_ASSERT_OR_PANIC(mNeoPixel, panic::kOutOfMemory);
		}
		else if(feature::isConfigured(feature::kSonar)) {
			ExtKit& g = ExtKit::global();
			mSonar = new Sonar("SonarForRingBitCar",
							   /* triggerOutput */ g.p0(),
							   /* echoInput */ g.p0(), MICROBIT_ID_IO_P0, *this,
							   /* echoInputStabilizer */ 1);
			EXT_KIT_ASSERT_OR_PANIC(mSonar, panic::kOutOfMemory);
		}
		else {
			ExtKit& g = ExtKit::global();
			mNeoPixel = new NeoPixel("NeoPixelForRingBitCar",
									 /* ledPort */ g.p0(),
									 /* ledCount */ 2);
			EXT_KIT_ASSERT_OR_PANIC(mNeoPixel, panic::kOutOfMemory);
		}
	}
	else if(feature::isConfigured(feature::kPanTiltBracket)) {
		mMotorsPT = new PanTiltBracket();
		EXT_KIT_ASSERT_OR_PANIC(mMotorsPT, panic::kOutOfMemory);
	}

	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kN },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kE },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kW },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBase + direction::kS },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	if(mMotorsPT) {
		static const PeriodDef periodicObservers[] = {
			{ PeriodicObserver::kUnit20ms, PeriodicObserver::kPriorityMedium },
			{ PeriodicObserver::kUnit100ms, PeriodicObserver::kPriorityMedium },
			{ PeriodicObserver::kUnitNever, PeriodicObserver::kPriorityVeryLow }	// END OF TABLE
		};
		selectPeriodicObservers(periodicObservers);
	}

	if(mMotorsLR) {
		addChild(*mMotorsLR);
	}
	if(mMotorsPT) {
		addChild(*mMotorsPT);
	}
	if(mNeoPixel) {
		addChild(*mNeoPixel);
	}
	if(mSonar) {
		addChild(*mSonar);
	}
	addChild(mReceiver);
}

/* AppModeBase */ void AppModeMotors::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			controlMotorsPTUsingButtons(button::kStart);
			display::showButton(button::kNone);
			if(mNeoPixel) {
				mNeoPixel->fillColor(Color::white);
				mNeoPixel->show();
			}
		}
	}
	else if(source == messageBusID::kRemoteEvent) {
		for(int i = 0; i < 4; i++) {
			Direction d = direction::kFour[i];
			if(value == messageBusEvent::kRemoteTiltBase + d) {
				display::showDirection(d, display::kSolidTriangle, 500 /* milliseconds */);
				break;
			}
		}
	}
}

/* Sonar::HandlerProtocol */ void AppModeMotors::handleSonarEcho(uint32_t duration /* in microseconds*/)
{
	const uint32_t kSoundSpeed = 343;	// 343 m/s
	SonarDistance value /* in centimeters */ = (duration * kSoundSpeed) / 2 / 10000;
	mSonarDistance.set(value);
}

/* AppModeBase */ void AppModeMotors::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Sonar Echo
	if(mSonar) {
		SonarDistance lastValue = mSonarDistance.lastValue();
		SonarDistance value;
		if(mSonarDistance.read(/* OUT */ value)) {
			if((value < 10) && (value < lastValue)) {
				const Direction d = direction::kStop;
				controlMotorsLRUsingDirection(d);
				display::showDirection(d);
			}
			else {
				display::showNumber(value);
			}
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Sonar Distance in centimeters: ", string::dec(value).toCharArray());
		}
		mSonar->trigger();
	}

	// Check Remote Direction
	{
		Direction d;
		if(mReceiverCategoryForButtons.direction.read(/* OUT */ d)) {
			controlMotorsLRUsingDirection(d);
			display::showDirection(d);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Direction: 0x", string::hex(d).toCharArray());
		}
	}

	// Check Local Buttons
	{
		Buttons b = button::readMicroBitButtons();
		if(mButtons.set(b)) {
			Direction d = direction::kCenter;
			if((b & button::kLR) == button::kLR) {
				d = direction::kN;
			}
			else if(b & button::kL) {
				d = direction::kLF;
			}
			else if(b & button::kR) {
				d = direction::kRF;
			}
			controlMotorsLRUsingDirection(d);
			display::showDirection(d);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Buttons: 0x", string::hex(b).toCharArray());
		}
	}
}

/* AppModeBase */ void AppModeMotors::doHandlePeriodic20ms(uint32_t /* count */)
{
	// Check Remote Buttons
	{
		const Buttons kTiltOrPan = button::kTiltU | button::kTiltD | button::kPanL | button::kPanR;
		Buttons b;
		if(mReceiverCategoryForButtons.buttons.read(/* OUT */ b)) {
			mButtonPressedDuration20ms = 0;
			controlMotorsPTUsingButtons(b);
			display::showButton(b);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
		}
		else if((b && kTiltOrPan) != 0) {
			const int kLongPressedDuration20ms = 25;	// 500 ms
			mButtonPressedDuration20ms++;
			if(kLongPressedDuration20ms < mButtonPressedDuration20ms) {
				controlMotorsPTUsingButtons(b);
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons Pressed Duration: ", string::dec(mButtonPressedDuration20ms).toCharArray());
			}
		}
	}
}

bool AppModeMotors::controlMotorsLRUsingDirection(Direction direction)
{
	if(!mMotorsLR) {
		return false;
	}

	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeMotors::controlMotorsLRUsingDirection() with direction 0x", string::hex(direction).toCharArray());
	const MotorsLR::MotorDirection	F = MotorsLR::kForward;
	const MotorsLR::MotorDirection	B = MotorsLR::kBackward;
	const int /* speedInPercent */	H = 100;
	const int /* speedInPercent */	L = 70;
	switch(direction) {
		case direction::kCenter: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: -");
			mMotorsLR->setMotorSpeed(F, F, 0, 0);
			return true;
		}
		case direction::kN: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: N");
			mMotorsLR->setMotorSpeed(F, F, H, H);
			return true;
		}
		case direction::kE: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: E");
			mMotorsLR->setMotorSpeed(F, B, H, H);
			return true;
		}
		case direction::kW: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: W");
			mMotorsLR->setMotorSpeed(B, F, H, H);
			return true;
		}
		case direction::kS: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: S");
			mMotorsLR->setMotorSpeed(B, B, H, H);
			return true;
		}
		case direction::kNE: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NE");
			mMotorsLR->setMotorSpeed(F, F, H, L);
			return true;
		}
		case direction::kNW: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NW");
			mMotorsLR->setMotorSpeed(F, F, L, H);
			return true;
		}
		case direction::kSE: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SE");
			mMotorsLR->setMotorSpeed(B, B, H, L);
			return true;
		}
		case direction::kSW: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SW");
			mMotorsLR->setMotorSpeed(B, B, L, H);
			return true;
		}
		case direction::kLF: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LF");
			mMotorsLR->setMotorSpeed(F, F, H, 0);
			return true;
		}
		case direction::kLB: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LB");
			mMotorsLR->setMotorSpeed(B, B, H, 0);
			return true;
		}
		case direction::kRF: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RF");
			mMotorsLR->setMotorSpeed(F, F, 0, H);
			return true;
		}
		case direction::kRB: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RB");
			mMotorsLR->setMotorSpeed(B, B, 0, H);
			return true;
		}
		case direction::kStop: {
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: Stop");
			mMotorsLR->setMotorSpeed(F, F, 0, 0);
			return true;
		}
		default: {
			// keep the current direction and speed
			return true;
		}
	}
	return false;
}

bool AppModeMotors::controlMotorsPTUsingButtons(Buttons buttons)
{
	if(!mMotorsPT) {
		return false;
	}

	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeMotors::controlMotorsPTUsingButtons() with buttons 0x", string::hex(buttons).toCharArray());
	const Motors::Motor	P = MotorsPT::kPan;
	const Motors::Motor	T = MotorsPT::kTilt;
	const int /* angleInDegree */	Center = 90;
	const int /* angleInDegree */	Inc = 3;
	const int /* angleInDegree */	Dec = -3;
	if(buttons & button::kTiltU) {
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Tilt: -");
		mMotorsPT->incrementMotorAngle(T, Dec);
		return true;
	}
	else if(buttons & button::kTiltD) {
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Tilt: +");
		mMotorsPT->incrementMotorAngle(T, Inc);	
		return true;
	}
	else if(buttons & button::kPanR) {
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Pan: -");
		mMotorsPT->incrementMotorAngle(P, Dec);
		return true;
	}
	else if(buttons & button::kPanL) {
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Pan: +");
		mMotorsPT->incrementMotorAngle(P, Inc);
		return true;
	}
	else if(buttons & button::kStart) {
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Pan: Center");
		mMotorsPT->updateMotorAngle(P, Center);
		debug_sendLine(EXT_KIT_DEBUG_ACTION "Tilt: Center");
		mMotorsPT->updateMotorAngle(T, Center);
		return true;
	}
	return false;
}

/**	@class	RingBitCar
	@reference	Ring:bit Car Package
		- https://makecode.microbit.org/pkg/tinkertanker/pxt-ringbitcar
	@reference	Tinkertanker/pxt-ringbitcar/ringbitcar.ts (MIT license)
		- https://github.com/Tinkertanker/pxt-ringbitcar
		- https://github.com/Tinkertanker/pxt-ringbitcar/blob/master/ringbitcar.ts
*/

RingBitCar::RingBitCar()
	: MotorsLR("RingBitCar")
	, mServoL(ExtKit::global().p1())
	, mServoR(ExtKit::global().p2())
{
	configureMotors();
}

/* Motors */ int /* ErrorCode */ RingBitCar::setMotorSpeed(Motors::Motor motor, Motors::MotorDirection direction, int speedInPercent)
{
	static const int kServoCenter	= 1500;	// microseconds
	static const int kServoRange	= 1800;	// microseconds
	// Servo Value 0°	=  600 (1500 - 900) microseconds
	// Servo Value 90°	= 1500 microseconds
	// Servo Value 180°	= 2400 (1500 + 900) microseconds

	static const int kCenter	= 90;	// °
	static const int kOffset	= 10;	// °
	static const int kRange		= 80;	// °
	// Servo Value 0-80°	= rotate clockwise
	// Servo Value 90°		= stop
	// Servo Value 100-180°	= rotate anticlockwise

	if(speedInPercent == 0) {
		switch(motor) {
			case kLeft: {
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Left speed: 0");
				return mServoL.setDigitalValue(0);
			}
			case kRight: {
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Right speed: 0");
				return mServoR.setDigitalValue(0);
			}
		}
	}
	else {
		int speed = kOffset + speedInPercent * kRange / 100;
		int value = kCenter;
		switch(motor) {
			case kLeft: {
				value += (direction == kForward) ? speed : - speed;
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Left speed: ", string::dec(value).toCharArray());
				return mServoL.setServoValue(value, kServoRange, kServoCenter);
			}
			case kRight: {
				value += (direction == kForward) ? - speed : speed;
				//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Right speed: ", string::dec(value).toCharArray());
				return mServoR.setServoValue(value, kServoRange, kServoCenter);
			}
		}
	}

	return MICROBIT_NOT_SUPPORTED;
}

/**	@class	PanTiltBracket
*/

PanTiltBracket::PanTiltBracket()
	: MotorsPT("PanTiltBracket")
	, mServoP(ExtKit::global().p1())
	, mServoT(ExtKit::global().p2())
{
	configureMotors();
}

/* Motors */ int /* ErrorCode */ PanTiltBracket::setMotorAngle(microbit_dal_ext_kit::Motors::Motor motor, int angleInDegree)
{
	switch(motor) {
		case kPan: {
			static const int kServoCenter	= 1500;	// microseconds
			static const int kServoRange	= 2000;	// microseconds
			// Servo Value 0°	=  500 (1500 - 1000) microseconds
			// Servo Value 90°	= 1500 microseconds
			// Servo Value 180°	= 2500 (1500 + 1000) microseconds

			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Pan angle: ", string::dec(angleInDegree).toCharArray());
			return mServoP.setServoValue(angleInDegree, kServoRange, kServoCenter);
		}
		case kTilt: {
			static const int kServoCenter	= 1500;	// microseconds
			static const int kServoRange	= 1600;	// microseconds
			// Servo Value 0°	=  700 (1500 - 800) microseconds
			// Servo Value 90°	= 1500 microseconds
			// Servo Value 180°	= 2300 (1500 + 800) microseconds

			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Tilt angle: ", string::dec(angleInDegree).toCharArray());
			return mServoT.setServoValue(angleInDegree, kServoRange, kServoCenter);
		}
	}

	return MICROBIT_NOT_SUPPORTED;
}

}	// microbit_dal_app_kit

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
	, mNeoPixel(0)
	, mSonar(0)
{
	if(feature::isConfigured(feature::kMotoBit)) {
		mMotorsLR = new MotoBit(false);
		EXT_KIT_ASSERT_OR_PANIC(mMotorsLR, kPanicOutOfMemory);
	}
	else if(feature::isConfigured(feature::kServoMotorsLR)) {
		mMotorsLR = new RingBitCar();
		EXT_KIT_ASSERT_OR_PANIC(mMotorsLR, kPanicOutOfMemory);

		if(feature::isConfigured(feature::kNeoPixel)) {
			mNeoPixel = new NeoPixelForRingBitCar(10);
		}
#if 0
		else if(feature::isConfigured(feature::kSonar)) {
			ExtKit& g = ExtKit::global();
			mSonar = new Sonar("SonarForRingBitCar",
							   /* triggerOutput */ g.p1(),
							   /* echoInput */ g.p0(), MICROBIT_ID_IO_P0, *this,
							   /* echoInputStabilizer */ 1);
			EXT_KIT_ASSERT_OR_PANIC(mSonar, kPanicOutOfMemory);
		}
#endif
		else {
			mNeoPixel = new NeoPixelForRingBitCar(2);
		}
	}

	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	if(mMotorsLR) {
		addChild(*mMotorsLR);
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
			display::showButton(button::kNone);
		}
	}
	else if(source == messageBusID::kRemoteEvent) {
		if(value == messageBusEvent::kRemoteTiltLeft) {
			display::flashChar('<');
		}
		else if(value == messageBusEvent::kRemoteTiltTop) {
			display::flashChar('^');
		}
		else if(value == messageBusEvent::kRemoteTiltRight) {
			display::flashChar('>');
		}
		else if(value == messageBusEvent::kRemoteTiltBottom) {
			display::flashChar('v');
		}
	}
}

/* Sonar::HandlerProtocol */ void AppModeMotors::handleSonarEcho(uint32_t duration /* in microseconds*/)
{
	const uint32_t kSoundSpeed = 343;			// 343 m/s
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
				controlMotorsUsingDirection(d);
				display::showDirection(d);
			}
			else {
				display::showNumber(value);
			}
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Sonar Distance in centimeters: ", ManagedString((int) value).toCharArray());
		}
		mSonar->trigger();
	}

	// Check Remote Buttons
	{
		Buttons b;
		if(mReceiverCategoryForButtons.buttons.read(/* OUT */ b)) {
			display::showButton(b);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b).toCharArray());
		}
	}

	// Check Remote Direction
	{
		Direction d;
		if(mReceiverCategoryForButtons.direction.read(/* OUT */ d)) {
			controlMotorsUsingDirection(d);
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
			controlMotorsUsingDirection(d);
			display::showDirection(d);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Buttons: 0x", string::hex(b).toCharArray());
		}
	}
}

bool AppModeMotors::controlMotorsUsingDirection(Direction direction)
{
	if(!mMotorsLR) {
		return false;
	}

	const MotorsLR::MotorDirection	F = MotorsLR::kForward;
	const MotorsLR::MotorDirection	B = MotorsLR::kBackward;
	const int	H = 50;	// 50; // speedInPercent - high
	const int	L = 25;	// 25; // speedInPercent - low
	switch(direction) {
		case direction::kCenter:
			mMotorsLR->setMotorSpeed(F, F, 0, 0);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: -");
			break;
		case direction::kN:
			mMotorsLR->setMotorSpeed(F, F, H, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: N");
			break;
		case direction::kE:
			mMotorsLR->setMotorSpeed(F, B, H, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: E");
			break;
		case direction::kW:
			mMotorsLR->setMotorSpeed(B, F, H, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: W");
			break;
		case direction::kS:
			mMotorsLR->setMotorSpeed(B, B, H, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: S");
			break;
		case direction::kNE:
			mMotorsLR->setMotorSpeed(F, F, H, L);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NE");
			break;
		case direction::kNW:
			mMotorsLR->setMotorSpeed(F, F, L, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NW");
			break;
		case direction::kSE:
			mMotorsLR->setMotorSpeed(B, B, H, L);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SE");
			break;
		case direction::kSW:
			mMotorsLR->setMotorSpeed(B, B, L, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SW");
			break;
		case direction::kLF:
			mMotorsLR->setMotorSpeed(F, F, H, 0);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LF");
			break;
		case direction::kLB:
			mMotorsLR->setMotorSpeed(B, B, H, 0);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LB");
			break;
		case direction::kRF:
			mMotorsLR->setMotorSpeed(F, F, 0, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RF");
			break;
		case direction::kRB:
			mMotorsLR->setMotorSpeed(B, B, 0, H);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RB");
			break;
		case direction::kStop:
			mMotorsLR->setMotorSpeed(F, F, 0, 0);	debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: Stop");
			break;
	}
	return true;
}

/**	@class	RingBitCar
	@reference	Tinkertanker pxt-ringbitcar ringbitcar.ts (MIT license)
		- https://makecode.microbit.org/pkg/tinkertanker/pxt-ringbitcar
		- https://github.com/Tinkertanker/pxt-ringbitcar
		- https://github.com/Tinkertanker/pxt-ringbitcar/blob/master/ringbitcar.ts
*/

RingBitCar::RingBitCar()
	: MotorsLR("RingBitCar")
	, mServoL(ExtKit::global().p1())
	, mServoR(ExtKit::global().p2())
{
}

/* MotorsLR */ int RingBitCar::setMotorSpeed(MotorsLR::Motor motor, MotorsLR::MotorDirection direction, int speedInPercent)	// returns MICROBIT_INVALID_PARAMETER, MICROBIT_NOT_SUPPORTED, MICROBIT_I2C_ERROR or MICROBIT_OK
{
	// range: 600-1400, 1500, 1600-2400
	static const int kCenter = 1500;	// microseconds
	static const int kOffset = 100;		// microseconds
	static const int kRatio = 8;		// microseconds for 1 percent

	int speed = kOffset + kRatio * speedInPercent;
	if(motor == kLeft) {
		return mServoL.setServoPulseUs(kCenter + (direction == kForward) ? speed : - speed);
	}
	else {
		return mServoR.setServoPulseUs(kCenter + (direction == kForward) ? - speed : speed);
	}
}

/**	@class	NeoPixelForRingBitCar
*/

NeoPixelForRingBitCar::NeoPixelForRingBitCar(int ledCount)
	: NeoPixel("NeoPixelForRingBitCar", /* ledPort */ ExtKit::global().p0(), ledCount)
{
}

}	// microbit_dal_app_kit

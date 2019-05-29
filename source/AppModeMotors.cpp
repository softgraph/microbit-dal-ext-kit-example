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
	, mSonar(ExtKit::global().p1(), ExtKit::global().p0(), MICROBIT_ID_IO_P0, *this)
{
	mRawSonarDuration[0] = 0;
	mRawSonarDuration[1] = 0;
	mRawSonarDuration[2] = 0;
	mRawSonarDuration[3] = 0;

	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltLeft },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltTop },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltRight },
		{ messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltBottom },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);

	addChild(mMotoBit);
	addChild(mSonar);
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
	// Apply the upper limit.
	const uint32_t kMaxDuration = 36 * 1000;	// 36 ms
	if(duration > kMaxDuration) {
		duration = kMaxDuration;
	}

	mRawSonarDuration[3] = mRawSonarDuration[2];
	mRawSonarDuration[2] = mRawSonarDuration[1];
	mRawSonarDuration[1] = mRawSonarDuration[0];
	mRawSonarDuration[0] = duration;

	duration = (mRawSonarDuration[0] + mRawSonarDuration[1]) / 2;	// the average of the latest two samples

	const uint32_t kSoundSpeed = 343;			// 343 m/s
	SonarDistance value /* in centimeters */ = (duration * kSoundSpeed) / 2 / 10000;
	mSonarDistance.set(value);
}

/* AppModeBase */ void AppModeMotors::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Sonar Echo
	{
		SonarDistance lastValue = mSonarDistance.lastValue();
		SonarDistance value;
		if(mSonarDistance.read(/* OUT */ value)) {
			if((value < 10) && (value < lastValue)) {
				const Direction d = direction::kStop;
				controlMotoBitUsingDirection(d);
				display::showDirection(d);
			}
			else {
				display::showNumber(value);
			}
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Sonar Duration in microseconds: ", ManagedString((int) mRawSonarDuration[0]).toCharArray());
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Sonar Distance in centimeters: ", ManagedString((int) value).toCharArray());
		}
		mSonar.trigger();
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
			controlMotoBitUsingDirection(d);
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
			controlMotoBitUsingDirection(d);
			display::showDirection(d);
		//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Local Buttons: 0x", string::hex(b).toCharArray());
		}
	}
}

bool AppModeMotors::controlMotoBitUsingDirection(Direction direction)
{
	const MotoBit::MotorDirection	F = MotoBit::kForward;
	const MotoBit::MotorDirection	B = MotoBit::kBackward;
	const int	H = 50;	// 50; // speedInPercent - high
	const int	L = 25;	// 25; // speedInPercent - low
	switch(direction) {
		case direction::kCenter:	mMotoBit.setMotorSpeed(F, F, 0, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: -");		break;
		case direction::kN:			mMotoBit.setMotorSpeed(F, F, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: N");		break;
		case direction::kE:			mMotoBit.setMotorSpeed(F, B, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: E");		break;
		case direction::kW:			mMotoBit.setMotorSpeed(B, F, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: W");		break;
		case direction::kS:			mMotoBit.setMotorSpeed(B, B, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: S");		break;
		case direction::kNE:		mMotoBit.setMotorSpeed(F, F, H, L);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NE");	break;
		case direction::kNW:		mMotoBit.setMotorSpeed(F, F, L, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NW");	break;
		case direction::kSE:		mMotoBit.setMotorSpeed(B, B, H, L);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SE");	break;
		case direction::kSW:		mMotoBit.setMotorSpeed(B, B, L, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SW");	break;
		case direction::kLF:		mMotoBit.setMotorSpeed(F, F, H, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LF");	break;
		case direction::kLB:		mMotoBit.setMotorSpeed(B, B, H, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LB");	break;
		case direction::kRF:		mMotoBit.setMotorSpeed(F, F, 0, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RF");	break;
		case direction::kRB:		mMotoBit.setMotorSpeed(B, B, 0, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RB");	break;
		case direction::kStop:		mMotoBit.setMotorSpeed(F, F, 0, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: Stop");	break;
	}
	return true;
}

}	// microbit_dal_app_kit

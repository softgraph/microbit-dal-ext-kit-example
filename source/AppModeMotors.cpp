/// App Mode for Motors
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeMotors.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeMotors
*/

struct ButtonsState {
	Buttons		latest	= button::kNone;
	Buttons		last	= button::kNone;
};

struct DirectionState {
	Direction	latest	= direction::kCenter;
	Direction	last	= direction::kCenter;
};

struct SonarDurationState {
	int			latest	= 0;
	int			last	= 0;
};

static const Features kAppMode = appMode::kMotors;

static ButtonsState			localButtons;
static ButtonsState			remoteButtons;
static DirectionState		remoteDirection;
static SonarDurationState	sonarDurationInMs;

/* Component */ bool AppModeMotors::isConfigured()
{
	return feature::configured() == kAppMode;
}

AppModeMotors::AppModeMotors()
	: AppModeBase("AppModeMotors")
	, mSonar(ExtKit::global().p1(), ExtKit::global().p0(), MICROBIT_ID_IO_P0, *this)
{
}

/* Component */ void AppModeMotors::start()
{
	AppModeBase::start();
	mMotoBit.start();
	mSonar.start();
	mRadio.start();
}

/* Component */ void AppModeMotors::stop()
{
	mRadio.stop();
	mSonar.stop();
	mMotoBit.stop();
	AppModeBase::stop();
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
		if(value == messageBusEvent::kRemoteTiltedLeft) {
			display::flashChar('<');
		}
		else if(value == messageBusEvent::kRemoteTiltedRight) {
			display::flashChar('>');
		}
	}
}

/* AppModeBase */ void AppModeMotors::doHandleRadioDatagramReceived(const ManagedString& /* received */)
{
	Buttons buttons = checkLatestRemoteButtons();
	if(buttons != button::kInvalid) {
		remoteButtons.latest = buttons;
	}

	Direction direction = checkLatestRemoteDirection();
	if(direction != direction::kInvalid) {
		remoteDirection.latest = direction;
	}
}

/* Sonar::HandlerProtocol */ void AppModeMotors::handleSonarEcho(uint64_t durationInMs)
{
	sonarDurationInMs.latest = (int) durationInMs;
	debug_sendLine(EXT_KIT_DEBUG_EVENT "Sonar Echo");
}

/* AppModeBase */ void AppModeMotors::doHandlePeriodic100ms(uint32_t /* count */)
{
	if(Sonar::isConfigured()) {
		SonarDurationState& s = sonarDurationInMs;
		if(s.last != s.latest) {
#if 0		/// @todo	to be implemented
			if(s.latest < 10) {
				...
			}
#endif
			display::showNumber(s.latest);
			s.last = s.latest;
			debug_sendLine(EXT_KIT_DEBUG_ACTION "Sonar Duration: 0x", string::hex(s.latest).toCharArray());
		}
		mSonar.trigger();
	}

	//	update remote direction
	{
		DirectionState& d = remoteDirection;
		if(d.last != d.latest) {
			controlMotoBitUsingDirection(d.latest);
			display::showDirection(d.latest);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Direction: 0x", string::hex(d.latest).toCharArray());
			d.last = d.latest;
		}
	}

	//	update remote buttons
	{
		ButtonsState& b = remoteButtons;
		if(b.last != b.latest) {
			display::showButton(b.latest);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Remote Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}

	//	update local buttons
	{
		ButtonsState& b = localButtons;
		b.latest = button::readMicroBitButtons();
		if(b.last != b.latest) {
			Direction direction = direction::kCenter;
			if((b.latest & button::kLR) == button::kLR) {
				direction = direction::kN;
			}
			else if(b.latest & button::kL) {
				direction = direction::kLF;
			}
			else if(b.latest & button::kR) {
				direction = direction::kRF;
			}
			controlMotoBitUsingDirection(direction);
			display::showDirection(direction);
			//	debug_sendLine(EXT_KIT_DEBUG_ACTION "Loclal Buttons: 0x", string::hex(b.latest).toCharArray());
			b.last = b.latest;
		}
	}
}

bool AppModeMotors::controlMotoBitUsingDirection(Direction direction)
{
	if(!MotoBit::isConfigured()) {
		return false;
	}

	#define F MotoBit::kForward
	#define B MotoBit::kBackward
	const int H = 50;	// 50; // speedInPercent - high
	const int L = 25;	// 25; // speedInPercent - low
	switch(direction) {
		case direction::kCenter:	mMotoBit.setMotorSpeed(F, F, 0, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: -");	break;
		case direction::kN:			mMotoBit.setMotorSpeed(F, F, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: N");	break;
		case direction::kE:			mMotoBit.setMotorSpeed(F, B, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: E");	break;
		case direction::kW:			mMotoBit.setMotorSpeed(B, F, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: W");	break;
		case direction::kS:			mMotoBit.setMotorSpeed(B, B, H, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: S");	break;
		case direction::kNE:		mMotoBit.setMotorSpeed(F, F, H, L);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NE");	break;
		case direction::kNW:		mMotoBit.setMotorSpeed(F, F, L, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: NW");	break;
		case direction::kSE:		mMotoBit.setMotorSpeed(B, B, H, L);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SE");	break;
		case direction::kSW:		mMotoBit.setMotorSpeed(B, B, L, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: SW");	break;
		case direction::kLF:		mMotoBit.setMotorSpeed(F, F, H, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LF");	break;
		case direction::kLB:		mMotoBit.setMotorSpeed(B, B, H, 0);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: LB");	break;
		case direction::kRF:		mMotoBit.setMotorSpeed(F, F, 0, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RF");	break;
		case direction::kRB:		mMotoBit.setMotorSpeed(B, B, 0, H);		debug_sendLine(EXT_KIT_DEBUG_ACTION "Move: RB");	break;
	}
	return true;
}

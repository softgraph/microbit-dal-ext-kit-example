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
#include "ExtKitRadio.h"
#include "ExtKitSonar.h"

#include "AppModeBase.h"

/// App Mode for Motors
class AppModeMotors : public AppModeBase, protected microbit_dal_ext_kit::Sonar::HandlerProtocol
{
public:
	/// Inherited.
	static /* Component */ bool isConfigured();

	/// Constructor.
	AppModeMotors();

	/// Inherited.
	/* Component */ void start();

	/// Inherited.
	/* Component */ void stop();

protected:
	/// Inherited.
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited.
	/* AppModeBase */ void doHandleRadioDatagramReceived(const ManagedString& received);

	/// Inherited.
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

	/// Inherited.
	/* Sonar::HandlerProtocol */ void handleSonarEcho(uint64_t durationInMs);

private:
	bool controlMotoBitUsingDirection(microbit_dal_ext_kit::Direction direction);

	microbit_dal_ext_kit::MotoBit	mMotoBit;
	microbit_dal_ext_kit::Radio		mRadio;
	microbit_dal_ext_kit::Sonar		mSonar;

};	// AppModeMotors

#endif	// APP_MODE_MOTORS_H

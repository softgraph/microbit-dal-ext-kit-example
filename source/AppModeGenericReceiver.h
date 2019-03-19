/// App Mode for Generic Receiver
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_GENERIC_RECEIVER_H
#define APP_MODE_GENERIC_RECEIVER_H

#include "ExtKitRadio.h"

#include "AppModeBase.h"

/// App Mode for Generic Receiver
class AppModeGenericReceiver : public AppModeBase
{
public:
	/// Inherited.
	static /* Component */ bool isConfigured();

	/// Constructor.
	AppModeGenericReceiver();

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

private:
	microbit_dal_ext_kit::Radio		mRadio;

};	// AppModeGenericReceiver

#endif	// APP_MODE_GENERIC_RECEIVER_H

/// App Mode Base component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_BASE_H
#define APP_MODE_BASE_H

#include "ExtKitComponent.h"
#include "ExtKitPeriodicListener.h"

class ManagedString;
class MicroBitEvent;

/// App Mode Base Component
/* abstract */ class AppModeBase : public microbit_dal_ext_kit::Component, microbit_dal_ext_kit::PeriodicListener::HandlerProtocol
{
public:
	/// Constructor.
	AppModeBase(const char* name);

	/// Inherited.
	/* Component */ void start();

	/// Inherited.
	/* Component */ void stop();

protected:
	virtual /* to be overridden */ void doHandleEvent(const MicroBitEvent& event);
	virtual /* to be overridden */ void doHandleRadioDatagramReceived(const ManagedString& received);
	virtual /* to be overridden */ void doHandlePeriodic100ms(uint32_t count);

	void listen(int id, int value);

private:
	void handleEvent(MicroBitEvent event);
	void handleRadioDatagramReceived(MicroBitEvent event);
	/* PeriodicListener::HandlerProtocol */ void handlePeriodicEvent(uint32_t count, microbit_dal_ext_kit::PeriodicListener::PeriodUnit unit);

};	// AppModeBase

#endif	// APP_MODE_BASE_H

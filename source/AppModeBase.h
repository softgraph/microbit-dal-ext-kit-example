/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode Base component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_BASE_H
#define APP_MODE_BASE_H

#include "ExtKitComponent.h"
#include "ExtKitPeriodicObserver.h"

class ManagedString;
class MicroBitEvent;

namespace microbit_dal_app_kit {

/// App Mode Base Composite Component
/* abstract */ class AppModeBase : public microbit_dal_ext_kit::CompositeComponent, microbit_dal_ext_kit::PeriodicObserver::Handler::Protocol
{
protected:
	/// Constructor
	AppModeBase(const char* name);

	/// Event Definition
	struct EventDef {
	public:
		uint16_t	id;
		uint16_t	value;
	};

	/// Select Events
	void selectEvents(const EventDef* def);

	/// Select Radio Events
	void selectRadioEvents(const EventDef* def);

	/// Inherited
	/* CompositeComponent */ void doStart();

	/// Inherited
	/* CompositeComponent */ void doStop();

	void listen(int id, int value);

	void ignore(int id, int value);

	/// Do Handle Event
	virtual /* to be overridden */ void doHandleEvent(const MicroBitEvent& /* event */)	{ /* nothing to do */ }

	/// Do Handle Periodic 100 ms
	virtual /* to be overridden */ void doHandlePeriodic100ms(uint32_t /* count */)	{ /* nothing to do */ }

private:
	void handleEvent(MicroBitEvent event);

	/* PeriodicObserver::Handler::Protocol */ void handlePeriodicEvent(uint32_t count, microbit_dal_ext_kit::PeriodicObserver::PeriodUnit unit);

	const EventDef*	mEvents;

	const EventDef*	mRadioEvents;

};	// AppModeBase

}	// microbit_dal_app_kit

#endif	// APP_MODE_BASE_H

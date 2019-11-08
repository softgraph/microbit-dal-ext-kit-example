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
/* abstract */ class AppModeBase : public microbit_dal_ext_kit::CompositeComponent, microbit_dal_ext_kit::PeriodicObserver::HandlerProtocol
{
protected:
	/// Constructor
	AppModeBase(const char* name);

	/// Event Definition
	struct EventDef {
	public:
		/// Event ID
		uint16_t	id;

		/// Event Value
		uint16_t	value;
	};

	/// Period Definition
	struct PeriodDef {
	public:
		/// Unit
		microbit_dal_ext_kit::PeriodicObserver::PeriodUnit	unit;

		/// Priority
		microbit_dal_ext_kit::PeriodicObserver::HandlerPriority	priority;
	};

	/// Select Events to be received
	void selectEvents(const EventDef* def);

	/// Select Radio Events to be forwarded
	void selectRadioEvents(const EventDef* def);

	/// Select Periodic Observers to be notified
	void selectPeriodicObservers(const PeriodDef* def);

	/// Inherited
	/* CompositeComponent */ void doHandleComponentAction(Action action);

	/// Do Handle Event
	virtual /* AppModeBase */ void doHandleEvent(const MicroBitEvent& /* event */)	{ /* nothing to do */ }

	/// Do Handle Periodic 100 ms
	/** This handler is enabled by default. */
	virtual /* AppModeBase */ void doHandlePeriodic100ms(uint32_t /* count */)	{ /* nothing to do */ }

	/// Do Handle Periodic 20 ms
	/** This handler is disabled by default. You need to call selectPeriodicObservers() to enable it. */
	virtual /* AppModeBase */ void doHandlePeriodic20ms(uint32_t /* count */)	{ /* nothing to do */ }

private:
	void listen(int id, int value);

	void ignore(int id, int value);

	void handleEvent(MicroBitEvent event);

	/* PeriodicObserver::HandlerProtocol */ void handlePeriodicEvent(uint32_t count, microbit_dal_ext_kit::PeriodicObserver::PeriodUnit unit);

	const EventDef*	mEvents;

	const EventDef*	mRadioEvents;

	const PeriodDef* mPeriodicObservers;

};	// AppModeBase

}	// microbit_dal_app_kit

#endif	// APP_MODE_BASE_H

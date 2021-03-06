/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode Base Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeBase.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeBase
*/

AppModeBase::AppModeBase(const char* name)
	: CompositeComponent(name)
	, mEvents(0)
	, mRadioEvents(0)
	, mPeriodicObservers(0)
{
	static const PeriodDef defaulPeriodicObservers[] = {
		{ PeriodicObserver::kUnit100ms, PeriodicObserver::kPriorityMedium },
		{ PeriodicObserver::kUnitNever, PeriodicObserver::kPriorityVeryLow }	// END OF TABLE
	};
	mPeriodicObservers = defaulPeriodicObservers;
}

void AppModeBase::selectEvents(const EventDef* def)
{
	mEvents = def;
}

void AppModeBase::selectRadioEvents(const EventDef* def)
{
	mRadioEvents = def;
}

void AppModeBase::selectPeriodicObservers(const PeriodDef* def)
{
	mPeriodicObservers = def;
}

/* CompositeComponent */ void AppModeBase::doHandleComponentAction(Action action)
{
	if(action == kStart) {
		// Listen to Selected Events
		if(mEvents) {
			const EventDef* p = mEvents;
			while((p->id) || (p->value)) {
				listen(p->id, p->value);
				p++;
			}
		}

		// Listen to Selected Radio Events to be forwarded to the receiver
		if(mRadioEvents) {
			MicroBitRadio* r = ExtKit::global().radio();
			if(r) {
				const EventDef* p = mRadioEvents;
				while((p->id) || (p->value)) {
					r->event.listen(p->id, p->value);
					p++;
				}
			}
		}

		// Listen Periodic Observers
		if(mPeriodicObservers) {
			const PeriodDef* p = mPeriodicObservers;
			while(p->unit != PeriodicObserver::kUnitNever) {
				PeriodicObserver::listen(p->unit, *this, p->priority);
				p++;
			}
		}
	}
	else if(action == kStop) {
		// Ignore Periodic Observers
		if(mPeriodicObservers) {
			const PeriodDef* p = mPeriodicObservers;
			while(p->unit != PeriodicObserver::kUnitNever) {
				PeriodicObserver::ignore(p->unit, *this);
				p++;
			}
		}

		// Ignore Radio Events
		if(mRadioEvents) {
			MicroBitRadio* r = ExtKit::global().radio();
			if(r) {
				const EventDef* p = mRadioEvents;
				while((p->id) || (p->value)) {
					r->event.ignore(p->id, p->value);
					p++;
				}
			}
		}

		// Ignore Events
		if(mEvents) {
			const EventDef* p = mEvents;
			while((p->id) || (p->value)) {
				ignore(p->id, p->value);
				p++;
			}
		}
	}

	CompositeComponent::doHandleComponentAction(action);
}

void AppModeBase::listen(int id, int value)
{
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.listen(id, value,  this, &AppModeBase::handleEvent);
	if(id == messageBusID::kLocalEvent) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() messageBusID::kLocalEvent");
	}
	else if(id == messageBusID::kRemoteEvent) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() messageBusID::kRemoteEvent");
	}
	else if(id == MICROBIT_ID_GESTURE) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() MICROBIT_ID_GESTURE");
	}
	else {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() Unknown");
	}
}

void AppModeBase::ignore(int id, int value)
{
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	mb.ignore(id, value,  this, &AppModeBase::handleEvent);
	if(id == messageBusID::kLocalEvent) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::ignore() messageBusID::kLocalEvent");
	}
	else if(id == messageBusID::kRemoteEvent) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::ignore() messageBusID::kRemoteEvent");
	}
	else if(id == MICROBIT_ID_GESTURE) {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::ignore() MICROBIT_ID_GESTURE");
	}
	else {
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::ignore() Unknown");
	}
}

void AppModeBase::handleEvent(MicroBitEvent event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Local Event: App Started");
		}
		else {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Local Event: Unknown");
		}
	}
	else if(source == messageBusID::kRemoteEvent) {
		if(value == messageBusEvent::kRemoteTiltBase + direction::kN) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilt to N");
		}
		else if(value == messageBusEvent::kRemoteTiltBase + direction::kE) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilt to E");
		}
		else if(value == messageBusEvent::kRemoteTiltBase + direction::kW) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilt to W");
		}
		else if(value == messageBusEvent::kRemoteTiltBase + direction::kS) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilt to S");
		}
		else {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Unknown");
		}
	}
	else if(source == MICROBIT_ID_GESTURE) {
		if(value == gesture::microBitGestureEventTilt(direction::kN)) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilt to N");
		}
		else if(value == gesture::microBitGestureEventTilt(direction::kE)) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilt to E");
		}
		else if(value == gesture::microBitGestureEventTilt(direction::kW)) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilt to W");
		}
		else if(value == gesture::microBitGestureEventTilt(direction::kS)) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilt to S");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FACE_UP) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Face Up");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FACE_DOWN) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Face Down");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FREEFALL) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Freefall");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_3G) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: 3G");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_6G) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: 6G");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_8G) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: 8G");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_SHAKE) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Shaken");
		}
		else {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Unknown");
		}
	}
	else {
		debug_sendLine(EXT_KIT_DEBUG_EVENT "Other Event: Unknown");
	}

	/* virtual */ doHandleEvent(event);
}

/* PeriodicObserver::HandlerProtocol */ void AppModeBase::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit unit)
{
	switch(unit) {
		case PeriodicObserver::kUnit20ms: {
			/* virtual */ doHandlePeriodic20ms(count);
			break;
		}
		case PeriodicObserver::kUnit100ms: {
			/* virtual */ doHandlePeriodic100ms(count);

			if((count & 0x7f) == 0) {
				// approx. every 12.8 seconds
				Statistics::debug_sendItems();
			}
			break;
		}
		case PeriodicObserver::kUnitNever: {
			break;
		}
	}
}

}	// microbit_dal_app_kit

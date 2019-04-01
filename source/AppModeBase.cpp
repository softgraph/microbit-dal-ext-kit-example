/// App Mode Base Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeBase.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/**	@class	AppModeBase
*/

AppModeBase::AppModeBase(const char* name)
	: CompositeComponent(name)
	, mEvents(0)
	, mRadioEvents(0)
{
}

void AppModeBase::selectEvents(const EventDef* def)
{
	mEvents = def;
}

void AppModeBase::selectRadioEvents(const EventDef* def)
{
	mRadioEvents = def;
}

/* CompositeComponent */ void AppModeBase::doStart()
{
	// Start Base classes
	CompositeComponent::doStart();

	// Start Children
	startChildren();

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

	// Listen Periodic Observer
	PeriodicObserver::Handler::listen(PeriodicObserver::kUnit100ms, *this);
}

/* CompositeComponent */ void AppModeBase::doStop()
{
	// Ignore Periodic Observer
	PeriodicObserver::Handler::ignore(PeriodicObserver::kUnit100ms, *this);

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

	// Stop Children
	stopChildren();

	// Stop Base classes
	CompositeComponent::doStop();
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
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() Others");
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
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::ignore() Others");
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
		if(value == messageBusEvent::kRemoteTiltedLeft) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilted Left");
		}
		else if(value == messageBusEvent::kRemoteTiltedRight) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Tilted Right");
		}
		else {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Event: Unknown");
		}
	}
	else if(source == MICROBIT_ID_GESTURE) {
		if(value == MICROBIT_ACCELEROMETER_EVT_TILT_UP) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilted Up");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_TILT_DOWN) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilted Down");
		}
		else if(value == gesture::microBitGestureEventTiltLeft()) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilted Left");
		}
		else if(value == gesture::microBitGestureEventTiltRight()) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Tilted Right");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FACE_UP) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Faced Up");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FACE_DOWN) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Faced Down");
		}
		else if(value == MICROBIT_ACCELEROMETER_EVT_FREEFALL) {
			debug_sendLine(EXT_KIT_DEBUG_EVENT "Gesture: Fallen Free");
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

/* PeriodicObserver::HandlerProtocol */ void AppModeBase::handlePeriodicEvent(uint32_t count, PeriodicObserver::PeriodUnit /* unit */)
{
	/* virtual */ doHandlePeriodic100ms(count);

	if((count & 0x7f) == 0) {
		// approx. every 12.8 seconds
		Statistics::debug_sendItems();
	}
}

/// App Mode Base Component
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeBase.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*	@class	AppModeBase
*/

AppModeBase::AppModeBase(const char* name)
	: Component(name)
{
}

/* Component */ void AppModeBase::start()
{
	// start listening to message bus events
	{
		listen(messageBusID::kLocalEvent, messageBusEvent::kLocalAppStarted);
	}
	if(feature::isConfigured(feature::kRemoteEventTx)) {
		// observe a remote event to be forwarded to the receiver
		MicroBitRadio* r = ExtKit::global().radio();
		if(r) {
			r->event.listen(messageBusID::kRemoteEvent, MICROBIT_EVT_ANY);
		}
	}
	if(feature::isConfigured(feature::kRemoteEventRx)) {
		// receive a remote event sent from the transmitter
		listen(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedLeft);
		listen(messageBusID::kRemoteEvent, messageBusEvent::kRemoteTiltedRight);
	}
	if(feature::isConfigured(feature::kRemoteStateTx) || feature::isConfigured(feature::kRemoteStateRx)) {
		// receive a radio received event from the receiver or transmitter
		listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM);
	}

	// register periodic handler
	PeriodicListener::registerHandler(PeriodicListener::kUnit100ms, this);
}

/* Component */ void AppModeBase::stop()
{
	// nothing to do
}

/* to be overridden */ void AppModeBase::doHandleEvent(const MicroBitEvent& /* event */)
{
	// nothing to do
}

/* to be overridden */ void AppModeBase::doHandleRadioDatagramReceived(const ManagedString& /* received */)
{
	// nothing to do
}

/* to be overridden */ void AppModeBase::doHandlePeriodic100ms(uint32_t /* count */)
{
	// nothing to do
}

void AppModeBase::listen(int id, int value)
{
	MicroBitMessageBus& mb = ExtKit::global().messageBus();
	if(id == messageBusID::kLocalEvent) {
		debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() handleLocalEvent");
		mb.listen(id, value,  this, &AppModeBase::handleEvent);
	}
	else if(id == messageBusID::kRemoteEvent) {
		debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() handleRemoteEvent");
		mb.listen(id, value,  this, &AppModeBase::handleEvent);
	}
	else if(id == MICROBIT_ID_GESTURE) {
		debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() handleGestureEvent");
		mb.listen(id, value,  this, &AppModeBase::handleEvent);
	}
	else if(id == MICROBIT_ID_RADIO && value == MICROBIT_RADIO_EVT_DATAGRAM) {
		debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() handleRadioDatagramReceived");
		mb.listen(id, value,  this, &AppModeBase::handleRadioDatagramReceived);
	}
	else {
		debug_sendLine(EXT_KIT_DEBUG_TRACE "AppModeBase::listen() handleOtherEvent");
		mb.listen(id, value,  this, &AppModeBase::handleEvent);
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

void AppModeBase::handleRadioDatagramReceived(MicroBitEvent /* event */)
{
	ManagedString received = recvFromRadio();
	if(received.length() <= 0) {
		return;
	}
	if(feature::isConfigured(feature::kRemoteStateTx)) {
		// receive a request sent from the receiver
		receiveRemoteRequestFromRadio(received);
	}
	else if(feature::isConfigured(feature::kRemoteStateRx)) {
		// receive a notification or response sent from the transmitter
		receiveRemoteStatesFromRadio(received);
	}

	/* virtual */ doHandleRadioDatagramReceived(received);
}

/* PeriodicListener::HandlerProtocol */ void AppModeBase::handlePeriodicEvent(uint32_t count, PeriodicListener::PeriodUnit /* unit */)
{
	/* virtual */ doHandlePeriodic100ms(count);

	if((count & 0x7f) == 0) {
		// approx. every 12.8 seconds
		Statistics::debug_sendItems();
	}
}

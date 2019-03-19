/// AppKit Radio
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKitRadio.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*
	Remote State
*/

//	Remote State Category
static const char remoteStateCategoryButtons	= 'b';
static const char remoteStateCategoryPianoKeys	= 'p';

EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, remoteStateButtons,		"\x01", "b")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, remoteStatePianoKeys,	"\x01", "p")

/*
	Remote State Tx (Transmitter)
*/

//	Remote State Marker
static const char remoteStateMarkerSequence		= '@';
static const char remoteStateMarkerButtons		= '+';
static const char remoteStateMarkerDirection	= '-';
static const char remoteStateMarkerPianoKeys	= '*';
static const char remoteStateMarkerOctave		= '/';
static const char remoteStateMarkerResponse		= '!';

EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, remoteStateResponse,	"\x01", "!")

/*
	Remote State Rx (Receiver)
*/

//	Remote State Marker
static const char remoteStateMarkerRequest		= '?';

EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, remoteStateRequest,		"\x01", "?")

static void handlePeriodic100mForRemoteStateRx(uint32_t count, PeriodicListener::PeriodUnit unit);

/*
	Radio
*/

bool prepareCoreRadio()
{
	if(!feature::isConfigured(feature::kRadio)) {
		return false;
	}

	if(feature::isConfigured(feature::kRemoteStateRx)) {
		PeriodicListener::registerHandler(PeriodicListener::kUnit100ms,
										  handlePeriodic100mForRemoteStateRx,
										  PeriodicListener::kHandlerPriorityLow);
		debug_sendLine(EXT_KIT_DEBUG_TRACE "prepareRadio registerHandler");
	}
	return true;
}

/*
	Remote State Tx (Transmitter)
*/

struct RemoteButtonsSent {
	bool		enabled		= false;
	uint8_t		sequence	= 0;
	Buttons		buttons		= button::kNone;
	Direction	direction	= direction::kCenter;
};

static RemoteButtonsSent remoteButtonsSent;

struct RemotePianoKeysSent {
	bool		enabled		= false;
	uint8_t		sequence	= 0;
	PianoKeys	pianoKeys	= pianoKey::kNone;
	Octave		octave		= octave::kCenter;
};

static RemotePianoKeysSent remotePianoKeysSent;

void updateRemoteButtonsToRadio(Buttons buttons, Direction direction)
{
	RemoteButtonsSent& r = remoteButtonsSent;
	r.enabled = true;
	r.sequence++;
	r.buttons = buttons;
	r.direction = direction;
	sendRemoteButtonsToRadio();
}

void updateRemotePianoKeysToRadio(PianoKeys pianoKeys, Octave octave)
{
	RemotePianoKeysSent& r = remotePianoKeysSent;
	r.enabled = true;
	r.sequence++;
	r.pianoKeys = pianoKeys;
	r.octave = octave;
	sendRemotePianoKeysToRadio();
}

void sendRemoteButtonsToRadio(bool asResponse)
{
	const RemoteButtonsSent& r = remoteButtonsSent;
	ManagedString s = remoteStateButtons;
	s = s + string::hex(r.sequence,	remoteStateMarkerSequence);
	s = s + string::hex(r.buttons,	remoteStateMarkerButtons);
	s = s + string::hex(r.direction,	remoteStateMarkerDirection);
	if(asResponse) {
		s = s + remoteStateResponse;
	}
	sendToRadio(s);
}

void sendRemotePianoKeysToRadio(bool asResponse)
{
	const RemotePianoKeysSent& r = remotePianoKeysSent;
	ManagedString s = remoteStatePianoKeys;
	s =	s + string::hex(r.sequence,	remoteStateMarkerSequence);
	s = s + string::hex(r.pianoKeys,	remoteStateMarkerPianoKeys);
	s = s + string::hex(r.octave,	remoteStateMarkerOctave);
	if(asResponse) {
		s = s + remoteStateResponse;
	}
	sendToRadio(s);
}

void receiveRemoteRequestFromRadio(ManagedString& received)
{
	// check the marker for request
	int16_t pos = string::seek(received, 0, remoteStateMarkerRequest);
	if(pos <= 0) {
		return;
	}

	// check the category
	char c = received.charAt(0);
	switch (c) {
		case remoteStateCategoryButtons: {
			if(remoteButtonsSent.enabled) {
				sendRemoteButtonsToRadio(true);
			}
			return;
		}
		case remoteStateCategoryPianoKeys: {
			if(remotePianoKeysSent.enabled) {
				sendRemotePianoKeysToRadio(true);
			}
			return;
		}
	}
}

/*
	Remote State Rx (Receiver)
*/

//																					 123456789abcdef0123456789
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioUpdateButtons,			"\x19", "Remote Buttons Update:   ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioResponseButtons,		"\x19", "Remote Buttons Response: ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioRecoveryButtons,		"\x19", "Remote Buttons Recovery: ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioSyncDurationButtons,	"\x19", "Remote Buttons Duration: ")

//																					 123456789abcdef0123456789ab
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioUpdatePianoKeys,		"\x1b", "Remote PianoKeys Update:   ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioResponsePianoKeys,		"\x1b", "Remote PianoKeys Response: ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioRecoveryPianoKeys,		"\x1b", "Remote PianoKeys Recovery: ")
EXT_KIT_DEFINE_LITERAL_MANAGED_STRING(static const, radioSyncDurationPianoKeys,	"\x1b", "Remote PianoKeys Duration: ")

static const uint16_t kSyncDurationInitial	= 400;

struct RemoteButtonsReceived {
	uint16_t				syncDuration	= 0;
	time::LongSystemTime	syncNextTime	= 0;
	uint8_t					sequence		= 0;
	Buttons					buttons			= button::kNone;
	Direction				direction		= direction::kCenter;
};

static RemoteButtonsReceived remoteButtonsReceived;

struct RemotePianoKeysReceived {
	uint16_t				syncDuration	= 0;
	time::LongSystemTime	syncNextTime	= 0;
	uint8_t					sequence		= 0;
	PianoKeys				pianoKeys		= pianoKey::kNone;
	Octave					octave			= octave::kCenter;
};

static RemotePianoKeysReceived remotePianoKeysReceived;

void handlePeriodic100mForRemoteStateRx(uint32_t /* count */, PeriodicListener::PeriodUnit /* unit */)
{
	{
		RemoteButtonsReceived& r = remoteButtonsReceived;
		uint16_t tmp = r.syncDuration;
		if(0 < tmp) {
			if(time::isElapsed(r.syncNextTime)) {
				requestRemoteButtonsToRadio();
				r.syncNextTime = time::longSystemTime() + tmp;
			}
		}
	}
	{
		RemotePianoKeysReceived& r = remotePianoKeysReceived;
		uint16_t tmp = r.syncDuration;
		if(0 < tmp) {
			if(time::isElapsed(r.syncNextTime)) {
				requestRemotePianoKeysToRadio();
				r.syncNextTime = time::longSystemTime() + tmp;
			}
		}
	}
}

void requestRemoteButtonsToRadio()
{
	ManagedString s = remoteStateButtons + remoteStateRequest;
	sendToRadio(s);
}

void requestRemotePianoKeysToRadio()
{
	ManagedString s = remoteStatePianoKeys + remoteStateRequest;
	sendToRadio(s);
}

void receiveRemoteStatesFromRadio(ManagedString& received)
{
	//	debug_sendLine(EXT_KIT_DEBUG_TRACE "receiveRemoteStatesFromRadio #1");

	// check the marker for Sequence
	int16_t pos = string::seek(received, 0, remoteStateMarkerSequence);
	if(pos <= 0) {
		return;
	}

	// check the marker for Response
	bool asResponse = 0 < string::seek(received, 0, remoteStateMarkerResponse);

	// check the category
	char c = received.charAt(0);
	switch (c) {
		case remoteStateCategoryButtons: {
			RemoteButtonsReceived& r = remoteButtonsReceived;
			uint8_t sequence = string::numberForHexString(received, pos);
			if(r.sequence == sequence) {
				uint16_t tmp = r.syncDuration;
				if(tmp < 0x8000) {
					r.syncDuration = tmp + tmp;
					Statistics::setItem(&radioSyncDurationButtons, r.syncDuration);
				}
				if(asResponse) {
					Statistics::incrementItem(&radioResponseButtons);
				}
				else {
					Statistics::incrementItem(&radioUpdateButtons);
				}
				return;
			}

			r.sequence = sequence;
			r.syncDuration = kSyncDurationInitial;
			Statistics::setItem(&radioSyncDurationButtons, r.syncDuration);
			if(asResponse) {
				Statistics::incrementItem(&radioResponseButtons);
				Statistics::incrementItem(&radioRecoveryButtons);
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Buttons are recovered");
			}
			else {
				Statistics::incrementItem(&radioUpdateButtons);
			}

			// check the marker for Buttons
			pos = string::seek(received, 0, remoteStateMarkerButtons);
			if(0 < pos) {
				r.buttons = string::numberForHexString(received, pos);
			}

			// check the marker for Direction
			pos = string::seek(received, 0, remoteStateMarkerDirection);
			if(0 < pos) {
				r.direction = string::numberForHexString(received, pos);
			}
			return;
		}
		case remoteStateCategoryPianoKeys: {
			RemotePianoKeysReceived& r = remotePianoKeysReceived;
			uint8_t sequence = string::numberForHexString(received, pos);
			if(r.sequence == sequence) {
				uint16_t tmp = r.syncDuration;
				if(tmp < 0x8000) {
					r.syncDuration = tmp + tmp;
					Statistics::setItem(&radioSyncDurationPianoKeys, r.syncDuration);
				}
				if(asResponse) {
					Statistics::incrementItem(&radioResponsePianoKeys);
				}
				else {
					Statistics::incrementItem(&radioUpdatePianoKeys);
				}
				return;
			}

			r.sequence = sequence;
			r.syncDuration = kSyncDurationInitial;
			Statistics::setItem(&radioSyncDurationPianoKeys, r.syncDuration);
			if(asResponse) {
				Statistics::incrementItem(&radioResponsePianoKeys);
				Statistics::incrementItem(&radioRecoveryPianoKeys);
				debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Piano Keys are recovered");
			}
			else {
				Statistics::incrementItem(&radioUpdatePianoKeys);
			}

			// check the marker for Piano Keys
			pos = string::seek(received, 0, remoteStateMarkerPianoKeys);
			if(0 < pos) {
				r.pianoKeys = string::numberForHexString(received, pos);
			}

			// check the marker for Octave
			pos = string::seek(received, 0, remoteStateMarkerOctave);
			if(0 < pos) {
				r.octave = string::numberForHexString(received, pos);
			}
			return;
		}
	}
}

Buttons checkLatestRemoteButtons()
{
	static Buttons last = button::kNone;
	Buttons latest = remoteButtonsReceived.buttons;
	if(last == latest) {
		return button::kInvalid;
	}

	last = latest;
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Buttons: 0x", string::hex(latest).toCharArray());
	return latest;
}

Direction checkLatestRemoteDirection()
{
	static Direction last = direction::kCenter;
	Direction latest = remoteButtonsReceived.direction;
	if(last == latest) {
		return direction::kInvalid;
	}

	last = latest;
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Direction: 0x", string::hex(latest).toCharArray());
	return latest;
}

PianoKeys checkLatestRemotePianoKeys()
{
	static PianoKeys last = pianoKey::kNone;
	PianoKeys latest = remotePianoKeysReceived.pianoKeys;
	if(last == latest) {
		return pianoKey::kInvalid;
	}

	last = latest;
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote PianoKeys: 0x", string::hex(latest).toCharArray());
	return latest;
}

Octave checkLatestRemoteOctave()
{
	static Octave last = octave::kCenter;
	Octave latest = remotePianoKeysReceived.octave;
	if(last == latest) {
		return octave::kInvalid;
	}

	last = latest;
	//	debug_sendLine(EXT_KIT_DEBUG_EVENT "Remote Octave: 0x", string::hex(latest).toCharArray());
	return latest;
}

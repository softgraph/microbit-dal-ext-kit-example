/// AppKit Remote State
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKitRemoteState.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

/*
	for both `RemoteStateTransmitterForButtons` and `RemoteStateReceiverForButtons`
*/

static const char kMarkerButtons	= '+';
static const char kMarkerDirection	= '-';

/*
	for both `RemoteStateTransmitterForPianoKeys` and `RemoteStateReceiverForPianoKeys`
*/

static const char kMarkerPianoKeys	= '+';
static const char kMarkerOctave		= '-';

/**	@class	RemoteStateTransmitter
*/

RemoteStateTransmitter::RemoteStateTransmitter(char category)
	: mTransmitter(remoteState::Transmitter::global())
	, mCategory(category)
{
	mTransmitter.listen(mCategory, *this);
}

/**	@class	RemoteStateTransmitterForButtons
*/

RemoteStateTransmitterForButtons::RemoteStateTransmitterForButtons()
	: RemoteStateTransmitter('b')
{
}

/* remoteState::Transmitter::Protocol */ ManagedString RemoteStateTransmitterForButtons::remoteState()
{
	ManagedString s =
		string::hex(buttons.value(), kMarkerButtons) +
		string::hex(direction.value(), kMarkerDirection);
	return s;
}

void RemoteStateTransmitterForButtons::updateRemoteState()
{
	Buttons b;
	Direction d;
	if(buttons.read(b) || direction.read(d)) {
		mTransmitter.requestToSend(mCategory);
	}
}

/**	@class	RemoteStateTransmitterForPianoKeys
*/

RemoteStateTransmitterForPianoKeys::RemoteStateTransmitterForPianoKeys()
	: RemoteStateTransmitter('p')
{
}

/* remoteState::Transmitter::Protocol */ ManagedString RemoteStateTransmitterForPianoKeys::remoteState()
{
	ManagedString s =
		string::hex(pianoKeys.value(), kMarkerPianoKeys) +
		string::hex(octave.value(), kMarkerOctave);
	return s;
}

void RemoteStateTransmitterForPianoKeys::updateRemoteState()
{
	PianoKeys p;
	Octave o;
	if(pianoKeys.read(p) || octave.read(o)) {
		mTransmitter.requestToSend(mCategory);
	}
}

/**	@class	RemoteStateReceiver
*/

RemoteStateReceiver::RemoteStateReceiver(char category)
	: mReceiver(remoteState::Receiver::global())
	, mCategory(category)
{
	mReceiver.listen(mCategory, *this);
}

/**	@class	RemoteStateReceiverForButtons
*/

RemoteStateReceiverForButtons::RemoteStateReceiverForButtons()
	: RemoteStateReceiver('b')
{
}

/* remoteState::Receiver::Protocol */ void RemoteStateReceiverForButtons::handleRemoteState(ManagedString& received)
{
	int16_t pos;
	pos = string::seek(received, 0, kMarkerButtons);
	if(0 < pos) {
		buttons.set(string::numberForHexString(received, pos));
	}

	pos = string::seek(received, 0, kMarkerDirection);
	if(0 < pos) {
		direction.set(string::numberForHexString(received, pos));
	}
}

/**	@class	RemoteStateReceiverForPianoKeys
*/

RemoteStateReceiverForPianoKeys::RemoteStateReceiverForPianoKeys()
	: RemoteStateReceiver('p')
{
}

/* remoteState::Receiver::Protocol */ void RemoteStateReceiverForPianoKeys::handleRemoteState(ManagedString& received)
{
	int16_t pos;
	pos = string::seek(received, 0, kMarkerPianoKeys);
	if(0 < pos) {
		pianoKeys.set(string::numberForHexString(received, pos));
	}

	pos = string::seek(received, 0, kMarkerOctave);
	if(0 < pos) {
		octave.set(string::numberForHexString(received, pos));
	}
}

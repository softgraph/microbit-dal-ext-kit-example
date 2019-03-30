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
	for both `RemoteStateTransmitterCategoryForButtons` and `RemoteStateReceiverCategoryForButtons`
*/

static const char kMarkerButtons	= '+';
static const char kMarkerDirection	= '-';

/*
	for both `RemoteStateTransmitterCategoryForPianoKeys` and `RemoteStateReceiverCategoryForPianoKeys`
*/

static const char kMarkerPianoKeys	= '+';
static const char kMarkerOctave		= '-';

/**	@class	RemoteStateTransmitterCategoryForButtons
*/

RemoteStateTransmitterCategoryForButtons::RemoteStateTransmitterCategoryForButtons()
	: remoteState::Transmitter::CategoryBase('b')
{
}

/* remoteState::Transmitter::CategoryProtocol */ ManagedString RemoteStateTransmitterCategoryForButtons::remoteState()
{
	ManagedString s =
		string::hex(buttons.value(), kMarkerButtons) +
		string::hex(direction.value(), kMarkerDirection);
	return s;
}

void RemoteStateTransmitterCategoryForButtons::updateRemoteState()
{
	Buttons b;
	Direction d;
	if(buttons.read(b) || direction.read(d)) {
		mTransmitter.requestToSend(mCategory);
	}
}

/**	@class	RemoteStateTransmitterCategoryForPianoKeys
*/

RemoteStateTransmitterCategoryForPianoKeys::RemoteStateTransmitterCategoryForPianoKeys()
	: remoteState::Transmitter::CategoryBase('p')
{
}

/* remoteState::Transmitter::CategoryProtocol */ ManagedString RemoteStateTransmitterCategoryForPianoKeys::remoteState()
{
	ManagedString s =
		string::hex(pianoKeys.value(), kMarkerPianoKeys) +
		string::hex(octave.value(), kMarkerOctave);
	return s;
}

void RemoteStateTransmitterCategoryForPianoKeys::updateRemoteState()
{
	PianoKeys p;
	Octave o;
	if(pianoKeys.read(p) || octave.read(o)) {
		mTransmitter.requestToSend(mCategory);
	}
}

/**	@class	RemoteStateReceiverCategoryForButtons
*/

RemoteStateReceiverCategoryForButtons::RemoteStateReceiverCategoryForButtons()
	: remoteState::Receiver::CategoryBase('b')
{
}

/* remoteState::Receiver::CategoryProtocol */ void RemoteStateReceiverCategoryForButtons::handleRemoteState(ManagedString& received)
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

/**	@class	RemoteStateReceiverCategoryForPianoKeys
*/

RemoteStateReceiverCategoryForPianoKeys::RemoteStateReceiverCategoryForPianoKeys()
	: remoteState::Receiver::CategoryBase('p')
{
}

/* remoteState::Receiver::CategoryProtocol */ void RemoteStateReceiverCategoryForPianoKeys::handleRemoteState(ManagedString& received)
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

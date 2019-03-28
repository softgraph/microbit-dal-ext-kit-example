/// AppKit Remote State
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_REMOTE_STATE_H
#define APP_KIT_REMOTE_STATE_H

#include "AppKitState.h"
#include "ExtKitRemoteState.h"

class ManagedString;

/// Remote State Transmitter
/* abstract */ class RemoteStateTransmitter : public microbit_dal_ext_kit::RemoteState::Transmitter::Protocol
{
protected:
	/// Constructor
	RemoteStateTransmitter(char category);

	/// Transmitter
	microbit_dal_ext_kit::RemoteState::Transmitter&	mTransmitter;

	/// Category
	char	mCategory;

};	// RemoteStateTransmitter

/// Remote State Transmitter For Buttons
class RemoteStateTransmitterForButtons : public RemoteStateTransmitter
{
public:
	/// Constructor
	RemoteStateTransmitterForButtons();

	/// Inherited
	/* RemoteState::Transmitter::Protocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For Buttons
	StateChangeForButtons	buttons;

	/// State Change For Direction
	StateChangeForDirection	direction;

};	// RemoteStateTransmitterForButtons

/// Remote State Transmitter For Piano Keys
class RemoteStateTransmitterForPianoKeys : public RemoteStateTransmitter
{
public:
	/// Constructor
	RemoteStateTransmitterForPianoKeys();

	/// Inherited
	/* RemoteState::Transmitter::Protocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For PianoKeys
	StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	StateChangeForOctave	octave;

};	// RemoteStateTransmitterForPianoKeys

/// Remote State Receiver
/* abstract */ class RemoteStateReceiver : public microbit_dal_ext_kit::RemoteState::Receiver::Protocol
{
protected:
	/// Constructor
	RemoteStateReceiver(char category);

	/// Receiver
	microbit_dal_ext_kit::RemoteState::Receiver&	mReceiver;

	/// Category
	char	mCategory;

};	// RemoteStateReceiver

/// Remote State Receiver For Buttons
class RemoteStateReceiverForButtons : public RemoteStateReceiver
{
public:
	/// Constructor
	RemoteStateReceiverForButtons();

	/// Inherited
	/* RemoteState::Receiver::Protocol */ void handleRemoteState(ManagedString& received);

	/// State Change For Buttons
	StateChangeForButtons	buttons;

	/// State Change For Direction
	StateChangeForDirection	direction;

};	// RemoteStateReceiverForButtons

/// Remote State Receiver For PianoKeys
class RemoteStateReceiverForPianoKeys : public RemoteStateReceiver
{
public:
	/// Constructor
	RemoteStateReceiverForPianoKeys();

	/// Inherited
	/* RemoteState::Receiver::Protocol */ void handleRemoteState(ManagedString& received);

	/// State Change For PianoKeys
	StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	StateChangeForOctave	octave;

};	// RemoteStateReceiverForPianoKeys

#endif	// APP_KIT_REMOTE_STATE_H

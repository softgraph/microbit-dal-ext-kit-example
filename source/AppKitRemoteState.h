/// AppKit Remote State
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_REMOTE_STATE_H
#define APP_KIT_REMOTE_STATE_H

#include "ExtKitRemoteState.h"
#include "ExtKitButton.h"
#include "ExtKitDirection.h"
#include "ExtKitOctave.h"
#include "ExtKitPianoKey.h"

class ManagedString;

/// Remote State Transmitter
/* abstract */ class RemoteStateTransmitter : public microbit_dal_ext_kit::remoteState::Transmitter::Protocol
{
protected:
	/// Constructor
	RemoteStateTransmitter(char category);

	/// Transmitter
	microbit_dal_ext_kit::remoteState::Transmitter&	mTransmitter;

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
	/* remoteState::Transmitter::Protocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For Buttons
	microbit_dal_ext_kit::StateChangeForButtons	buttons;

	/// State Change For Direction
	microbit_dal_ext_kit::StateChangeForDirection	direction;

};	// RemoteStateTransmitterForButtons

/// Remote State Transmitter For Piano Keys
class RemoteStateTransmitterForPianoKeys : public RemoteStateTransmitter
{
public:
	/// Constructor
	RemoteStateTransmitterForPianoKeys();

	/// Inherited
	/* remoteState::Transmitter::Protocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For PianoKeys
	microbit_dal_ext_kit::StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	microbit_dal_ext_kit::StateChangeForOctave	octave;

};	// RemoteStateTransmitterForPianoKeys

/// Remote State Receiver
/* abstract */ class RemoteStateReceiver : public microbit_dal_ext_kit::remoteState::Receiver::Protocol
{
protected:
	/// Constructor
	RemoteStateReceiver(char category);

	/// Receiver
	microbit_dal_ext_kit::remoteState::Receiver&	mReceiver;

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
	/* remoteState::Receiver::Protocol */ void handleRemoteState(ManagedString& received);

	/// State Change For Buttons
	microbit_dal_ext_kit::StateChangeForButtons	buttons;

	/// State Change For Direction
	microbit_dal_ext_kit::StateChangeForDirection	direction;

};	// RemoteStateReceiverForButtons

/// Remote State Receiver For PianoKeys
class RemoteStateReceiverForPianoKeys : public RemoteStateReceiver
{
public:
	/// Constructor
	RemoteStateReceiverForPianoKeys();

	/// Inherited
	/* remoteState::Receiver::Protocol */ void handleRemoteState(ManagedString& received);

	/// State Change For PianoKeys
	microbit_dal_ext_kit::StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	microbit_dal_ext_kit::StateChangeForOctave	octave;

};	// RemoteStateReceiverForPianoKeys

#endif	// APP_KIT_REMOTE_STATE_H

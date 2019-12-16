/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

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

namespace microbit_dal_app_kit {

/// Remote State Transmitter Category For Buttons and Direction
class RemoteStateTransmitterCategoryForButtons : public microbit_dal_ext_kit::remoteState::Transmitter::CategoryBase
{
public:
	/// Constructor
	RemoteStateTransmitterCategoryForButtons();

	/// Inherited
	/* remoteState::Transmitter::CategoryProtocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For Buttons
	microbit_dal_ext_kit::StateChangeForButtons	buttons;

	/// State Change For Direction
	microbit_dal_ext_kit::StateChangeForDirection	direction;

};	// RemoteStateTransmitterCategoryForButtons

/// Remote State Transmitter Category For PianoKeys and Octave
class RemoteStateTransmitterCategoryForPianoKeys : public microbit_dal_ext_kit::remoteState::Transmitter::CategoryBase
{
public:
	/// Constructor
	RemoteStateTransmitterCategoryForPianoKeys();

	/// Inherited
	/* remoteState::Transmitter::CategoryProtocol */ ManagedString remoteState();

	/// Update Remote State
	void updateRemoteState();

	/// State Change For PianoKeys
	microbit_dal_ext_kit::StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	microbit_dal_ext_kit::StateChangeForOctave	octave;

};	// RemoteStateTransmitterCategoryForPianoKeys

/// Remote State Receiver Category For Buttons and Direction
class RemoteStateReceiverCategoryForButtons : public microbit_dal_ext_kit::remoteState::Receiver::CategoryBase
{
public:
	/// Constructor
	RemoteStateReceiverCategoryForButtons();

	/// Inherited
	/* remoteState::Receiver::CategoryProtocol */ void handleRemoteState(ManagedString& received);

	/// State Change For Buttons
	microbit_dal_ext_kit::StateChangeForButtons	buttons;

	/// State Change For Direction
	microbit_dal_ext_kit::StateChangeForDirection	direction;

};	// RemoteStateReceiverCategoryForButtons

/// Remote State Receiver Category For PianoKeys and Octave
class RemoteStateReceiverCategoryForPianoKeys : public microbit_dal_ext_kit::remoteState::Receiver::CategoryBase
{
public:
	/// Constructor
	RemoteStateReceiverCategoryForPianoKeys();

	/// Inherited
	/* remoteState::Receiver::CategoryProtocol */ void handleRemoteState(ManagedString& received);

	/// State Change For PianoKeys
	microbit_dal_ext_kit::StateChangeForPianoKeys	pianoKeys;

	/// State Change For Octave
	microbit_dal_ext_kit::StateChangeForOctave	octave;

};	// RemoteStateReceiverCategoryForPianoKeys

}	// microbit_dal_app_kit

#endif	// APP_KIT_REMOTE_STATE_H

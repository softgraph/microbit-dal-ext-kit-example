/// AppKit Radio
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_RADIO_H
#define APP_KIT_RADIO_H

#include "ExtKitButton.h"
#include "ExtKitDirection.h"
#include "ExtKitOctave.h"
#include "ExtKitPianoKey.h"

class ManagedString;

/*
	Radio
*/

bool prepareCoreRadio();

/*
	Remote State Tx (Transmitter)
*/

void updateRemoteButtonsToRadio(microbit_dal_ext_kit::Buttons buttons, microbit_dal_ext_kit::Direction direction);
void updateRemotePianoKeysToRadio(microbit_dal_ext_kit::PianoKeys pianoKeys, microbit_dal_ext_kit::Octave octave);

void sendRemoteButtonsToRadio(bool asResponse = false);
void sendRemotePianoKeysToRadio(bool asResponse = false);

void receiveRemoteRequestFromRadio(ManagedString& received);

/*
	Remote State Rx (Receiver)
*/

void requestRemoteButtonsToRadio();
void requestRemotePianoKeysToRadio();

void receiveRemoteStatesFromRadio(ManagedString& received);

microbit_dal_ext_kit::Buttons checkLatestRemoteButtons();
microbit_dal_ext_kit::Direction checkLatestRemoteDirection();
microbit_dal_ext_kit::PianoKeys checkLatestRemotePianoKeys();
microbit_dal_ext_kit::Octave checkLatestRemoteOctave();

#endif	// APP_KIT_RADIO_H

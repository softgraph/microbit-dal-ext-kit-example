/// AppKit State
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_STATE_H
#define APP_KIT_STATE_H

#include "ExtKitButton.h"
#include "ExtKitDirection.h"
#include "ExtKitOctave.h"
#include "ExtKitPianoKey.h"
#include "ExtKitState.h"

/*
	Extern Template Instantiation for class `State<T>`
*/

extern template class microbit_dal_ext_kit::State<uint16_t>;
extern template class microbit_dal_ext_kit::State<uint32_t>;

/*
	Extern Template Instantiation for class `StateChange<T>`
*/

extern template class microbit_dal_ext_kit::StateChange<uint16_t>;
extern template class microbit_dal_ext_kit::StateChange<uint32_t>;

/// State For Buttons
class StateForButtons : public microbit_dal_ext_kit::State<microbit_dal_ext_kit::Buttons>
{
public:
	/// Constructor
	StateForButtons();

};	// StateForButtons

/// State Change For Buttons
class StateChangeForButtons : public microbit_dal_ext_kit::StateChange<microbit_dal_ext_kit::Buttons>
{
public:
	/// Constructor
	StateChangeForButtons();

};	// StateChangeForButtons

/// State For Direction
class StateForDirection : public microbit_dal_ext_kit::State<microbit_dal_ext_kit::Direction>
{
public:
	/// Constructor
	StateForDirection();

};	// StateForDirection

/// State Change For Direction
class StateChangeForDirection : public microbit_dal_ext_kit::StateChange<microbit_dal_ext_kit::Direction>
{
public:
	/// Constructor
	StateChangeForDirection();

};	// StateChangeForDirection

/// State For PianoKeys
class StateForPianoKeys : public microbit_dal_ext_kit::State<microbit_dal_ext_kit::PianoKeys>
{
public:
	/// Constructor
	StateForPianoKeys();

};	// StateForPianoKeys

/// State Change For PianoKeys
class StateChangeForPianoKeys : public microbit_dal_ext_kit::StateChange<microbit_dal_ext_kit::PianoKeys>
{
public:
	/// Constructor
	StateChangeForPianoKeys();

};	// StateChangeForPianoKeys

/// State For Octave
class StateForOctave : public microbit_dal_ext_kit::State<microbit_dal_ext_kit::Octave>
{
public:
	/// Constructor
	StateForOctave();

};	// StateForOctave

/// State Change For Octave
class StateChangeForOctave : public microbit_dal_ext_kit::StateChange<microbit_dal_ext_kit::Octave>
{
public:
	/// Constructor
	StateChangeForOctave();

};	// StateChangeForOctave

/// State Change For Sonar Duration
class StateChangeForSonarDuration : public microbit_dal_ext_kit::StateChange<uint32_t>
{
public:
	/// Constructor
	StateChangeForSonarDuration();

};	// StateForSonarDuration

#endif	// APP_KIT_STATE_H

/// AppKit State
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKitState.h"	// self
#include "AppKit.h"

#include "ExtKitState.cpp.h"	// Implementation for "ExtKitState.h"

using namespace microbit_dal_ext_kit;

/*
	Explicit Template Instantiation for class `State<T>`
*/

template class State<uint16_t>;
template class State<uint32_t>;

/*
	Explicit Template Instantiation for class `StateChange<T>`
*/

template class StateChange<uint16_t>;
template class StateChange<uint32_t>;

/**	@class	StateForButtons
*/

StateForButtons::StateForButtons()
	: State<Buttons>(button::kNone)
{
}

/**	@class	StateChangeForButtons
*/

StateChangeForButtons::StateChangeForButtons()
	: StateChange<Buttons>(button::kNone)
{
}

/**	@class	StateForDirection
*/

StateForDirection::StateForDirection()
	: State<Direction>(direction::kCenter)
{
}

/**	@class	StateChangeForDirection
*/

StateChangeForDirection::StateChangeForDirection()
	: StateChange<Direction>(direction::kCenter)
{
}

/**	@class	StateForPianoKeys
*/

StateForPianoKeys::StateForPianoKeys()
	: State<PianoKeys>(pianoKey::kNone)
{
}

/**	@class	StateChangeForPianoKeys
*/

StateChangeForPianoKeys::StateChangeForPianoKeys()
	: StateChange<PianoKeys>(pianoKey::kNone)
{
}

/**	@class	StateForOctave
*/

StateForOctave::StateForOctave()
	: State<Octave>(octave::kCenter)
{
}

/**	@class	StateChangeForOctave
*/

StateChangeForOctave::StateChangeForOctave()
	: StateChange<Octave>(octave::kCenter)
{
}

/**	@class	StateChangeForSonarDuration
*/

StateChangeForSonarDuration::StateChangeForSonarDuration()
	: StateChange<uint32_t>(0)
{
}

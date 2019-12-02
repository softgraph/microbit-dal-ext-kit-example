/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// AppKit Event
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_EVENT_H
#define APP_KIT_EVENT_H

namespace microbit_dal_app_kit {

/// Message Bus ID for App Event
namespace messageBusID {

/// Message Bus ID: Local Event
const int kLocalEvent	= 2900;

/// Message Bus ID: Remote Event
const int kRemoteEvent	= 2901;

}	// messageBusID

/// Message Bus Event for App Event
namespace messageBusEvent {

/// Local Event: App Started
const int kLocalAppStarted		= 1;

/// Remote Event: Tilt to the Left
const int kRemoteTiltLeft		= 1;

/// Remote Event: Tilt Down (= Tilt to the Top)
const int kRemoteTiltTop		= 2;

/// Remote Event: Tilt to the Right
const int kRemoteTiltRight		= 3;

/// Remote Event: Tilt Up (= Tilt to the Botttom)
const int kRemoteTiltBottom		= 4;

}	// messageBusEvent
}	// microbit_dal_app_kit

#endif	// APP_KIT_EVENT_H

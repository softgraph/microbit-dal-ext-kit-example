/// AppKit Event
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_EVENT_H
#define APP_KIT_EVENT_H

/// Message Bus ID for App Event
namespace messageBusID {

/// Local Event
const int kLocalEvent	= 2900;

/// Remote Event
const int kRemoteEvent	= 2901;

}	// messageBusID

/// Message Bus Event for App Event
namespace messageBusEvent {

/// App Started - Local Event (messageBusID::kLocalEvent)
const int kLocalAppStarted	= 1;

/// Tilted Left - Remote Event (messageBusID::kRemoteEvent)
const int kRemoteTiltedLeft	= 1;

/// Tilted Right - Remote Event (messageBusID::kRemoteEvent)
const int kRemoteTiltedRight	= 2;

}	// messageBusID

#endif	// APP_KIT_EVENT_H

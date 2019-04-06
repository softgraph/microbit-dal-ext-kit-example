/// An example for using microbit-dal-ext-kit
/**	@package	microbit_dal_app_kit
*/

/// AppKit Serial Debugger
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_KIT_SERIAL_DEBUGGER_H
#define APP_KIT_SERIAL_DEBUGGER_H

#include "ExtKitSerialDebugger.h"

namespace microbit_dal_app_kit {

/// App Serial Debugger
class AppSerialDebugger : public microbit_dal_ext_kit::SerialDebugger
{
public:
	/// Constructor
	AppSerialDebugger();

protected:
	/// Inherited
	/* SerialDebugger */ bool /* consumed */ doHandleDirectCommand(ManagedString command);

	/// Inherited
	/* SerialDebugger */ bool /* consumed */ doHandleLineCommand(ManagedString command);

	/// Inherited
	/* SerialDebugger */ void debug_sendCmdHelp();

	/// Inherited
	/* SerialDebugger */ void debug_sendConfig();

	/// Inherited
	/* SerialDebugger */ void debug_sendDeviceInfo();

};	// AppSerialDebugger

}	// microbit_dal_app_kit

#endif	// APP_KIT_SERIAL_DEBUGGER_H

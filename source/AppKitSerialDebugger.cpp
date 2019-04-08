/// An example for using microbit-dal-ext-kit
/**	@package	microbit_dal_app_kit
*/

/// AppKit Serial Debugger
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKitSerialDebugger.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

AppSerialDebugger::AppSerialDebugger()
	: SerialDebugger("AppSerialDebugger")
{
}

/* to be overridden */ bool /* consumed */ AppSerialDebugger::doHandleDirectCommand(ManagedString command)
{
	return SerialDebugger::doHandleDirectCommand(command);
}

/* to be overridden */ bool /* consumed */ AppSerialDebugger::doHandleLineCommand(ManagedString command)
{
	if((command.length() > 0) && (command.charAt(0) == ':')) {
		if(command.length() == 4) {
			const char c1 = command.charAt(1);
			const char c2 = command.charAt(2);
			const char c3 = command.charAt(3);
			if(((c1 == 'r') || (c1 == 'R')) &&
			   ((c2 == 'a') || (c2 == 'A')) &&
			   ((c3 == 'm') || (c3 == 'M')))
			{	// Restart App Mode
				static RequestToken request;
				PeriodicObserver& po = PeriodicObserver::global();
				request.value = po.kRequestToCancel;
				po.issueRequest(request);
				return true;	// consumed
			}
		}
	}
	return SerialDebugger::doHandleLineCommand(command);
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendHelpForDirectCommands()
{
	SerialDebugger::debug_sendHelpForDirectCommands();
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendHelpForLineCommands()
{
	SerialDebugger::debug_sendHelpForLineCommands();

	static const char* const lineArray[] = {
		":ram    Restart App Mode",
		0	// END OF TABLE
	};

	debug_sendLines(lineArray);
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendConfig()
{
	SerialDebugger::debug_sendConfig();
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendDeviceInfo()
{
	SerialDebugger::debug_sendDeviceInfo();

	debug_sendLine("microbit_dal_ext_kit-example version: " YOTTA_MICROBIT_DAL_EXT_KIT_EXAMPLE_VERSION_STRING, false);
}

}	// microbit_dal_app_kit

/// AppKit Serial Debugger
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppKitSerialDebugger.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

AppSerialDebugger::AppSerialDebugger()
	: SerialDebugger("AppSerialDebugger")
{
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendConfig()
{
	SerialDebugger::debug_sendConfig();

//	debug_sendLine("--- Yotta Config (microbit_dal_ext_kit-example) ---", false);
}

/* SerialDebugger */ void AppSerialDebugger::debug_sendDeviceInfo()
{
	SerialDebugger::debug_sendDeviceInfo();
	debug_sendLine("microbit_dal_ext_kit-example version: " YOTTA_MICROBIT_DAL_EXT_KIT_EXAMPLE_VERSION_STRING, false);
}

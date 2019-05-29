/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_H
#define APP_MODE_H

#include "ExtKitAppMode.h"

#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode Describer
class AppModeDescriber : public microbit_dal_ext_kit::AppModeDescriberProtocol
{
public:
	/// Inherited
	/* AppModeDescriberProtocol */ const char* const * hints() const;

	/// Inherited
	/* AppModeDescriberProtocol */ const char* menuKeyFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ const char* descriptionFor(microbit_dal_ext_kit::AppMode appMode) const;

	/// Inherited
	/* AppModeDescriberProtocol */ int /* count */ appModesFor(microbit_dal_ext_kit::Features condition, const char* menuKeyFilter, microbit_dal_ext_kit::AppMode** /* OUT new[] */ outAppModes) const;

};	// AppModeDescriber

/// Check Avaiable Hardware
microbit_dal_ext_kit::Features checkAvaiableHardware();

/// Instantiate App Mode
/* new */ AppModeBase* instantiateAppMode();

}	// microbit_dal_app_kit

#endif	// APP_MODE_H

/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Gravity Sensor
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#ifndef APP_MODE_GRAVITY_SENSOR_H
#define APP_MODE_GRAVITY_SENSOR_H

#include "AppModeBase.h"

namespace microbit_dal_app_kit {

/// App Mode for Gravity Sensor
class AppModeGravitySensor : public AppModeBase
{
public:
	/// Inherited
	static /* Component */ bool isConfigured();

	/// Constructor
	AppModeGravitySensor();

protected:
	/// Inherited
	/* AppModeBase */ void doHandleEvent(const MicroBitEvent& event);

	/// Inherited
	/* AppModeBase */ void doHandlePeriodic100ms(uint32_t count);

};	// AppModeGravitySensor

}	// microbit_dal_app_kit

#endif	// APP_MODE_GRAVITY_SENSOR_H

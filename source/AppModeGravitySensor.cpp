/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// App Mode for Gravity Sensor
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

#include "AppModeGravitySensor.h"	// self
#include "AppKit.h"

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@class	AppModeGravitySensor
*/

static const Features kAppMode	= appMode::kGravitySensor;

/* Component */ bool AppModeGravitySensor::isConfigured()
{
	Features configured = feature::configured();
	return configured == kAppMode;
}

AppModeGravitySensor::AppModeGravitySensor()
	: AppModeBase("AppModeGravitySensor")
{
	static const EventDef events[] = {
		{ messageBusID::kLocalEvent,  messageBusEvent::kLocalAppStarted },
		{ MICROBIT_ID_ANY, MICROBIT_EVT_ANY }	// END OF TABLE
	};
	selectEvents(events);
}

/* AppModeBase */ void AppModeGravitySensor::doHandleEvent(const MicroBitEvent& event)
{
	uint16_t source = event.source;
	uint16_t value = event.value;
	if(source == messageBusID::kLocalEvent) {
		if(value == messageBusEvent::kLocalAppStarted) {
			display::clear();
		}
	}
}

/* AppModeBase */ void AppModeGravitySensor::doHandlePeriodic100ms(uint32_t /* count */)
{
	// Check Accelerometer
	MicroBitAccelerometer* a = ExtKit::global().accelerometer();
	if(a) {
		Sample3D samples;
		samples = a->getSample();

		int x;
		if(samples.x < -600)		x = 0;
		else if (samples.x < -250)	x = 1;
		else if (600 < samples.x)	x = 4;
		else if (250 < samples.x)	x = 3;
		else						x = 2;

		int y;
		if(samples.y < -600)		y = 0;
		else if (samples.y < -250)	y = 1;
		else if (600 < samples.y)	y = 4;
		else if (250 < samples.y)	y = 3;
		else						y = 2;

		MicroBitImage image(5,5);
		image.setPixelValue(x, y, 1);
		display::showImage(image);
	}
}

}	// microbit_dal_app_kit

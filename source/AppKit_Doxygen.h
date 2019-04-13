/// An example for using `microbit-dal-ext-kit`
/**	@package	microbit_dal_app_kit
*/

/// Doxygen Topics
/**	@file
	@author	Copyright (c) 2019 Tomoyuki Nakashima.<br>
			This code is licensed under MIT license. See `LICENSE` in the project root for more information.
	@note	Run Doxygen (http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.
*/

using namespace microbit_dal_ext_kit;

namespace microbit_dal_app_kit {

/**	@page	microbit-dal-ext-kit-example	Topics - microbit-dal-ext-kit-example
		- @subpage	AppKit_Main
		- @subpage	AppKit_AppMode
		- @subpage	AppKit_RemoteStateCategory
		- @subpage	AppKit_BuildConfig
		- @subpage	AppKit_Headers
*/

/**	@page	AppKit_Main	Main Flow
		@dontinclude	AppKitMain.cpp
		The following steps are excerpts of the main flow. See <a href=_app_kit_main_8cpp_source.html>AppKitMain.cpp</a> for the complete source code.
		-# Create a device class instance of `MicroBitExtKit` or `PrimitiveExtKit`.
			The instance should not be created in stack memory (like local variables).
			-	@skipline	#define
			- If ENABLE_ALL_MICROBIT_FEATURES is true, an instance of `MicroBitExtKit` is created as variabe `uBit`.
				@skipline	#if
			-	@skip		//
				@until		static
			- If ENABLE_ALL_MICROBIT_FEATURES is not true, an instance of `AppExtKit`, which inherits `PrimitiveExtKit`, is created as variabe `uBit`.
				@skipline	#else
			-	@skip		class
				@until		};
			-	@skip		AppExtKit::AppExtKit()
				@until		}
			-	@skip		void AppExtKit::init()
				@until		}
			-	@skip		//
				@until		static
			-	@skipline	#endif
			- See also @ref	ExtKit_Device.
			.
		-# Create other instances.
			The instances should not be created in stack memory (like local variables).
			- 	@skip		//
				@until		sDebugger;
			- 	@skip		//
				@until		sDescriber;
			- 	@skip		//
				@until		sPeriodicObserver;
		-# Start main().
			-	@skipline	main()
		-# Initialize the device.
			-	@skip		//
				@until	uBit.init();
		-# Start the Serial Debugger.
			-	@skip		//
				@until		sDebugger.start();
			-	@skip		//
				@until		display::scrollString(APP_STRING_BOOTUP);
		-# Check Avaiable Hardware.
			-	@skip		//
				@until		EXT_KIT_ASSERT
		-# Select an App Mode.
			-	@skip		//
				@until		while (true)
			-	@skip		//
				@until		EXT_KIT_ASSERT
			- See also @ref	AppKit_AppMode.
		-# Set display rotation.
			-	@skip		//
				@until		display::setDisplayRotation
		-# Start the corresponding App Mode Component.
			-	@skip		//
				@until		appMode->start();
			-	@skip		//
				@until		display::clear();
		-# Fire the App Stared event.
			-	@skip		//
				@until		MicroBitEvent
		-# Start the Periodic Observer.
			-	@skip		//
				@until		sPeriodicObserver.waitForCompletion();
		-# Stop services.
			-	@skip		//
				@until		delete appMode;
			-	@skipline	}
*/

/**	@page	AppKit_AppMode	App Mode - the set of components specific to a micro:bit setup and usage

	# App Mode for ElecFreaks' Joystick:bit
		The following App Mode is selected automatically if Joystick:bit board is connected to the micro:bit.
		- App Mode J (`appMode::kJoystickController`) <br>
			`AppModeJoystickController` provides a transmitter using ElecFreaks' Joystick:bit.

	# App Mode for SparkFun's moto:bit
		The following App Mode is selected automatically if moto:bit board is connected to the micro:bit.
		- App Mode M (`appMode::kMotors`) <br>
			`AppModeMotors` provides a receiver using SparkFun's moto:bit.

	# App Modes for Waveshare's Mini Piano Module
		The following App Modes are available if Mini Piano Module is connected to the micro:bit.
		- App Mode P (`appMode::kPianoPlayer`) <br>
			`AppModePianoPlayer` provides a stand-alone piano player using Waveshare's Mini Piano Module
		- App Mode K (`appMode::kPianoKeyController`) <br>
			`AppModePianoKeyController` provides a transmitter using Waveshare's Mini Piano Module.

	# App Modes for Kitronik's Zip Halo with a buzzer connected to port P2
		The following App Mode is selected automatically if a buzzer is connected to port P2 on the micro:bit.
		- App Mode O (`appMode::kNeoPixelRing`) <br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo with a Buzzer.

	# App Modes for a receiver with a buzzer connected to port P1
		The following App Mode is selected automatically if a buzzer is connected to port P1 on the micro:bit.
		- App Mode B (`appMode::kBuzzer`) <br>
			`AppModeGenericReceiver` provides a receiver with a Buzzer.

	# App Modes for no auto-detection
		The following App Modes are available if all of detections above are failed.
		- App Mode R (`appMode::kGenericReceiver`) <br>
			`AppModeGenericReceiver` provides a generic receiver using micro:bit only.
		- App Mode T (`appMode::kGenericTransmitter`) <br>
			`AppModeGenericTransmitter` provides a generic transmitter using micro:bit only.
		- App Mode Z (`appMode::kZipHalo`) <br>
			`AppModeNeoPixelRing` provides a receiver using Kitronik's Zip Halo.
*/

/**	@page	AppKit_RemoteStateCategory	Remote State Category - the set of remote states sent from the transmiiter to the reciver over radio

	# Remote State Category For Buttons
		The category sends and receives states of `Buttons` and `Direction`. <br>
		The following App Modes support the category using `RemoteStateTransmitterCategoryForButtons` and `RemoteStateReceiverCategoryForButtons`.
		<table>
		<tr>
			<td>
				Transmitter
			</td>
			<td>
				Receiver
			</td>
		</tr>
		<tr>
			<td>
				App Mode J (`appMode::kJoystickController`) <br>
				App Mode T (`appMode::kGenericTransmitter`)
			</td>
			<td>
				App Mode M (`appMode::kMotors`) <br>
				App Mode O (`appMode::kNeoPixelRing`) <br>
				App Mode Z (`appMode::kZipHalo`) <br>
				App Mode R (`appMode::kGenericReceiver`)
			</td>
		</tr>
		</table>

	# Remote State Category For PianoKeys
		The category The category sends and receives states of `PianoKeys` and `Octave`. <br>
		The following App Modes support the category using `RemoteStateTransmitterCategoryForPianoKeys` and `RemoteStateReceiverCategoryForPianoKeys`.
		<table>
		<tr>
			<td>
				Transmitter
			</td>
			<td>
				Receiver
			</td>
		</tr>
		<tr>
			<td>
				App Mode K (`appMode::kPianoKeyController`)
			</td>
			<td>
				App Mode O (`appMode::kNeoPixelRing`) <br>
				App Mode B (`appMode::kBuzzer`)
			</td>
		</tr>
		</table>
*/

/**	@page	AppKit_BuildConfig	Build Configuration

	# Build Configuration
		- The `module.json` file in the module root is used to describe the module or executable, especially the module name and dependencies to other modules.
		- Here is an example of `module.json` for `microbit-dal-ext-kit-example` executable.
			@dontinclude	./module.json
			- @skipline	{
			- @until	"name"
				- The module name is `microbit-dal-ext-kit-example`.
			- @until	"license"
			- @until	},
				- The module depends on the following module.
					- https://github.com/softgraph/microbit-dal-ext-kit
			- @until	"private"
			- @until	"bin"
				- The module is an executable.
			- @skipline	}
		- For the details of `module.json`, see the site below.
			@reference
				- <a href="http://docs.yottabuild.org/reference/module.html"><b>module.json Reference</b> (yottabuild.org)</a>
*/

}	// microbit_dal_app_kit

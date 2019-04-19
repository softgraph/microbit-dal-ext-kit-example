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

/**	@page	Topics_microbit-dal-ext-kit-example	Topics - microbit-dal-ext-kit-example
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

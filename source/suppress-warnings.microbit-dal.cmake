
if(CMAKE_COMPILER_IS_GNUCC)
	message("suppressing warnings from microbit-dal")
	target_compile_options(microbit-dal
		PRIVATE "-ftabstop=4"
		PRIVATE "-Warray-bounds=0"
		PRIVATE "-Wno-class-memaccess"
	)
endif()

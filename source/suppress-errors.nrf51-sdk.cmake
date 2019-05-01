# This .cmake file intends to fix the following gcc compile error reported only for a debug (less-optimized) build, e.g., `yotta build --debug-build`.
#	- `error: r7 cannot be used in asm here`
#	  (reported at inline assembly code with a clobbered register list including `r7`)
# For a release (optimized) build, the same error is suppressed by `-fomit-frame-pointer` gcc option that is implicitly enabled by other optimization options, e.g., `-O`, `-O1` or higher.
# Therefore, the explicit `-fomit-frame-pointer` option is required to suppress the error also for a debug build.
# See also:
#	- https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
#	- https://tls.mbed.org/kb/development/arm-thumb-error-r7-cannot-be-used-in-asm-here

if(CMAKE_COMPILER_IS_GNUCC)
	message("suppressing errors from nrf51-sdk")
	target_compile_options(nrf51-sdk
		PRIVATE "-fomit-frame-pointer"
	)
endif()

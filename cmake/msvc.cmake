SET(PASSOA_COMPILER_MSVC TRUE)
add_definitions(-DPLAT_MSVC)

set(PA_LIBS 
	optimized crypto
	optimized system
	optimized filesystem
	debug cryptod
	debug systemd
	debug filesystemd
	)
			 
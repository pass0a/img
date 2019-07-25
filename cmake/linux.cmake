
SET(PASSOA_COMPILER_GCC TRUE)
add_definitions(-DPLAT_GCC)

set(PA_LIBS 
    system
    filesystem
	crypto
    pthread
    dl
    )


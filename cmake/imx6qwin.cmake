# this is required
SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
message("" ${CMAKE_ARM_GCC})
# specify the cross compiler
SET(CMAKE_C_COMPILER ${CMAKE_ARM_GCC}/bin/arm-linux-gnueabihf-gcc.exe)
message("" ${CMAKE_C_COMPILER})
SET(CMAKE_CXX_COMPILER ${CMAKE_ARM_GCC}/bin/arm-linux-gnueabihf-g++.exe)

#SET(CMAKE_MAKE_PROGRAM ${CMAKE_ARM_GCC}/bin/make.exe)
# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  ${CMAKE_ARM_GCC})
# SET(CMAKE_EXT_LIBRARAY_PATH  E:/usr/linaro/imx6q)
# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


SET(PASSOA_COMPILER_GCC TRUE)
add_definitions(-DPLAT_GCC)

set(PA_LIBS 
    system
    filesystem
	crypto
    pthread
    dl
    )


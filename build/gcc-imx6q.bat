set GENERATOR=Unix Makefiles
set TOOLCHAIN="-DCMAKE_TOOLCHAIN_FILE=../../cmake/imx6qwin.cmake"

if exist 3rd_arm rd 3rd_arm /S/Q
mkdir 3rd_arm
cd 3rd_arm

cmake ../../generate -G "%GENERATOR%" %TOOLCHAIN% -DCMAKE_INSTALL_PREFIX=../../stage -DPASSOA3RD=ON -DCMAKE_ARM_GCC=E:/usr/linaro/gcc -DCMAKE_MAKE_PROGRAM=E:/usr/linaro/gcc/bin/make.exe
cmake --build ./ --target install --config Release
cd ..

if exist imx6q rd imx6q /S/Q
mkdir imx6q
cd imx6q

cmake ../../generate -G "%GENERATOR%" %TOOLCHAIN% -DCMAKE_INSTALL_PREFIX=../../output -DPASSOA=ON -DCMAKE_ARM_GCC=E:/usr/linaro/gcc -DCMAKE_MAKE_PROGRAM=E:/usr/linaro/gcc/bin/make.exe
cmake --build ./ --target install --config Release
cd ..
pause
set TOOLCHAIN="-DCMAKE_TOOLCHAIN_FILE=../../cmake/msvc.cmake"
set GENERATOR=Visual Studio 14 2015

if not exist 3rd mkdir 3rd
cd 3rd

cmake ../../3rd/libjpeg-turbo -G "%GENERATOR%" -T v140_xp -DCMAKE_INSTALL_PREFIX=../../stage
cmake --build ./ --target install --config Release
cd ..

if not exist x32win mkdir x32win
cd x32win

cmake ../../generate -G "%GENERATOR%" %TOOLCHAIN% -T v140_xp -DCMAKE_INSTALL_PREFIX=../../output
cmake --build ./ --target install --config Release
cd ..
pause
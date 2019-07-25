
if exist 3rd_android rd 3rd_android /S/Q
mkdir 3rd_android
cd 3rd_android

cmake ../../3rd/libjpeg-turbo -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=D:/dev/androidsdk/sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_STL=c++_static -DANDROID_TOOLCHAIN=clang -DANDROID_PLATFORM=android-17 -DANDROID_ABI=armeabi-v7a -DCMAKE_MAKE_PROGRAM=D:/dev/msys2/mingw32/bin/mingw32-make.exe -DCMAKE_INSTALL_PREFIX=../../stage 
cmake --build ./ --target install
cd ..

if not exist android mkdir android
cd android

cmake ../../generate -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=E:/downloads/android-ndk-r19c/build/cmake/android.toolchain.cmake -DCMAKE_INSTALL_PREFIX=../../output -DANDROID_STL=c++_static -DANDROID_TOOLCHAIN=clang -DANDROID_PLATFORM=android-17 -DANDROID_ABI=armeabi-v7a -DCMAKE_MAKE_PROGRAM=D:/dev/msys2/mingw32/bin/mingw32-make.exe

cmake --build ./ --target install --config Release
cd ..
pause
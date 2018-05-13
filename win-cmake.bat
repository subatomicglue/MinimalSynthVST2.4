
::make vcvars local to this script only
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
rmdir /S/Q build-win32
mkdir build-win32 & pushd build-win32
cmake -G "Visual Studio 14" ..
popd
endlocal

setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
rmdir /S/Q build-win64
mkdir build-win64 & pushd build-win64
cmake -G "Visual Studio 14 Win64" ..
popd
endlocal


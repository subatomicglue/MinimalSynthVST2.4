::make vcvars local to this script only
setlocal

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
cmake --build build-win32 --config Release

endlocal

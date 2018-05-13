
if NOT EXIST  build-win32\Mantis.sln (
    call win-cmake.bat
)
if NOT EXIST  build-win32\Release\Mantis307.dll (
    call win-build32.bat
)
if NOT EXIST  build-win64\Release\Mantis307.dll (
    call win-build64.bat
)

cmake --build build-win32 --config Release --target dist
cmake --build build-win64 --config Release --target dist

::IF NOT EXIST  build-win32\Release\getversion.exe (
::    call win-cmake.bat
::    call win-build32.bat
::    call win-build64.bat
::)

:: read the version into %VERSION%
::for /f %%i in ('build-win32\Release\getversion.exe') do set VERSION=%%i

::pushd nsis
::call "c:\Program Files (x86)\NSIS\makensis.exe" /DARCH=x64 /DVERSION=%VERSION% /DTHEDLL=..\build-win64\Release\Mantis307.dll /DOUTFILE=mantis307-VSTi-Windows-x64-%VERSION%.exe mantis307.nsi
::call "c:\Program Files (x86)\NSIS\makensis.exe" /DARCH=x86 /DVERSION=%VERSION% /DTHEDLL=..\build-win32\Release\Mantis307.dll /DOUTFILE=mantis307-VSTi-Windows-x86-%VERSION%.exe mantis307.nsi
::popd

move nsis\mantis307*.exe .



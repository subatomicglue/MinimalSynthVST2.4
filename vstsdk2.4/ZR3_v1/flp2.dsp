# Microsoft Developer Studio Project File - Name="flp2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=flp2 - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "flp2.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "flp2.mak" CFG="flp2 - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "flp2 - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "flp2 - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "flp2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FLP2_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /Gi /vd0 /O2 /Ob2 /I "c:\Eigene Dateien\vstsdk2\source\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D WINDOWS=1 /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 winmm.lib vstgui.lib kernel32.lib comdlg32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.3 /dll /pdb:none /machine:I386 /nodefaultlib:"LIBCMT.lib" /out:"Release/flp4.dll" /libpath:"c:\Eigene Dateien\vstsdk2\win\library"
# SUBTRACT LINK32 /verbose /map /debug
# Begin Special Build Tool
# End Special Build Tool

!ELSEIF  "$(CFG)" == "flp2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "flp2___Win32_Debug"
# PROP BASE Intermediate_Dir "flp2___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gi /vd0 /Ot /Ow /Og /Oi /Oy /I "e:\dokumente\vstsdk2\source\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D WINDOWS=1 /FD /c
# ADD CPP /nologo /MDd /W3 /vd0 /GR /GX /ZI /Od /Oy /I "c:\Eigene Dateien\vstsdk2\source\common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D WINDOWS=1 /FAs /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib vstgui.lib kernel32.lib comdlg32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:0.10 /dll /pdb:none /machine:I386 /nodefaultlib:"LIBCMT.lib" /libpath:"e:\dokumente\vstsdk2\win\library"
# SUBTRACT BASE LINK32 /verbose /map /debug
# ADD LINK32 winmm.lib vstgui.lib kernel32.lib comdlg32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:0.10 /dll /map /debug /machine:I386 /nodefaultlib:"LIBCMT.lib" /out:"Debug/flp4.dll" /libpath:"c:\Eigene Dateien\vstsdk2\win\library"
# SUBTRACT LINK32 /verbose /pdb:none
# Begin Special Build Tool
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "flp2 - Win32 Release"
# Name "flp2 - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\AudioEffect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\audioeffectx.cpp
# End Source File
# Begin Source File

SOURCE=.\Controls.cpp
# End Source File
# Begin Source File

SOURCE=.\Editor.cpp
# End Source File
# Begin Source File

SOURCE=.\flp.cpp
# End Source File
# Begin Source File

SOURCE=.\flp2.def
# End Source File
# Begin Source File

SOURCE=.\flp_frame.cpp
# End Source File
# Begin Source File

SOURCE=.\flpmain.cpp
# End Source File
# Begin Source File

SOURCE=.\flpproc.cpp
# End Source File
# Begin Source File

SOURCE=.\FX.cpp
# End Source File
# Begin Source File

SOURCE=.\res_flp2.rc
# End Source File
# Begin Source File

SOURCE=.\voice_classes.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\AEffect.h
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\aeffectx.h
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\AudioEffect.hpp
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\audioeffectx.h
# End Source File
# Begin Source File

SOURCE=.\Controls.h
# End Source File
# Begin Source File

SOURCE=.\Editor.h
# End Source File
# Begin Source File

SOURCE=.\flp.h
# End Source File
# Begin Source File

SOURCE=.\FX.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\voice_classes.h
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\vstfxstore.h
# End Source File
# Begin Source File

SOURCE=..\..\vstsdk2\source\common\vstgui.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cknob.bmp
# End Source File
# Begin Source File

SOURCE=.\dbblack.bmp
# End Source File
# Begin Source File

SOURCE=.\dbbrown.bmp
# End Source File
# Begin Source File

SOURCE=.\dbwhite.bmp
# End Source File
# Begin Source File

SOURCE=.\inside.bmp
# End Source File
# Begin Source File

SOURCE=".\make a change.bmp"
# End Source File
# Begin Source File

SOURCE=.\miniledred.bmp
# End Source File
# Begin Source File

SOURCE=.\minioffon.bmp
# End Source File
# Begin Source File

SOURCE=.\num_yellow.bmp
# End Source File
# Begin Source File

SOURCE=.\onoffgreen.bmp
# End Source File
# Begin Source File

SOURCE=.\panelfx.bmp
# End Source File
# Begin Source File

SOURCE=.\panelvoice.bmp
# End Source File
# Begin Source File

SOURCE=.\vonoff.bmp
# End Source File
# End Group
# End Target
# End Project

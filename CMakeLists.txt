
# to build for the native host (works on windows too) call:
# for 32bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules/Native32.cmake
# for 64bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules/Native64.cmake
#
# to cross compile to Windows (from Mac/Lin/etc.) call:
# for 32bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules/Windows32.cmake
# for 64bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules/Windows64.cmake
#
# to natively build on Windows, but customize version of MSVC, call:
# for 32bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules\Native32.cmake -G "Visual Studio 14"
#  cmake --build . --config Release   # build by command line
# for 64bit:
#  cmake -DCMAKE_TOOLCHAIN_FILE=Modules\Native64.cmake -G "Visual Studio 14 Win64"
#  cmake --build . --config Release   # build by command line
#
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Modules/cmake_example/Modules")

set(PROJECT_NAME "Minimal")
SET(CPACK_PACKAGE_VERSION_MAJOR 0)
SET(CPACK_PACKAGE_VERSION_MINOR 0)
SET(CPACK_PACKAGE_VERSION_MICRO 0)
SET(CPACK_PACKAGE_VERSION_PATCH 1)
SET(VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_MICRO}.${CPACK_PACKAGE_VERSION_PATCH}" )

################################################################
message( "==========   Now configuring build for ${PROJECT_NAME} v${VERSION}   --  determining...   ==========" )
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_COLOR_MAKEFILE ON)
set(WINDOWS_EXPORT_ALL_SYMBOLS  TRUE)
project(${PROJECT_NAME}
  VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_MICRO}.${CPACK_PACKAGE_VERSION_PATCH}
)

# enable .rc file compilation
if (WIN32 OR MSVC)
  enable_language(RC) # cmake doesn't automatically pick this up
                      # and calling it from our Platform/Llvm...
                      # results in recursive error from cmake
endif()

# get the Architeture and # of bits
SET(ARCH ${CMAKE_LIBRARY_ARCHITECTURE}) # x86 or x64
if (WIN32 AND NOT CMAKE_CROSSCOMPILING)
  if(NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    SET(ARCH "x86") # x86 or x64
  else()
    SET(ARCH "x64") # x86 or x64
  endif()
endif()
if (ARCH STREQUAL x86)
  SET(BITS 32)
else()
  SET(BITS 64)
endif()
message( "APPLE:                 ${APPLE}" )
message( "WIN32:                 ${WIN32}" )
message( "cross compile:         ${CMAKE_CROSSCOMPILING}" )
message( "==========   Now configuring build for ${PROJECT_NAME}-${ARCH} v${VERSION}   --  ${BITS}bit   ==========" )
################################################################

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

##################### global compiler setup ##########################
if(UNIX AND NOT APPLE)
  # API fix for Linux builds #
  add_definitions( -D__cdecl= -DVERSION=${VERSION} )
endif()
if (MSVC)
   enable_language(RC)
   add_definitions(/D_CRT_SECURE_NO_WARNINGS /DVERSION=${VERSION} /DWIN32 /EHa /EHs) # cl.exe compatible options here
   if (CMAKE_CROSSCOMPILING)
      add_definitions(-Wno-deprecated-register ) # clang-cl options here
   endif()
endif()


# location for user's vst plugins
set(APPLE_VSTPLUGINS_DIR "$ENV{HOME}/Library/Audio/Plug-Ins/VST")
set(WINDOWS_VSTPLUGINS_DIR "/Program Files (x86)/VSTPlugins/")
set(WINDOWS64_VSTPLUGINS_DIR "/Program Files/VSTPlugins/")

if (APPLE)
  set(VSTGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_mac.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/plugin-bindings/aeffguieditor.cpp
  )
  set(VSTGUI_STANDALONE
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_standalone_mac.mm
  )
endif()
if (WIN32)
  set(VSTGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_win32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/plugin-bindings/aeffguieditor.cpp
  )
  set(VSTGUI_STANDALONE
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_standalone_win32.cpp
  )
  # exception handling for certain files.
  #set_source_files_properties(vstgui/vstgui/vstgui_win32.cpp PROPERTIES COMPILE_FLAGS "/EHa /EHs")
  #set_source_files_properties(vstgui/vstgui/plugin-bindings/aeffguieditor.cpp PROPERTIES COMPILE_FLAGS "/EHa /EHs")
endif()
if (UNIX AND NOT APPLE)
  set(VSTGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_linux.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/plugin-bindings/aeffguieditor.cpp
  )
  set(VSTGUI_STANDALONE
    ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/vstgui_standalone.cpp
  )
endif()

set(VST_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/public.sdk/source/vst2.x/audioeffect.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/public.sdk/source/vst2.x/audioeffectx.cpp
)
set(VST_SOURCES_PLUGMAIN
  ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/public.sdk/source/vst2.x/vstplugmain.cpp
)

set(MINIMAL_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/MinimalEffect.cpp
)

set(RESOURCE_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/bmp00128.png
)

set(VSTPLUGIN_INCLUDE_DIRS
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/public.sdk/source/vst2.x/
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/pluginterfaces/vst2.x/
)
set(VSTHOST_INCLUDE_DIRS
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/pluginterfaces/vst2.x/
   ${CMAKE_CURRENT_SOURCE_DIR}/vstsdk2.4/public.sdk/source/vst2.x
)
set(VSTGUI_INCLUDE_DIRS
   ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui
   ${CMAKE_CURRENT_SOURCE_DIR}/vstgui/vstgui/lib
)
set(INCLUDE_DIRS
	${VSTGUI_INCLUDE_DIRS}
	${VSTPLUGIN_INCLUDE_DIRS}
)

if (WIN32)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc.in ${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc)
  set(DEF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/windows.def ${CMAKE_CURRENT_SOURCE_DIR}/Resource.rc)
  set(LINK_LIBS Gdi32.lib Shell32.lib Ole32.lib User32.lib Comdlg32.lib Advapi32.lib)
endif()
if (APPLE)
	set_source_files_properties(PkgInfo PROPERTIES MACOSX_PACKAGE_LOCATION .)
	set(DEF_FILE PkgInfo)
	set(LINK_LIBS
	   "-framework CoreServices"
	   "-framework Carbon"
	   "-framework QuartzCore"
	   "-framework AppKit"
	   "-framework Accelerate"
	   "-framework System"
	   "-framework OpenGL"
	)
	set(ICONS
	   ${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_128x128.png
	   ${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_16x16.png
	   ${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_16x16@2x.png
	   ${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_32x32@2x.png
	   ${CMAKE_CURRENT_SOURCE_DIR}/icon.icns
	   ${CMAKE_CURRENT_SOURCE_DIR}/icon.png
	)
endif()


# vstgui static lib
set(PROJECT_NAME "vstgui")
include_directories(${VSTGUI_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC ${VSTGUI_SOURCES})

# vstsdk static lib
set(PROJECT_NAME "vstsdk")
include_directories(${VSTPLUGIN_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC ${VST_SOURCES})

# the vst effect as a static lib
set(PROJECT_NAME "MinimalCore")
include_directories(${VSTPLUGIN_INCLUDE_DIRS})
add_library(${PROJECT_NAME} STATIC ${MINIMAL_SOURCES})


#######################################################################################
# Minimal VST
#######################################################################################

set(PROJECT_NAME "Minimal")
include_directories(${INCLUDE_DIRS})
add_library(${PROJECT_NAME} MODULE ${VST_SOURCES_PLUGMAIN} ${DEF_FILE} ${ICONS} ${RESOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS} MinimalCore vstgui vstsdk)
if (DEFINED MANTIS_EMBEDDED)
  target_compile_options(${PROJECT_NAME} PUBLIC -DNONAG -DNOGUI)
endif()

# MacOSX bundle properties
if (APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
	  BUNDLE true
	  BUNDLE_EXTENSION "vst"
	  XCODE_ATTRIBUTE_WRAPPER_EXTENSION "vst"
	  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/Info.plist.in"
	  MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
	  MACOSX_BUNDLE_GUI_IDENTIFIER "net.subatomiclabs.vstplugin.${PROJECT_NAME}"
	  #  MACOSX_FRAMEWORK_IDENTIFIER "net.subatomiclabs.vstplugin.${PROJECT_NAME}"
	  MACOSX_BUNDLE_ICON_FILE icon.icns
	  MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
    MACOSX_BUNDLE_COPYRIGHT "(c) subatomiclabs (2008-Present)"
	  RESOURCE "${RESOURCE_FILES}"
	)
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_128x128.png PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_16x16.png PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_16x16@2x.png PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icons/mantis_32x32@2x.png PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icon.png PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/icon.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   # aaaaand.... this is the only one that actually sets the icon for the folder:
   # The Info.plist works for .app bundles, but we have a .vst bundle
   # So we need to set the .vst bundle using "extended attributes" in MacOSX (like SetFile -a C, GetFileInfo).
   # This little 'fileicon' utility does it:
   add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/fileicon set ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vst ${CMAKE_CURRENT_SOURCE_DIR}/icon.png
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Assign a icon to the bundle..."
   )
endif()


# make install
# DLLs are treated as RUNTIME, .so's are treated as LIBRARY, and .a and .lib as ARCHIVE, MacOSX bundles as BUNDLE
if(APPLE)
  install(TARGETS ${PROJECT_NAME}
    BUNDLE # DLLs are treated as RUNTIME, .so's are treated as LIBRARY, and .a and .lib as ARCHIVE, MacOSX bundles as BUNDLE
    LIBRARY DESTINATION  ${APPLE_VSTPLUGINS_DIR}/Minimal-${ARCH}
    BUNDLE DESTINATION  ${APPLE_VSTPLUGINS_DIR}/Minimal-${ARCH}
    RUNTIME DESTINATION .
    COMPONENT MinimalInstall
    #RESOURCE DESTINATION  "${APPLE_VSTPLUGINS_DIR}/${PROJECT_NAME}.vst/Contents/Resources/"
  )
elseif(WIN32)
  install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${WINDOWS_VSTPLUGINS_DIR}/Minimal-${ARCH}
	LIBRARY DESTINATION ${WINDOWS_VSTPLUGINS_DIR}/Minimal-${ARCH}
    COMPONENT MinimalInstall
  )
elseif(UNIX AND NOT APPLE) #Linux
   install(TARGETS ${PROJECT_NAME}
    LIBRARY # DLLs are treated as RUNTIME, .so's are treated as LIBRARY, and .a and .lib as ARCHIVE, MacOSX bundles as BUNDLE
    DESTINATION "/usr/lib/lxvst"
    RUNTIME DESTINATION .
    COMPONENT MinimalInstall
  )
endif()
if(APPLE)
   set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DVST_2_4_EXTENSIONS -DMACX -DMAC -Wno-#warnings -Wno-invalid-source-encoding -Wno-deprecated-register -Wno-unused-value -Wno-nonportable-include-path -Wno-deprecated-declarations")
endif()





# Install script for directory: G:/QtProject/Dyplom/QXlsx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Dyplom")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "G:/Qt/Tools/mingw1310_64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/libQXlsxQt6.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QXlsx" TYPE FILE FILES
    "G:/QtProject/Dyplom/QXlsx/header/xlsxabstractooxmlfile.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxabstractsheet.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxabstractsheet_p.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxcellformula.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxcell.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxcelllocation.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxcellrange.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxcellreference.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxchart.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxchartsheet.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxconditionalformatting.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxdatavalidation.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxdatetype.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxdocument.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxformat.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxglobal.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxrichstring.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxworkbook.h"
    "G:/QtProject/Dyplom/QXlsx/header/xlsxworksheet.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/CMakeFiles/QXlsx.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake"
         "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES
    "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/QXlsxQt6Config.cmake"
    "G:/QtProject/Dyplom/build/Desktop_Qt_6_11_0_MinGW_64_bit-Release/QXlsx/QXlsxQt6ConfigVersion.cmake"
    )
endif()


cmake_minimum_required(VERSION 3.0.2)
project(hayaemon_qt)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
               "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

find_package(Qt5Widgets)
find_package(Qt5Multimedia)

if (Qt5Widgets_FOUND)
  if (Qt5Widgets_VERSION VERSION_LESS 5.6.3)
    message(FATAL_ERROR "Minimum supported Qt5 version is 5.6.3!")
  else ()
    message("Qt5 version ${Qt5Widgets_VERSION}")
  endif ()
else ()
  message(SEND_ERROR "The Qt5Widgets library could not be found!")
endif (Qt5Widgets_FOUND)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_COMMON
  ${SRC_DIR}/Common/Bass.h
  ${SRC_DIR}/Common/BassFx.h
  ${SRC_DIR}/Common/CommandList.h
  ${SRC_DIR}/Common/Define.h
  ${SRC_DIR}/Common/DoubleSpinBox.h
  ${SRC_DIR}/Common/ListView.cpp
  ${SRC_DIR}/Common/ListView.h
  ${SRC_DIR}/Common/SliderCtrl.h
  ${SRC_DIR}/Common/SliderCtrlCore.h
  ${SRC_DIR}/Common/SpinBox.h
  ${SRC_DIR}/Common/StaticCore.h
  ${SRC_DIR}/Common/Tab.h
  ${SRC_DIR}/Common/Utils.cpp
  ${SRC_DIR}/Common/Utils.h
)
set(SRC_COUNTLOOPWND
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd_MainWnd.cpp
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd_MainWnd.h
)
set(SRC_DECFREQWND
  ${SRC_DIR}/DecFreqWnd/DecFreqWnd_MainWnd.cpp
  ${SRC_DIR}/DecFreqWnd/DecFreqWnd_MainWnd.h)
set(SRC_DECSPEEDWND
  ${SRC_DIR}/DecSpeedWnd/DecSpeedWnd_MainWnd.cpp
  ${SRC_DIR}/DecSpeedWnd/DecSpeedWnd_MainWnd.h)
set(SRC_INCFREQWND
  ${SRC_DIR}/IncFreqWnd/IncFreqWnd_MainWnd.cpp
  ${SRC_DIR}/IncFreqWnd/IncFreqWnd_MainWnd.h)
set(SRC_INCSPEEDWND
  ${SRC_DIR}/IncSpeedWnd/IncSpeedWnd_MainWnd.cpp
  ${SRC_DIR}/IncSpeedWnd/IncSpeedWnd_MainWnd.h)
set(SRC_LIMITSETTINGWND
  ${SRC_DIR}/LimitSettingWnd/LimitSettingWnd_MainWnd.cpp
  ${SRC_DIR}/LimitSettingWnd/LimitSettingWnd_MainWnd.h)
set(SRC_MAINWND
  ${SRC_DIR}/MainWnd/3DReverbCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/3DReverbCustomizeWnd.h
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.cpp
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.h
  ${SRC_DIR}/MainWnd/AllSaveWnd_MainWnd.cpp
  ${SRC_DIR}/MainWnd/AllSaveWnd_MainWnd.h
  ${SRC_DIR}/MainWnd/ChorusCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/ChorusCustomizeWnd.h
  ${SRC_DIR}/MainWnd/CompressorCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/CompressorCustomizeWnd.h
  ${SRC_DIR}/MainWnd/DelayCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/DelayCustomizeWnd.h
  ${SRC_DIR}/MainWnd/DistortionCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/DistortionCustomizeWnd.h
  ${SRC_DIR}/MainWnd/Explorer.cpp
  ${SRC_DIR}/MainWnd/Explorer.h
  ${SRC_DIR}/MainWnd/ExplorerBar.cpp
  ${SRC_DIR}/MainWnd/ExplorerBar.h
  ${SRC_DIR}/MainWnd/FlangerCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/FlangerCustomizeWnd.h
  ${SRC_DIR}/MainWnd/GargleCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/GargleCustomizeWnd.h
  ${SRC_DIR}/MainWnd/EQLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/EQLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/EQSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/EQSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/FreqLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/FreqLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/FreqSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/FreqSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/M3UFile.cpp
  ${SRC_DIR}/MainWnd/M3UFile.h
  ${SRC_DIR}/MainWnd/MainWnd.cpp
  ${SRC_DIR}/MainWnd/MainWnd.h
  ${SRC_DIR}/MainWnd/MainWnd_inline.h
  ${SRC_DIR}/MainWnd/Menu_MainWnd.cpp
  ${SRC_DIR}/MainWnd/Menu_MainWnd.h
  ${SRC_DIR}/MainWnd/OpenURLWnd.cpp
  ${SRC_DIR}/MainWnd/OpenURLWnd.h
  ${SRC_DIR}/MainWnd/PanLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PanLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/PanSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PanSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/PitchLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PitchLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/PitchSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PitchSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/PitchSpinBox.h
  ${SRC_DIR}/MainWnd/Platform.h
  ${SRC_DIR}/MainWnd/Platform.cpp
  ${SRC_DIR}/MainWnd/Platform_macOS.cpp
  ${SRC_DIR}/MainWnd/PlayListView_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PlayListView_MainWnd.h
  ${SRC_DIR}/MainWnd/PlayPositionWnd.cpp
  ${SRC_DIR}/MainWnd/PlayPositionWnd.h
  ${SRC_DIR}/MainWnd/PlayRangeWnd.cpp
  ${SRC_DIR}/MainWnd/PlayRangeWnd.h
  ${SRC_DIR}/MainWnd/PresetMenu.cpp
  ${SRC_DIR}/MainWnd/PresetMenu.h
  ${SRC_DIR}/MainWnd/PresetNameInputWnd.cpp
  ${SRC_DIR}/MainWnd/PresetNameInputWnd.h
  ${SRC_DIR}/MainWnd/ReverbCustomizeWnd.cpp
  ${SRC_DIR}/MainWnd/ReverbCustomizeWnd.h
  ${SRC_DIR}/MainWnd/RMenu_Explorer.cpp
  ${SRC_DIR}/MainWnd/RMenu_Explorer.h
  ${SRC_DIR}/MainWnd/RMenu_ListView.cpp
  ${SRC_DIR}/MainWnd/RMenu_ListView.h
  ${SRC_DIR}/MainWnd/Sound.cpp
  ${SRC_DIR}/MainWnd/Sound.h
  ${SRC_DIR}/MainWnd/Sound_inline.h
  ${SRC_DIR}/MainWnd/SpeedLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/SpeedLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/SpeedSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/SpeedSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/TimeLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/TimeLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/TimeSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/TimeSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/ToolBar_MainWnd.cpp
  ${SRC_DIR}/MainWnd/ToolBar_MainWnd.h
  ${SRC_DIR}/MainWnd/Tab_MainWnd.cpp
  ${SRC_DIR}/MainWnd/Tab_MainWnd.h
  ${SRC_DIR}/MainWnd/Utility.h
  ${SRC_DIR}/MainWnd/VolumeLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/VolumeLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/VolumeSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/VolumeSlider_MainWnd.h
)
set(SRC_METRONOMEWND
  ${SRC_DIR}/MetronomeWnd/MetronomeWnd_MainWnd.cpp
  ${SRC_DIR}/MetronomeWnd/MetronomeWnd_MainWnd.h)
set(SRC_TIMERPLAYWND
  ${SRC_DIR}/TimerPlayWnd/TimerPlayWnd_MainWnd.cpp
  ${SRC_DIR}/TimerPlayWnd/TimerPlayWnd_MainWnd.h)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
if (WIN32)
  set(BASS_DIR ${THIRDPARTY_DIR}/bass/win32)
  set(BASSLIB_DIR ${BASS_DIR}/lib/x64)
elseif (APPLE)
  set(BASS_DIR ${THIRDPARTY_DIR}/bass/macOS)
  set(BASSLIB_DIR ${BASS_DIR}/lib)
endif()
set(TAGLIB_DIR ${THIRDPARTY_DIR}/taglib-1.11.1)

if (WIN32)
  set(SRC_BASS
    ${BASS_DIR}/include/bass/bass.h
    ${BASS_DIR}/include/bass/bass_aac.h
    ${BASS_DIR}/include/bass/bass_ape.h
    ${BASS_DIR}/include/bass/bass_fx.h
    ${BASS_DIR}/include/bass/bassalac.h
    ${BASS_DIR}/include/bass/basscd.h
    ${BASS_DIR}/include/bass/bassenc.h
    ${BASS_DIR}/include/bass/bassflac.h
    ${BASS_DIR}/include/bass/tags.h)
elseif (APPLE)
  set(SRC_BASS
    ${BASS_DIR}/include/bass/bass.h
    ${BASS_DIR}/include/bass/bass_ape.h
    ${BASS_DIR}/include/bass/bass_fx.h
    ${BASS_DIR}/include/bass/bassflac.h
    ${BASS_DIR}/include/bass/tags.h)
endif()

source_group(Bass FILES ${SRC_BASS})
source_group(Common FILES ${SRC_COMMON})
source_group(CountLoopWnd FILES ${SRC_COUNTLOOPWND})
source_group(DecSpeedWnd FILES ${SRC_DECSPEEDWND})
source_group(IncSpeedWnd FILES ${SRC_INCSPEEDWND})
source_group(DecFreqWnd FILES ${SRC_DECFREQWND})
source_group(IncFreqWnd FILES ${SRC_INCFREQWND})
source_group(LimitSettingWnd FILES ${SRC_LIMITSETTINGWND})
source_group(MainWnd FILES ${SRC_MAINWND})
source_group(MetronomeWnd FILES ${SRC_METRONOMEWND})
source_group(TimerPlayWnd FILES ${SRC_TIMERPLAYWND})
source_group("" FILES
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D_UNICODE -DUNICODE -DTAGLIB_STATIC)
if (WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
elseif (APPLE)
  set(CMAKE_CXX_FLAGS_RELEASE "-O3  -mmacosx-version-min=10.9")
  set(CMAKE_EXE_LINKER_FLAGS "-O3 -mmacosx-version-min=10.9")
endif()

qt5_add_resources(RESOURCES ${SRC_DIR}/Hayaemon.qrc)
qt5_wrap_ui(UI_MOC
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd.ui
  ${SRC_DIR}/IncSpeedWnd/IncSpeedWnd.ui
  ${SRC_DIR}/LimitSettingWnd/LimitSettingWnd.ui
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.ui
  ${SRC_DIR}/MainWnd/AllSaveWnd.ui
  ${SRC_DIR}/MainWnd/ChorusCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/CompressorCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/DelayCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/DistortionCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/FlangerCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/GargleCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/MainWnd.ui
  ${SRC_DIR}/MainWnd/OpenURLWnd.ui
  ${SRC_DIR}/MainWnd/PlayPositionWnd.ui
  ${SRC_DIR}/MainWnd/PlayRangeWnd.ui
  ${SRC_DIR}/MainWnd/PresetNameInputWnd.ui
  ${SRC_DIR}/MainWnd/Reverb3DCustomizeWnd.ui
  ${SRC_DIR}/MainWnd/ReverbCustomizeWnd.ui
  ${SRC_DIR}/MetronomeWnd/MetronomeWnd.ui
  ${SRC_DIR}/TimerPlayWnd/TimerPlayWnd.ui)

include_directories(
  ${SRC_DIR}/Common
  ${SRC_DIR}/MainWnd
  ${BASS_DIR}/include
  ${TAGLIB_DIR}/include)
link_directories(${BASSLIB_DIR})

if (WIN32)
  set(APP_BUNDLE WIN32)
  set(APP_ICON ${CMAKE_SOURCE_DIR}/resource/windows.rc)
elseif (APPLE)
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(APP_BUNDLE MACOSX_BUNDLE)
    set(APP_ICON_NAME icon1.icns)
    set(APP_ICON ${CMAKE_SOURCE_DIR}/resource/${APP_ICON_NAME})
    # set(MACOSX_BUNDLE_BUNDLE_NAME Hayaemon)
    # set(MACOSX_BUNDLE_GUI_IDENTIFIER "")
    set(MACOSX_BUNDLE_ICON_FILE ${APP_ICON_NAME})
    set_source_files_properties(
      ${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    # set(MACOSX_BUNDLE_INFO_STRING "")
    # set(MACOSX_BUNDLE_SHORT_VERSION_STRING "" )
    # set(MACOSX_BUNDLE_LONG_VERSION_STRING "")
    # set(MACOSX_BUNDLE_BUNDLE_VERSION "")
    # set(MACOSX_BUNDLE_COPYRIGHT "")
    set(BUNDLE_DISPLAY_NAME Hayaemon)
  endif ()
endif ()

add_executable(Hayaemon
  ${APP_BUNDLE}
  ${APP_ICON}
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
  ${SRC_BASS}
  ${SRC_COMMON}
  ${SRC_COUNTLOOPWND}
  ${SRC_DECSPEEDWND}
  ${SRC_INCSPEEDWND}
  ${SRC_DECFREQWND}
  ${SRC_INCFREQWND}
  ${SRC_LIMITSETTINGWND}
  ${SRC_MAINWND}
  ${SRC_METRONOMEWND}
  ${SRC_TIMERPLAYWND}
  ${RESOURCES}
  ${UI_MOC}
)
if (WIN32)
  target_link_libraries(Hayaemon
    bass
    bass_aac
    bass_ape
    bass_fx
    bassalac
    basscd
    bassenc
    bassflac
    tags
    winmm
    debug ${TAGLIB_DIR}/lib/win32/Debug/tag.lib
    optimized ${TAGLIB_DIR}/lib/win32/Release/tag.lib)
elseif (APPLE)
  target_link_libraries(Hayaemon
    bass
    bassenc
    bass_ape
    bass_fx
    bassflac
    tags
    debug ${TAGLIB_DIR}/lib/macOS/Debug/libtag.a
    optimized ${TAGLIB_DIR}/lib/macOS/Release/libtag.a
    z)
   set_target_properties(Hayaemon PROPERTIES MACOSX_BUNDLE_INFO_PLIST
                         ${SRC_DIR}/Info.plist.in)
endif ()

qt5_use_modules(Hayaemon Widgets Multimedia)

if (WIN32)
  file(GLOB_RECURSE BASSLIB_FILES ${BASSLIB_DIR}/*.dll)
elseif (APPLE)
  file(GLOB_RECURSE BASSLIB_FILES ${BASSLIB_DIR}/*.dylib)
endif ()

foreach (LIB_FILE ${BASSLIB_FILES})
  add_custom_command(TARGET Hayaemon
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${LIB_FILE} $<TARGET_FILE_DIR:Hayaemon>/.)
endforeach ()

add_custom_command(TARGET Hayaemon
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/sound
    $<TARGET_FILE_DIR:Hayaemon>/sound
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/licenses
    $<TARGET_FILE_DIR:Hayaemon>/licenses
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/resource/click.wav
    $<TARGET_FILE_DIR:Hayaemon>/.)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/sound
        DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES ${CMAKE_SOURCE_DIR}/resource/click.wav
        DESTINATION ${CMAKE_INSTALL_PREFIX})
if (WIN32)
  install(TARGETS Hayaemon RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
  install(DIRECTORY ${BASSLIB_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX}
          FILES_MATCHING PATTERN "*.dll")
  install(FILES ${THIRDPARTY_DIR}/lame/win32/bin/x64/lame.exe
          DESTINATION ${CMAKE_INSTALL_PREFIX})
  install(FILES ${THIRDPARTY_DIR}/oggenc/win32/bin/x64/oggenc2.exe
          DESTINATION ${CMAKE_INSTALL_PREFIX})
elseif (APPLE)
  if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    install(TARGETS Hayaemon BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX})
  else ()
    install(TARGETS Hayaemon RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
  endif ()
  install(DIRECTORY ${BASSLIB_DIR}/ DESTINATION ${CMAKE_INSTALL_PREFIX}
          FILES_MATCHING PATTERN "*.dylib")
endif ()

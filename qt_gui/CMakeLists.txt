cmake_minimum_required(VERSION 3.0.2)
project(hayaemon_qt)

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_COMMON
  ${SRC_DIR}/Common/Bass.h
  ${SRC_DIR}/Common/BassFx.h
  ${SRC_DIR}/Common/CommandList.h
  ${SRC_DIR}/Common/Define.h
  ${SRC_DIR}/Common/SliderCtrl.h
  ${SRC_DIR}/Common/SliderCtrlCore.h
  ${SRC_DIR}/Common/StaticCore.h
  ${SRC_DIR}/Common/Tab.h
)
set(SRC_COUNTLOOPWND
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd_MainWnd.cpp
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd_MainWnd.h
)
set(SRC_MAINWND
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.cpp
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.h
  ${SRC_DIR}/MainWnd/EQLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/EQLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/EQSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/EQSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/FreqLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/FreqLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/FreqSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/FreqSlider_MainWnd.h
  ${SRC_DIR}/MainWnd/MainWnd.cpp
  ${SRC_DIR}/MainWnd/MainWnd.h
  ${SRC_DIR}/MainWnd/Menu_MainWnd.cpp
  ${SRC_DIR}/MainWnd/Menu_MainWnd.h
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
  ${SRC_DIR}/MainWnd/Platform_macOS.cpp
  ${SRC_DIR}/MainWnd/PlayListView_MainWnd.cpp
  ${SRC_DIR}/MainWnd/PlayListView_MainWnd.h
  ${SRC_DIR}/MainWnd/Sound.cpp
  ${SRC_DIR}/MainWnd/Sound.h
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
  ${SRC_DIR}/MainWnd/Tab_MainWnd.h
  ${SRC_DIR}/MainWnd/Utility.h
  ${SRC_DIR}/MainWnd/VolumeLabel_MainWnd.cpp
  ${SRC_DIR}/MainWnd/VolumeLabel_MainWnd.h
  ${SRC_DIR}/MainWnd/VolumeSlider_MainWnd.cpp
  ${SRC_DIR}/MainWnd/VolumeSlider_MainWnd.h
)

if (WIN32)
set(BASS_DIR ${CMAKE_SOURCE_DIR}/3rdparty/bass/win32)
elseif (APPLE)
set(BASS_DIR ${CMAKE_SOURCE_DIR}/3rdparty/bass/macOS)
endif()

if (WIN32)
set(SRC_BASS
  ${BASS_DIR}/include/bass/bass.h
  ${BASS_DIR}/include/bass/bass_aac.h
  ${BASS_DIR}/include/bass/bass_ape.h
  ${BASS_DIR}/include/bass/bass_fx.h
  ${BASS_DIR}/include/bass/bassalac.h
  ${BASS_DIR}/include/bass/basscd.h
  ${BASS_DIR}/include/bass/bassflac.h
)
elseif (APPLE)
set(SRC_BASS
  ${BASS_DIR}/include/bass/bass.h
  ${BASS_DIR}/include/bass/bass_ape.h
  ${BASS_DIR}/include/bass/bass_fx.h
  ${BASS_DIR}/include/bass/bassflac.h
)
endif()

source_group(Bass FILES ${SRC_BASS})
source_group(Common FILES ${SRC_COMMON})
source_group(CountLoopWnd FILES ${SRC_COUNTLOOPWND})
source_group(MainWnd FILES ${SRC_MAINWND})
source_group("" FILES
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_UNICODE -DUNICODE)
if (WIN32)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

qt5_add_resources(RESOURCES ${SRC_DIR}/Hayaemon.qrc)
qt5_wrap_ui(UI_MOC
  ${SRC_DIR}/CountLoopWnd/CountLoopWnd.ui
  ${SRC_DIR}/MainWnd/ABLoopPosWnd.ui
  ${SRC_DIR}/MainWnd/MainWnd.ui)

include_directories(
  ${SRC_DIR}/Common
  ${SRC_DIR}/MainWnd
  ${BASS_DIR}/include)
if (WIN32)
link_directories(${BASS_DIR}/lib/x64)
elseif (APPLE)
link_directories(${BASS_DIR}/lib)
endif()

add_executable(Hayaemon
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
  ${SRC_BASS}
  ${SRC_COMMON}
  ${SRC_COUNTLOOPWND}
  ${SRC_MAINWND}
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
  bassflac
)
elseif (APPLE)
target_link_libraries(Hayaemon
  bass
  bass_ape
  bass_fx
  bassflac
)
endif()

qt5_use_modules(Hayaemon Widgets)

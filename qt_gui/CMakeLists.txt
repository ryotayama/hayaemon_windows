cmake_minimum_required(VERSION 3.0.2)
project(hayaemon_qt)

find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_COMMON
  ${SRC_DIR}/Common/Define.h
)
set(SRC_MAINWND
  ${SRC_DIR}/MainWnd/MainWnd.cpp
  ${SRC_DIR}/MainWnd/MainWnd.h
)

source_group(Common FILES ${SRC_COMMON})
source_group(MainWnd FILES ${SRC_MAINWND})
source_group("" FILES
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
)

qt5_add_resources(RESOURCES ${SRC_DIR}/Hayaemon.qrc)
qt5_wrap_ui(UI_MOC ${SRC_DIR}/MainWnd/MainWnd.ui)

add_executable(Hayaemon
  ${SRC_DIR}/App.cpp
  ${SRC_DIR}/App.h
  ${SRC_COMMON}
  ${SRC_MAINWND}
  ${RESOURCES}
  ${UI_MOC}
)

qt5_use_modules(Hayaemon Widgets)

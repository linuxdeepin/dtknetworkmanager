# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

cmake_minimum_required(VERSION 3.13)

# If do't define version number, specify the version number
set (VERSION "1.0.0" CACHE STRING "define project version")

project(DtkNetworkManager
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/linuxdeepin/dtknetworkmanager
    DESCRIPTION "NetworkManager DBus interface binding for Qt"
    VERSION ${VERSION}
)

set(LIB_NAME dtknetworkmanager)

# specify install dir
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra")
set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--as-needed")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/DtkNetworkManager)
set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/include/dtk/DNetworkManager)
# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose Debug or Release" FORCE)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TESTING ON)
    set(BUILD_EXAMPLES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

find_package(PkgConfig)
pkg_search_module(NetworkManager REQUIRED IMPORTED_TARGET libnm>=1.4.0)
pkg_search_module(Gio REQUIRED IMPORTED_TARGET gio-2.0)
find_package(DtkCore REQUIRED)
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core DBus Network)

add_subdirectory(src)

set(BUILD_DOCS ON CACHE BOOL "Generate doxygen-based documentation")
find_package(Doxygen)
if (BUILD_DOCS AND DOXYGEN_FOUND)
    add_subdirectory(docs)
endif ()

# test
if (BUILD_TESTING)
   add_subdirectory(tests)
endif ()

# examples
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

target_link_directories(${LIB_NAME} INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_LIBDIR}>
)

write_basic_package_version_file(
    DtkNetworkManagerConfigVersion.cmake
    VERSION ${VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(misc/DtkNetworkManagerConfig.cmake.in
    DtkNetworkManagerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DtkNetworkManager
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

# for pc file config
set(PC_LIBS_PRIVATE Qt${QT_VERSION_MAJOR}Core)
set(PC_REQ_PRIVATE)
set(PC_REQ_PUBLIC)

# config pkgconfig file
set(PC_REQUIRES "Qt${QT_VERSION_MAJOR}Core Qt${QT_VERSION_MAJOR}DBus Qt${QT_VERSION_MAJOR}Network dtkcore Gio NetworkManager")
configure_file(misc/${LIB_NAME}.pc.in ${LIB_NAME}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DtkNetworkManagerConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/DtkNetworkManagerConfigVersion.cmake DESTINATION ${ConfigPackageLocation})

# config qmake moudule file
set(DTK_MODULE ${LIB_NAME})
set(DTK_DEPS "core dbus network dtkcore")
set(DTK_CFG "v2 ltcg")
set(QMKSPECS_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/qt${QT_VERSION_MAJOR}/mkspecs/modules" CACHE STRING "INSTALL DIR FOR qt pri files")
configure_file(misc/qt_lib_${LIB_NAME}.pri.in qt_lib_${LIB_NAME}.pri @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/qt_lib_${LIB_NAME}.pri DESTINATION "${QMKSPECS_INSTALL_DIR}")

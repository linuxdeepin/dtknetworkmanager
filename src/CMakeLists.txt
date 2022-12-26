# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB SETTING_HEADER "../include/settings/*h")
file(GLOB COMMON_HEADER "../include/*.h")

file(GLOB_RECURSE SRCS
    "./*.h"
    "./*.cpp"
)

add_library(${LIB_NAME} SHARED
    ${COMMON_HEADER}
    ${SETTING_HEADER}
    ${SRCS}
)

set(EXPORT_HEADERS ${COMMON_HEADER} ${SETTING_HEADER})

target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/settings>
    $<BUILD_INTERFACE:${DtkCore_INCLUDE_DIRS}>)

target_include_directories(${LIB_NAME} INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_definitions(${LIB_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

target_link_libraries(${LIB_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    ${DtkCore_LIBRARIES}
    PkgConfig::Gio
    PkgConfig::NetworkManager
)

set_target_properties(${LIB_NAME} PROPERTIES
    EXPORT_NAME NetworkManager
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${EXPORT_HEADER}")

install(TARGETS ${LIB_NAME} EXPORT DtkNetworkManagerTargets
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${COMMON_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/)
install(FILES ${SETTING_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/settings)

install(EXPORT DtkNetworkManagerTargets
    FILE DtkNetworkManagerTargets.cmake
    NAMESPACE Dtk::
    DESTINATION ${ConfigPackageLocation}
)

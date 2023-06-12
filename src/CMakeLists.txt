# SPDX-FileCopyrightText: 2022 - 2023 UnionTech Software Technology Co., Ltd.
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

target_include_directories(${LIB_NAME}
PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/settings>
INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_directories(${LIB_NAME} INTERFACE
$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
$<INSTALL_INTERFACE:${LIBRARY_INSTALL_DIR}>)

target_compile_definitions(${LIB_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

target_link_libraries(${LIB_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    Dtk${DTK_VERSION_MAJOR}::Core
    PkgConfig::Gio
    PkgConfig::NetworkManager
)

set_target_properties(${LIB_NAME} PROPERTIES
    EXPORT_NAME NetworkManager
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${EXPORT_HEADER}")

install(TARGETS ${LIB_NAME} EXPORT ${DtkNetworkManager}Targets
LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${COMMON_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/)
install(FILES ${SETTING_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/settings)

install(EXPORT ${DtkNetworkManager}Targets
    FILE ${DtkNetworkManager}Targets.cmake
    NAMESPACE Dtk${DTK_VERSION_MAJOR}::
    DESTINATION ${CONFIG_CMAKE_INSTALL_DIR}
)

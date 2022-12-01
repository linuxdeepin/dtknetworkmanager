# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

file(GLOB SETTING_HEADER "../include/settings/*h")
file(GLOB COMMON_HEADER "../include/*.h")

file(GLOB_RECURSE SRCS
    "./*.h"
    "./*.cpp"
)

add_library(${BIN_NAME} SHARED
    ${COMMON_HEADER}
    ${SETTING_HEADER}
    ${SRCS}
)

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    ${DtkCore_INCLUDE_DIRS}
    ../include
    ../include/settings
    ./dbus
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Network
    ${DtkCore_LIBRARIES}
    PkgConfig::Gio
    PkgConfig::NetworkManager
)

install(FILES ${COMMON_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(FILES ${SETTING_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME}/settings)
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})

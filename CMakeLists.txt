cmake_minimum_required(VERSION 3.14)

project(sharing_service)

# By default select Debug build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core DBus REQUIRED)

set(PROJECT_SOURCES
src/main.cpp src/sharingdbusadaptor.cpp src/sharingdbusadaptor.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core
                                        Qt${QT_VERSION_MAJOR}::DBus)

install(TARGETS ${PROJECT_NAME}
    COMPONENT sharingservice
    RUNTIME DESTINATION "/home/"
    LIBRARY DESTINATION "/home/"
    DESTINATION "/home/"
)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK")
INCLUDE(CPack)
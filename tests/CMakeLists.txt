# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.9.5)

if (NOT DEFINED VERSION)
    set(VERSION 1.0.0)
endif ()
configure_file(../gomoku/assets/environments.h.in environments.h @ONLY)
#可访问private
ADD_COMPILE_OPTIONS(-fno-access-control)
ADD_COMPILE_OPTIONS(-fno-inline)
set(APP_SRC_DIR "${CMAKE_SOURCE_DIR}/gomoku")
set(APP_BIN_NAME "deepin-gomoku-test")
set(PROJECT_NAME_TEST ${APP_BIN_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_VERSION_MAJOR 6)
#set(CMAKE_CXX_FLAGS "-g -Wall")
#编译生成覆盖环境
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
#添加-fno-inline编译选项，禁止内联，能获取到函数地址，可以对内联函数进行打桩
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-inline")
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "sw_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mieee")
endif ()

set(CMAKE_SAFETYTEST "${CMAKE_SAFETYTEST_ARG}")
if(CMAKE_SAFETYTEST STREQUAL "")
    set(CMAKE_SAFETYTEST "CMAKE_SAFETYTEST_ARG_OFF")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${CMAKE_SAFETYTEST}")
if(CMAKE_SAFETYTEST STREQUAL "CMAKE_SAFETYTEST_ARG_ON")
  #安全测试选项
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=undefined,address -O2")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=undefined,address -O2")
endif()

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    set(DTK_VERSION 6)
endif()

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Multimedia REQUIRED)
find_package(Dtk${DTK_VERSION}Core REQUIRED)
find_package(Dtk${DTK_VERSION}Widget REQUIRED)
find_package(Dtk${DTK_VERSION}Gui REQUIRED)
# find_package(Qt5LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}DBus REQUIRED)
add_definitions(${Qt${QT_VERSION_MAJOR}Test_DEFINITIONS})

include_directories(${APP_SRC_DIR}/src)

SUBDIRLIST(all_src ${APP_SRC_DIR}/src)

#Include all app own subdirectorys
foreach(subdir ${all_src})
    include_directories(${APP_SRC_DIR}/src/${subdir})
endforeach()
file(GLOB_RECURSE Gomoku_SRC ${APP_SRC_DIR}/src/*.cpp)
list(REMOVE_ITEM Gomoku_SRC ${APP_SRC_DIR}/src/main.cpp)
FILE(GLOB qrcFiles
    ../src/resources.qrc
)


# 5. 头文件
# 5.1. 定义函数，用于递归添加头文件
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_sub_directories_recursively("${CMAKE_CURRENT_SOURCE_DIR}/../gomoku/src")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
SUBDIRLIST(all_src ${CMAKE_CURRENT_SOURCE_DIR}/src)
#Include all app own subdirectorys
foreach(subdir ${all_src})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir})
endforeach()

include_directories(${Dtk${DTK_VERSION}Widget_INCLUDE_DIRS})
include_directories(${Dtk${DTK_VERSION}Core_INCLUDE_DIRS})
include_directories(${Dtk${DTK_VERSION}Gui_INCLUDE_DIRS})
include_directories(${Qt${QT_VERSION_MAJOR}TestLib_LIBRARIES}
    ${PROJECT_NAME_TEST}
    ${Qt${QT_VERSION_MAJOR}DBus_LIVRARIES}
)

#angr安全加固
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector-all")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -z relro -z now -z noexecstack -pie")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -z relro -z now -z noexecstack -pie")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE Gomoku_TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
include_directories(src)


add_executable(${PROJECT_NAME_TEST} ${Gomoku_SRC} ${qrcFiles} ${Gomoku_TEST_SRC} ${APP_QM_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${DtkWidget_INCLUDE_DIRS} ${OBJECT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME_TEST}
    ${Qt${QT_VERSION_MAJOR}DBus_LIVRARIES}
    ${LINK_LIBS}
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Test
    ${DFrameworkdbus_LIBRARIES}
    Dtk${DTK_VERSION}::Core
    Dtk${DTK_VERSION}::Gui
    Dtk${DTK_VERSION}::Widget
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::DBus
    Qt${QT_VERSION_MAJOR}::Multimedia
    pthread -ldl -fPIC
)


cmake_minimum_required(VERSION 3.10)
project(tst_plugin1 VERSION 1.0.0)

set(PRODUCTNAME "TST_PLUGIN1")
set(DESCRIPTION "TST_PLUGIN1")
set(COMPANY     "RTPTechGroup")
set(COPYRIGHT   "Copyright (C) RTPTechGroup")
set(LIBRARIES
    plugin
)

include(../plugins.cmake)

find_package(Qt5Core)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

find_package(Qt5Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

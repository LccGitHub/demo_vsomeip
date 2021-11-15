# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8.7)
project (threadutils)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/
)


link_directories(
    ${VSOME_PATH}/build
)


add_library(myutils SHARED LooperThreadBase.cpp LooperThreadImpl.cpp Message.cpp)

add_executable (thread_test test/TestFastLooperThread.cpp)
target_link_libraries(thread_test myutils pthread)




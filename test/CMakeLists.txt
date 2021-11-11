# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8.7)
project (vSomeIPHelloWorld)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(VSOME_PATH ${ROOT_PATH}/vsome/)
set(VSOME_INCLUDE_PATH ${ROOT_PATH}/vsome/interface/)

set (VSOMEIP_LIBRARIES vsomeip3)

include_directories(${VSOME_INCLUDE_PATH})


link_directories(
    ${VSOME_PATH}/build
)



add_executable (hello_world_client hello_world_client_main.cpp)
target_link_libraries(hello_world_client ${VSOMEIP_LIBRARIES})


add_executable (hello_world_service hello_world_service_main.cpp)
target_link_libraries(hello_world_service ${VSOMEIP_LIBRARIES} pthread)


#-------------------------------------------------------------------------------
# OSPRay Streamline Tests
#
# Copyright (c) 2018 RWTH Aachen University, Germany,
# Virtual Reality & Immersive Visualisation Group.
#-------------------------------------------------------------------------------
#                                  License
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ospray_streamline_tests LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH
  "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

find_package  (OSPRay REQUIRED)

add_executable(ospray_streamline_tests
  main.cpp
  ospray_app.cpp
  )
target_include_directories(ospray_streamline_tests
  PUBLIC
  ${OSPRAY_INCLUDE_DIRS}
  )
target_link_libraries(ospray_streamline_tests
  PUBLIC
  ${OSPRAY_LIBRARIES}
  )

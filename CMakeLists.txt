##
## Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
## directory of this distribution.
##
## Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
## may not be copied, modified, or distributed except according to those terms.
##
cmake_minimum_required(VERSION 2.8.7)
project(ll1_analyzer)

enable_testing()

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed.")
endif ()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-deprecated-register")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ll1_analyzer src/main.cc include/ast/ast.h include/ast/visitor.h include/ast/walker.h lib/walker.cc)

target_compile_features(ll1_analyzer PRIVATE cxx_range_for)

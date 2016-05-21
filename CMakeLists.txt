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

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wno-deprecated-register")

find_package(BISON REQUIRED)
if (${BISON_FOUND})
    bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/src/parser/parser.y
        ${CMAKE_SOURCE_DIR}/src/parser/parser.cc)
endif()

find_package(FLEX REQUIRED)
if (${FLEX_FOUND})
    flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/src/parser/lexer.l
    ${CMAKE_SOURCE_DIR}/src/parser/lexer.cc)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES_NO_MAIN)
list(REMOVE_ITEM SOURCES_NO_MAIN ${CMAKE_SOURCE_DIR}/src/main.cc)

file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/*.h")

# Define source groups
source_group(parser FILES
	${CMAKE_SOURCE_DIR}/src/parser/parser.y
	${CMAKE_SOURCE_DIR}/src/parser/lexer.l
    ${FLEX_FlexOutput_OUTPUTS}
	${BISON_BisonOutput_OUTPUTS}
)

source_group(src FILES ${SOURCES})
source_group(include FILES ${INCLUDES})

add_executable(ll1_analyzer
	${SOURCES} ${INCLUDES} ${FLEX_FlexOutput_OUTPUTS}
	${BISON_BisonOutput_OUTPUTS}
)

# Add unit test.
add_executable(unit_test
    ${CMAKE_SOURCE_DIR}/test/unit_tests.cc
    ${FLEX_FlexOutput_OUTPUTS}
    ${BISON_BisonOutput_OUTPUTS}
    ${SOURCES_NO_MAIN}
)

message(STATUS ${SOURCES_NO_MAIN})

add_test(
    NAME unit_test
    COMMAND ${CMAKE_BINARY_DIR}/unit_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test
)

target_compile_features(ll1_analyzer PRIVATE cxx_range_for)
target_compile_features(unit_test PRIVATE cxx_range_for)

cmake_minimum_required(VERSION 2.8.7)
project(lli_analyzer)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
   message(FATAL_ERROR "In-source builds are not allowed.")
endif()

# find_package(BISON)
# if (${BISON_FOUND})
#     bison_target(BisonOutput ${CMAKE_SOURCE_DIR}/src/parser/parser.y ${CMAKE_SOURCE_DIR}/src/parser.cc)
# endif()
#
# find_package(FLEX)
# if (${FLEX_FOUND})
#     flex_target(FlexOutput ${CMAKE_SOURCE_DIR}/src/parser/lexer.l ${CMAKE_SOURCE_DIR}/src/lexer.cc)
# endif()

include_directories(${CMAKE_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_SOURCE_DIR}/src SOURCES)

file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/*.h")

# Define source groups
source_group(parser FILES
	${CMAKE_SOURCE_DIR}/src/parser/parser.y
	${CMAKE_SOURCE_DIR}/src/parser/lexer.l
)

source_group(src FILES ${SOURCES})
source_group(include FILES ${INCLUDES})

add_executable(ll1_analyzer
	${SOURCES} ${INCLUDES} ${FLEX_FlexOutput_OUTPUTS}
	${BISON_BisonOutput_OUTPUTS}
)

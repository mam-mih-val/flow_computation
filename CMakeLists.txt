cmake_minimum_required(VERSION 3.15)
project(FlowComputation)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{QnTools_HOME})
list(APPEND CMAKE_PREFIX_PATH ${QnTools_HOME})

find_package(ROOT REQUIRED COMPONENTS RIO Tree)
find_package(QnTools REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall")
include(${ROOT_USE_FILE})

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${ROOT_INCLUDE_DIRS}
        ${QnTools_INCLUDE_DIR}/QnTools
)
#link_directories(
#        ${CMAKE_SOURCE_DIR}
#        ${QnTools_LIBRARY_DIR}
#)

set(HEADERS
        src/correlation.h
        src/correlation_builder.h
        src/functions.h
        )

set(SOURCES
        src/correlation.cc
        src/correlation_builder.cc
        )

set(${PROJECT_NAME}_INCLUDE_DIR "include")
set(${PROJECT_NAME}_LIBRARY_DIR "lib")

add_library(FlowComputation SHARED ${SOURCES})

add_executable(flow src/flow.cc)
target_link_libraries(flow QnTools::Base ${ROOT_LIBRARIES} FlowComputation)

install(TARGETS FlowComputation DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
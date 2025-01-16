cmake_minimum_required(VERSION 3.20)

project(zc_enum CXX)

option(ZC_ENUM_BUILD_TESTS "Create test target for zc_enum" ON)

set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

#if(MSVC)
#	#add_compile_options("/:bigobj  /:utf-8")
#endif()

include_directories("include")

add_library(zc_enum INTERFACE)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

target_include_directories(zc_enum
  INTERFACE 
    $<INSTALL_INTERFACE:include>    
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(NOT ZC_ENUM_BUILD_SHARED_LIBS)
  target_compile_definitions(zc_enum INTERFACE "zc_enum")
endif()

message(STATUS ${ZC_ENUM_BUILD_TESTS})

if(ZC_ENUM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

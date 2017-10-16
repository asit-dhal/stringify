cmake_minimum_required (VERSION 2.8.12)

project (Google-Benchmark)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Import our CMake modules
include(CheckCXXCompilerFlag)
include(AddCXXCompilerFlag)
include(CXXFeatureCheck)

cxx_feature_check(STD_REGEX)
cxx_feature_check(GNU_POSIX_REGEX)
cxx_feature_check(POSIX_REGEX)

if(NOT HAVE_STD_REGEX AND NOT HAVE_GNU_POSIX_REGEX AND NOT HAVE_POSIX_REGEX)
	message(FATAL_ERROR "Failed to determine the source files for the regular expression backend")
endif()

cxx_feature_check(STEADY_CLOCK)

find_package(Threads REQUIRED)

file(GLOB SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

add_library(benchmark STATIC ${SOURCE_FILES})

target_include_directories(
	benchmark PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

find_library(LIBRT rt)
if(LIBRT)
	target_link_libraries(benchmark ${LIBRT} ${CMAKE_THREAD_LIBS_INIT})
endif()

set_target_properties(benchmark
	PROPERTIES POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(benchmark)

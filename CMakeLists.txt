# -------------------------------------------------------------------------
# setup
# -------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

project(oqs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------------------------
# packages
# -------------------------------------------------------------------------
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# -------------------------------------------------------------------------
# third_party
# -------------------------------------------------------------------------
add_subdirectory(third_party EXCLUDE_FROM_ALL)
include_directories (${SPDLOG_INCLUDE_PATH} ${EIGEN_INCLUDE_PATH} ${CATCH_INCLUDE_PATH} ${INIH_INCLUDE_PATH})

# -------------------------------------------------------------------------
# library
# -------------------------------------------------------------------------

# configure variables
set(LIB_NAME "${PROJECT_NAME}")

# configure directories
set(LIB_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

# set includes
include_directories(${LIB_INCLUDE_PATH})

# set sources
file(GLOB_RECURSE LIB_HEADER_FILES "${LIB_INCLUDE_PATH}/*.h")

# set library
add_library(${LIB_NAME} INTERFACE)
add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

target_include_directories(
    ${LIB_NAME}
    INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

add_custom_target(${LIB_NAME}_lib SOURCES ${LIB_HEADER_FILES})

# -------------------------------------------------------------------------
# test
# -------------------------------------------------------------------------
enable_testing()
add_subdirectory(test)

# -------------------------------------------------------------------------
# example
# -------------------------------------------------------------------------
add_subdirectory(example)

# -------------------------------------------------------------------------
# copy .ini file from root to binary directory
# -------------------------------------------------------------------------
message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${PROJECT_SOURCE_DIR}/oqs.ini ${CMAKE_CURRENT_BINARY_DIR}/oqs.ini COPYONLY)

# -------------------------------------------------------------------------
# code coverage
# -------------------------------------------------------------------------
option (CODE_COVERAGE "Enable coverage reporting." OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	# Add required flags (GCC & LLVM/Clang)
	target_compile_options(${LIB_NAME} INTERFACE
		-O0        # no optimization
		-g         # generate debug info
		--coverage # sets all required flags
	)
	target_link_libraries(${LIB_NAME} INTERFACE --coverage)
endif()
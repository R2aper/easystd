cmake_minimum_required(VERSION 3.14)
project(estd LANGUAGES C)

# Setup output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Source files
file(GLOB ESTD_SRC "src/estd/*.c")
file(GLOB ESTD_HEADERS "include/estd/*.h")
set(ESTD_MAIN_HEADER "include/estd.h")

# Include directories
include_directories(include)

# Build type (Release/Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose Release or Debug" FORCE)
endif()

# Compiler flags by compiler
if(MSVC)
    # MSVC (cl)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /MP /permissive- /Iinclude")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Zi /Od")
else()
    # GCC/Clang
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Iinclude -Wall -Wextra -pedantic -fPIC")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
    # Use C23 if supported
    include(CheckCCompilerFlag)
    check_c_compiler_flag("-std=c23" HAS_C23_FLAG)
    if(HAS_C23_FLAG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c23")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    endif()
endif()

# Static library
add_library(estd_static STATIC ${ESTD_SRC})
set_target_properties(estd_static PROPERTIES OUTPUT_NAME "estd")

# Shared/Dynamic library
add_library(estd_shared SHARED ${ESTD_SRC})
set_target_properties(estd_shared PROPERTIES OUTPUT_NAME "estd")

# Platform-specific link libraries
if(MSVC)
    # MSVC does not need a separate math lib
else()
    target_link_libraries(estd_static m)
    target_link_libraries(estd_shared m)
endif()

# Install instructions
include(GNUInstallDirs)
install(TARGETS estd_static DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS estd_shared DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${ESTD_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/estd)
install(FILES ${ESTD_MAIN_HEADER} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

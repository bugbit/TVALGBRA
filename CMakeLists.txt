# CMakeList.txt: proyecto de CMake para TVALGBRA, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
#cmake_minimum_required (VERSION 3.8)
cmake_minimum_required (VERSION 3.5)
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.13.0")
    cmake_policy(SET CMP0077 NEW) # 'option()' honors normal variables.
endif()
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.15.0")
    cmake_policy(SET CMP0091 NEW) # MSVC runtime library flags are selected by an abstraction.
endif()

project ("TVALGBRA")

# Project options

include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    #define _doDeclare(a, b) int a ## b;
    #define _expand(a, ...) _doDeclare(a, __VA_ARGS__)
    #define _declare(a) _expand(a, __COUNTER__)

    _declare(a)
    _declare(a)
    _declare(a)

    int main() { return a1; }
"   SUPPORTS_COUNTER_MACRO)

function(tv_add_private_includes target)
    target_include_directories(${target} PRIVATE
        "${PROJECT_SOURCE_DIR}/tvision/include/tvision"
        "${PROJECT_SOURCE_DIR}/tvision/include/tvision/compat"
    )
    if (NOT WIN32 AND NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux"))
        target_include_directories(${target} PRIVATE
            "${PROJECT_SOURCE_DIR}/tvision/include/tvision/compat/malloc"
        )
    endif()
endfunction()

function(tv_app_enable_pch app)
        if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
            target_precompile_headers(${app} PRIVATE "${PROJECT_SOURCE_DIR}/tvision/include/pch.h")
        endif()
    endfunction()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    option(TV_BUILD_USING_GPM "Use GPM" ON)
    set(MAY_BUILD_USING_GPM TRUE)
endif()

if (MSVC)
    option(TV_USE_STATIC_RTL "Link against the static version of the runtime library (MSVC only)" OFF)
    if (TV_USE_STATIC_RTL)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
    set(MAY_USE_STATIC_RTL TRUE)
endif()

option(TV_REDUCE_APP_SIZE "Strip out unused funcions and data from executables" OFF)
if ((CMAKE_VERSION VERSION_LESS "3.13.0") AND TV_REDUCE_APP_SIZE)
    tv_message(WARNING "'TV_REDUCE_APP_SIZE' requested but only available in CMake 3.13.0 or newer.")
    set(TV_REDUCE_APP_SIZE OFF)
endif()

option(TV_LTO "Enable link-time optimization" OFF)

option(TV_LIBRARY_UNITY_BUILD "Use CMake's Unity Build" OFF)
if ((CMAKE_VERSION VERSION_LESS "3.16.0") AND TV_LIBRARY_UNITY_BUILD)
    tv_message(WARNING "'TV_LIBRARY_UNITY_BUILD' requested but only available in CMake 3.16.0 or newer.")
    set(TV_LIBRARY_UNITY_BUILD OFF)
endif()

# Agregue un origen al ejecutable de este proyecto.
add_executable (TVALGBRA "src/TVALGBRA.cpp" "src/TVALGBRA.h" "src/gadgets.cpp" "src/gadgets.h")

tv_add_private_includes(TVALGBRA)
tv_app_enable_pch(TVALGBRA)

# TODO: Agregue pruebas y destinos de instalación si es necesario.
add_subdirectory(tvision) # Assuming Turbo Vision is in the 'tvision' directory.
target_link_libraries(TVALGBRA tvision)
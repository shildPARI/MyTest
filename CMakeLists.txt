cmake_minimum_required(VERSION 3.20)
project(meinprojekt VERSION 1.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Eigener Test-Mode (zusätzlich zu Debug/Release)
option(ENABLE_TEST_MODE "Kompiliere mit Test-Features" OFF)

# Wenn kein Build-Typ gesetzt und Generator ist Single-Config, nimm Release als Default
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  message(STATUS "Keine CMAKE_BUILD_TYPE angegeben. Setze Default auf Release.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(SRC
    src/main.cpp
    src/test.cpp
)

# Executable
add_executable(meinprogramm ${SRC})

# Include directory for headers
target_include_directories(meinprogramm
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Füge Suffixe für unterschiedliche Build-Typen hinzu
set_target_properties(meinprogramm PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:_debug>$<$<BOOL:${ENABLE_TEST_MODE}>:_test>"
)

# Per-Konfiguration: Definitions (rein informativ im Code verwendbar)
target_compile_definitions(meinprogramm PRIVATE
  $<$<CONFIG:Debug>:DEBUG_MODE=1>
  $<$<CONFIG:Release>:RELEASE_MODE=1>
)

# Test-Mode schaltet zusätzliches Define
if(ENABLE_TEST_MODE)
  message(STATUS "⚙️  ENABLE_TEST_MODE ist AKTIV")
  target_compile_definitions(meinprogramm PRIVATE TEST_MODE=1)
else()
  message(STATUS "⚙️  ENABLE_TEST_MODE ist inaktiv")
endif()

# Warnflags
if (MSVC)
  target_compile_options(meinprogramm PRIVATE /W4)
else()
  target_compile_options(meinprogramm PRIVATE -Wall -Wextra -Wpedantic)
endif()

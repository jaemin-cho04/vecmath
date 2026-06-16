cmake_minimum_required(VERSION 3.16)
project(linalg LANGUAGES CXX)

# --- Project-wide settings ---------------------------------------------------
set(CMAKE_CXX_STANDARD 17)          # C++17. Bump to 20 later if you want.
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Treat warnings as useful signal. Add -Werror later once you're comfortable.
if (NOT MSVC)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- The library itself ------------------------------------------------------
# Every .cpp you add under src/ goes in this list.
add_library(linalg
  src/vec3.cpp
  src/mat3.cpp
  src/mat4.cpp
)

# Anything that links `linalg` can #include <linalg/...> headers.
target_include_directories(linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# --- Tests -------------------------------------------------------------------
enable_testing()
add_subdirectory(tests)

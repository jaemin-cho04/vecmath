include(FetchContent)

# Pull GoogleTest at configure time. Needs network on the first build only;
# after that it's cached. No manual install required.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

# One test executable. Add more test_*.cpp files to this list as you grow.
add_executable(unit_tests
  test_vec3.cpp
  test_mat3.cpp
  test_mat4.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    linalg          # your library, so tests can #include <linalg/vec3.hpp>
    GTest::gtest_main
)

# Register the executable with CTest so `ctest` (and CI) can run it.
include(GoogleTest)
gtest_discover_tests(unit_tests)

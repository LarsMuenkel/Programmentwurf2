# Set minimum required CMake version
cmake_minimum_required(VERSION 3.20)

# Define project name and language
project(DeveloperExercise LANGUAGES CXX)

# Set C++ standard to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Do not use GNU extensions

# add some compile options
add_compile_options(-Wall -Wextra -pedantic -O0)

# Set compiler flags (as specified)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Add path for library header files
include_directories(include)

# Definition for the path to the logo files
# This path will be relative to the project's source directory
# Assume the logos are in a folder "logos" in the project root directory
set(LOGO_FILES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/logos")
# Check if LOGO_PATH is passed as a string, add quotes if necessary
# This is important so that the path is correctly interpreted as a string in C++ code.
add_definitions("-DLOGO_PATH=\"${LOGO_FILES_PATH}\"")


# Create library "developer_lib"
# It consists of the classes Developer, JuniorDeveloper, and SeniorDeveloper
add_library(developer_lib
    src/developer.cpp
    src/juniordeveloper.cpp
    src/seniordeveloper.cpp
)

# Declare the library's header files as public
target_include_directories(developer_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Create main application "main_app"
add_executable(main_app src/main.cpp)

# Link the main application against "developer_lib"
target_link_libraries(main_app PRIVATE developer_lib)

# --- GoogleTest Integration ---
# Enable testing system
enable_testing()

# Download and configure GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main # or a specific version like release-1.14.0
)
# Make gtest and gtest_main available, but do not build by default
# unless required by a test.
FetchContent_MakeAvailable(googletest)

# Create test executable
# Assumption: The test files are located in the "test" directory
add_executable(run_tests
    test/developer_test.cpp
    # Add more test files here if available
)

# Link the test executable against developer_lib and googletest
target_link_libraries(run_tests PRIVATE developer_lib gtest_main)

# Add the tests to the CTest framework
include(GoogleTest)
gtest_discover_tests(run_tests)

# Output for information
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler Flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Logo path definition: -DLOGO_PATH=\"${LOGO_FILES_PATH}\"")
message(STATUS "GoogleTest integration enabled.")

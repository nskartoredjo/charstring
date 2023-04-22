# Set minimal cmake requirement
cmake_minimum_required(VERSION 3.10)

# Define project
project ("charstring" VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Add source to this project's static library
file(GLOB SOURCE_FILES "src/*.c")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Define public headers
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Define project.
project ("unity" VERSION 0.1 LANGUAGES C)

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)

file(GLOB SOURCE_FILES "src/*.c")

# Add as a static library.
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Set version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# Define public headers.
target_include_directories(${PROJECT_NAME} PUBLIC "include")
target_include_directories(${PROJECT_NAME} PRIVATE "src")

project ("unit_test" VERSION 0.1 LANGUAGES C)

set(UNITY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.unity")
set(DATABASE_FILE "${UNITY_DIR}/tests.csv")
set(RUNNER_FILE "${UNITY_DIR}/runner.c")
set(BUILD_COMMAND "${UNITY_DIR}/generator.py" "${CMAKE_CURRENT_SOURCE_DIR}/src" "-o${UNITY_DIR}")

file (TOUCH "${DATABASE_FILE}")
file (TOUCH "${RUNNER_FILE}")

# Add call to runner generator
execute_process(COMMAND ${BUILD_COMMAND})

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} "${RUNNER_FILE}" ${SOURCE_FILES})

# Set version property
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# Define public headers
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Add call to runner generator; notice only a touch of the files is required
# This will allow for re-configuration
add_custom_target(unity_build COMMAND ${BUILD_COMMAND} "-t")
add_dependencies(${PROJECT_NAME} unity_build)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${DATABASE_FILE})
set(ITERATOR 0)
file(READ ${DATABASE_FILE} TESTS)

foreach(TEST_NAME ${TESTS})
  add_test(${TEST_NAME} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ${ITERATOR})
  math(EXPR ITERATOR "${ITERATOR}+1")
endforeach()

# Add Unity library
target_link_libraries(${PROJECT_NAME} PUBLIC unity)

# Add charstring header
target_include_directories(${PROJECT_NAME} PUBLIC ${CHARSTRING_INCLUDE})

add_custom_target(check COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})

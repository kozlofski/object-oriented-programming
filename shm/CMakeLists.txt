cmake_minimum_required(VERSION 3.10)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 3.10)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

project(shm)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    alcohol.cpp
    cargo.cpp
    fruit.cpp
    island.cpp
    item.cpp
    map.cpp
    player.cpp
    ship.cpp
    shm_time.cpp
    store.cpp)

set(TESTS
    tests/alcohol_test.cpp
    tests/fruit_test.cpp
    tests/island_test.cpp
    tests/item_test.cpp
    tests/map_test.cpp
    tests/player_test.cpp
    tests/ship_test.cpp)

set(FLAGS -Wall -Wextra -pedantic -Wconversion -Werror)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME}-ut ${TESTS})
target_link_libraries(${PROJECT_NAME}-ut gtest_main ${PROJECT_NAME}-lib)
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}-ut)

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})

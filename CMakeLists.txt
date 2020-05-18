 


cmake_minimum_required(VERSION 3.10)

include(FindPkgConfig)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# set cxx flags
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall  -O0")


# set project name and version
project(ForestHike VERSION 1.0)


include_directories(include)

set(SOURCES
    ${SRC_DIR}/foresthike.cpp
    ${SRC_DIR}/foresthikeyaml.cpp
    ${SRC_DIR}/bridge.cpp
)



# Download and unpack yaml at configure time
configure_file(CMakeLists.yaml.in yaml-cpp-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE yamlresult
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-download )
if(yamlresult)
  message(FATAL_ERROR "CMake step for yaml failed: ${yamlresult}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE yamlresult
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-download )
if(result)
  message(FATAL_ERROR "Build step for yaml failed: ${yamlresult}")
endif()

# Add yaml directly to our build. This defines
# the yaml and targets
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-src
                 ${CMAKE_CURRENT_BINARY_DIR}/yaml-cpp-build
                 EXCLUDE_FROM_ALL)


add_executable(foresthike
    ${SRC_DIR}/main.cpp
    ${SOURCES}
)

target_link_libraries(foresthike yaml-cpp)


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
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(UT_SOURCES
    tests/main.cpp
    tests/test_foresthike.cpp
    tests/test_foresthikeyaml.cpp
    ${SOURCES}
    
)

# link against gtest or gtest_main as needed. Eg
add_executable(foresthike-ut
    ${UT_SOURCES}
)

target_link_libraries(foresthike-ut gtest_main yaml-cpp)
add_test(NAME foresthike-ut_test COMMAND foresthike-ut)










cmake_minimum_required(VERSION 3.0.0)
project(EngineThingy VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

option(BUILD_SHARED_LIBS "Wether to link the engine in a shared library" ON)
option(BUILD_TESTING "Build test programs" OFF)
option(CONSOLE_MODE "Build console version" ON)

if(NOT ${BUILD_SHARED_LIBS})
add_library(${PROJECT_NAME} STATIC ${SOURCES})
else()
add_library(${PROJECT_NAME} SHARED ${SOURCES})
endif(NOT ${BUILD_SHARED_LIBS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(${PROJECT_NAME} PUBLIC include/et/pch.h)


target_compile_definitions(${PROJECT_NAME} PRIVATE ET_BUILD=1)

if(${BUILD_SHARED_LIBS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ET_BUILD_SHARED)
endif(${BUILD_SHARED_LIBS})

if(${CONSOLE_MODE})
target_compile_definitions(${PROJECT_NAME} PUBLIC ET_CONSOLE_MODE)
endif(${CONSOLE_MODE})



add_subdirectory(deps)
target_link_libraries(${PROJECT_NAME} PUBLIC libstra spdlog)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


add_subdirectory(examples)

add_executable(meta_tests tests/meta.cpp)
add_test(NAME Misc COMMAND meta_tests)
target_link_libraries(meta_tests PRIVATE ${PROJECT_NAME})

add_executable(evt_tests tests/events.cpp)
add_test(NAME EventTests COMMAND evt_tests)
target_link_libraries(evt_tests PRIVATE ${PROJECT_NAME})

add_executable(hash_tests tests/hash.cpp)
add_test(NAME HashTests COMMAND hash_tests)
target_link_libraries(hash_tests PRIVATE ${PROJECT_NAME})
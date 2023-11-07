

add_library(glad STATIC src/glad.c)
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR})
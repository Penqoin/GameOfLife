cmake_minimum_required(VERSION 3.12)

project(
    GameOfLife
    VERSION 0.0.1
)


file(GLOB_RECURSE SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/**/*.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/glad.c"
)

file(COPY shaders DESTINATION "${CMAKE_BINARY_DIR}/CMakeFiles/GameOfLife.dir/src/engine/graphics/rendering")
file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}/")

set(HEADER_FILES
    "${CMAKE_SOURCE_DIR}/include/"
    "${CMAKE_SOURCE_DIR}/thirdparty/include/"
)

add_executable(${PROJECT_NAME} "thirdparty/glad.c" ${SOURCE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_definitions(-DGLEW_STATIC)
add_subdirectory(thirdparty/glfw EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty/glew EXCLUDE_FROM_ALL)
add_subdirectory(thirdparty/glm EXCLUDE_FROM_ALL)

add_library(glad  "thirdparty/glad.c")

target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE glfw
    PRIVATE libglew_static 
    PRIVATE glm
    PRIVATE glad
)

include_directories(${PROJECT_NAME} PUBLIC ${HEADER_FILES})

cmake_minimum_required(VERSION 2.8)

project(MovingTriangle)

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(
    ${PROJECT_NAME}
    gl3w.c
    main.cpp
    programlinker.cpp
    shader.cpp
)

target_link_libraries(${PROJECT_NAME} SDL2 GL dl)

install(
    TARGETS
        ${PROJECT_NAME}
    DESTINATION
        bin
)

cmake_minimum_required(VERSION 2.8)

project(Textured2DTriangle)

include_directories("${PROJECT_SOURCE_DIR}/include")

# set(COMPILE_FLAGS "-std=c++11 -framework OpenGL")
if(${APPLE})
    set(COMPILE_FLAGS "-std=c++11 -framework OpenGL")
else()
    set(COMPILE_FLAGS "-std=c++11 -lGL")
endif()

set(CMAKE_CXX_FLAGS ${COMPILE_FLAGS})

add_executable(
    ${PROJECT_NAME}
    main.cpp
    programlinker.cpp
    shader.cpp
    texture.cpp
    window.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_image
    glew
)

install(
    TARGETS
        ${PROJECT_NAME}
    DESTINATION
        ${PROJECT_SOURCE_DIR}
)

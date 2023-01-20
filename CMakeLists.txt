cmake_minimum_required(VERSION 3.14)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors")

include_directories("./libs/")

file(GLOB SRC_FILES
    "src/*.cpp"
    "src/Game/*.cpp"
    "src/ECS/*.cpp"
    "src/AssetManager/*.cpp"
    "src/Logger/*.cpp"
    "libs/imgui/*.cpp"
)

add_executable(Engine.app ${SRC_FILES})
target_link_libraries(Engine.app -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua)

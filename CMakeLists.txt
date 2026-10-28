
cmake_minimum_required(VERSION 3.28)

project(PathfindingVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SFML)

add_executable(PathfindingVisualizer
    src/main.cpp
)

target_link_libraries(PathfindingVisualizer
    PRIVATE SFML::Graphics
)

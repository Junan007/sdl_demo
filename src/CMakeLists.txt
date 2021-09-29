cmake_minimum_required(VERSION 3.1.0)

project(demo)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

include_directories(
    /usr/local/include
)

link_directories(
    /usr/local/lib
)

file(GLOB SRC_LIST
    ./*.cxx
    ./tinyxml/*.cpp
    )

set(LINK_LIBRARIES SDL2 SDL2main SDL2_Image z)

add_executable(demo ${SRC_LIST})
target_link_libraries(demo ${LINK_LIBRARIES})
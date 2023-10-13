cmake_minimum_required(VERSION 3.19)

project(Heveraldo_Project)

set(CMAKE_C_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(./includes)

file(GLOB DEFINITIONS_SOURCES 
    ./src/definitions/*.c
    ./src/definitions/**/**.c 
)

add_executable(${PROJECT_NAME} ./src/main.c ${DEFINITIONS_SOURCES})

# Enable compiler warnings
if (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

target_link_libraries(${PROJECT_NAME} -lncurses)

add_custom_target(run
    COMMAND ./${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
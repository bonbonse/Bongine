cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME Bongine)

add_subdirectory(BongineEditor)
add_subdirectory(BongineCore)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BongineEditor)
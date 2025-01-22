cmake_minimum_required(VERSION 3.6)
project(Chroma++)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Chroma++ Main/main.cpp CleanUp/CleanUp.cpp)

find_package(DPP REQUIRED)

target_link_libraries(Chroma++ ${DPP_LIBRARIES})

target_include_directories(Chroma++ PUBLIC ${DPP_INCLUDE_DIR})

target_link_libraries(Chroma++ PRIVATE dpp::dpp)
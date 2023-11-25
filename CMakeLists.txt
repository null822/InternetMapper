cmake_minimum_required(VERSION 3.27)
project(InternetMapper)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        InternetMapper
        src/main.cpp
        src/ColoredText.cpp
        src/ColoredText.h
)
if(WIN32)
    target_link_libraries(InternetMapper wsock32 ws2_32)
    target_link_libraries(InternetMapper iphlpapi iphlpapi)
endif()

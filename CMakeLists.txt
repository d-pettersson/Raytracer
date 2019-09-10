cmake_minimum_required(VERSION 3.14)
project(RTC)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(RTC_run ${SOURCE_FILES})

target_link_libraries(RTC_run RTC_lib)

include_directories(RTC_lib)
add_subdirectory(RTC_lib)

add_subdirectory(apps)

add_subdirectory(Google_tests)

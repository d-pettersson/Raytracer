cmake_minimum_required(VERSION 3.14)
project(RTC)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

find_package(OpenMP)

add_executable(RTC_run ${SOURCE_FILES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(RTC_run PUBLIC OpenMP::OpenMP_CXX)
endif()

#target_link_libraries(RTC_run RTC_lib)

include_directories(RTC_lib)
add_subdirectory(RTC_lib)

add_subdirectory(apps)

add_subdirectory(Google_tests)

add_executable(cannon cannon/cannon.cpp cannon/projectile.cpp cannon/environment.cpp)

include_directories(${CMAKE_SOURCE_DIR}/RTC_lib)
link_directories(${CMAKE_SOURCE_DIR}/RTC_lib)

target_link_libraries(cannon RTC_lib)
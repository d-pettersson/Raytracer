add_executable(cannon cannon/projectile.cpp cannon/environment.cpp cannon/cannonPPM.cpp)
#add_executable(clock clock/clock.cpp)

include_directories(${CMAKE_SOURCE_DIR}/RTC_lib)
link_directories(${CMAKE_SOURCE_DIR}/RTC_lib)

target_link_libraries(cannon RTC_lib)
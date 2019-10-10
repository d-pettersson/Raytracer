#add_executable(cannon cannon/projectile.cpp cannon/environment.cpp cannon/cannonPPM.cpp)
#add_executable(clock clock/clock.cpp)
#add_executable(silhouette silhouette/silhouettePhong.cpp)
#add_executable(trisphere trisphere/trisphere.cpp)
add_executable(plane plane/plane.cpp)

include_directories(${CMAKE_SOURCE_DIR}/RTC_lib)
link_directories(${CMAKE_SOURCE_DIR}/RTC_lib)

target_link_libraries(plane RTC_lib)
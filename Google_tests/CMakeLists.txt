project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run
                    TupleTest.cpp
                    MatrixTest.cpp
                    TransformTest.cpp
                    RayTest.cpp
                    CanvasTest.cpp
                    IntersectionTest.cpp
                    SphereTest.cpp
                    PlaneTest.cpp
                    WorldTest.cpp
                    CameraTest.cpp
                    MaterialTest.cpp)

# linking Google_Tests_run with RTC_lib which will be tested
target_link_libraries(Google_Tests_run RTC_lib)

target_link_libraries(Google_Tests_run gtest gtest_main)
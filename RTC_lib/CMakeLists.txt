project(RTC)

set(HEADER_FILES include/tuple.h include/canvas.h include/constants.h include/common.h include/matrix.h include/transform.h include/ray.h include/shape.h include/intersection.h include/sphere.h include/light.h include/material.h include/world.h include/camera.h include/utils.h include/plane.h include/pattern.h)

set(SOURCE_FILES src/tuple.cpp src/canvas.cpp src/matrix.cpp src/transform.cpp src/ray.cpp src/shape.cpp src/intersection.cpp src/sphere.cpp src/light.cpp src/material.cpp src/world.cpp src/camera.cpp src/plane.cpp src/pattern.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

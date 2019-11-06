project(RTC)

set(HEADER_FILES
        include/tuple.h
        include/matrix.h
        include/transform.h
        include/ray.h
        include/intersection.h
        include/material.h
        include/light.h
        include/pattern.h
        include/shape.h
        include/sphere.h
        include/plane.h
        include/world.h
        include/pattern.h
        include/camera.h
        include/canvas.h)

set(SOURCE_FILES
        src/tuple.cpp
        src/matrix.cpp
        src/transform.cpp
        src/ray.cpp
        src/intersection.cpp
        src/material.cpp
        src/light.cpp
        src/pattern.cpp
        src/shape.cpp
        src/sphere.cpp
        src/plane.cpp
        src/world.cpp
        src/pattern.cpp
        src/camera.cpp
        src/canvas.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

project(RTC)

set(HEADER_FILES tuple.h canvas.h constants.h common.h matrix.h transform.h ray.h shape.h intersection.h sphere.h light.h material.h world.h camera.h)

set(SOURCE_FILES tuple.cpp canvas.cpp matrix.cpp transform.cpp ray.cpp shape.cpp intersection.cpp sphere.cpp light.cpp material.cpp world.cpp camera.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

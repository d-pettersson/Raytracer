project(RTC)

set(HEADER_FILES tuple.h canvas.h constants.h common.h matrix.h transform.h ray.h shape.h intersection.h sphere.h)

set(SOURCE_FILES tuple.cpp canvas.cpp matrix.cpp transform.cpp ray.cpp shape.cpp intersection.cpp sphere.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

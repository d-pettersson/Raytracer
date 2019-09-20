project(RTC)

set(HEADER_FILES tuple.h canvas.h constants.h common.h matrix.h transform.h ray.cpp ray.h shape.cpp shape.h intersection.cpp intersection.h)

set(SOURCE_FILES tuple.cpp canvas.cpp matrix.cpp transform.cpp ray.cpp ray.h shape.cpp shape.h intersection.cpp intersection.h)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

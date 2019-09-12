project(RTC)

set(HEADER_FILES tuple.h canvas.h maths.h common.h matrix.cpp matrix.h)

set(SOURCE_FILES tuple.cpp canvas.cpp matrix.cpp matrix.h)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

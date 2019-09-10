project(RTC)

set(HEADER_FILES tuple.h canvas.h)

set(SOURCE_FILES tuple.cpp canvas.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

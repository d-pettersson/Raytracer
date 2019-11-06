project(RTC)

set(HEADER_FILES include/tuple.h)

set(SOURCE_FILES src/tuple.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

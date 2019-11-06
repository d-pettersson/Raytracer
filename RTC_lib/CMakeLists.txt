project(RTC)

set(HEADER_FILES include/tuple.h include/matrix.h)

set(SOURCE_FILES src/tuple.cpp src/matrix.cpp)

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

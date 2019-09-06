project(RTC)

set(HEADER_FILES
        Tuple.h
        )

set(SOURCE_FILES
        Tuple.cpp
        )

add_library(RTC_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

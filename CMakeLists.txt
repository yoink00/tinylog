project(tinylog)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -std=gnu99")

add_library(tinylog STATIC src/log.c)

add_executable(tinylog_test src/log_test.c
                            src/log.c)

install(TARGETS tinylog
	DESTINATION lib)
install(FILES src/log.h
	DESTINATION include)
install(TARGETS tinylog_test
    DESTINATION bin)

project(tinylog)

cmake_minimum_required(VERSION 2.6)
set(CMAKE_C_FLAGS "-std=gnu99 -g")

add_library(tinylog STATIC src/log.c)

install(TARGETS tinylog
	DESTINATION lib)
install(FILES src/log.h
	DESTINATION include)

set(target IBR)
file(GLOB_RECURSE HEADERS *.h *.hpp)
file(GLOB_RECURSE SOURCES *.cpp *.cc *.c)
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../ann_1.1.2/include
	${OpenCV_INCLUDE_DIRS})
add_library(IBR ${HEADERS} ${SOURCES})
target_link_libraries(${target} ANN)
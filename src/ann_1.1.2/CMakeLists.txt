set(target ANN)
file(GLOB_RECURSE HEADERS *.h *.hpp)
add_subdirectory(src)
include_directories(include)

add_library(${target} ${HEADERS} ${SOURCES})
# Minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
if(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

# Set CMake project name
PROJECT(JHEAD)

set(jheadlib_SRCS
  jhead.c
  jpgfile.c
  paths.c
  exif.c
  iptc.c
  gpsinfo.c
  makernote.c
  )
if(WIN32)
  set(jheadlib_SRCS ${jheadlib_SRCS} myglob.c)
endif(WIN32)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

add_library(jhead ${jheadlib_SRCS})

# Install
if(NOT BIN_DIR)
  set(BIN_DIR bin)
endif(NOT BIN_DIR)
if(NOT LIB_DIR)
  set(LIB_DIR lib)
endif(NOT LIB_DIR)
install(TARGETS jhead
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

# Minimum required version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
if(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
endif(COMMAND CMAKE_POLICY)

# Set CMake project name
PROJECT(OPENCTM)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/liblzma
  )

# Install
if(NOT BIN_DIR)
  set(BIN_DIR bin)
endif(NOT BIN_DIR)
if(NOT LIB_DIR)
  set(LIB_DIR lib)
endif(NOT LIB_DIR)

add_subdirectory(lib)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

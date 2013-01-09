set(3ds_SRCS
  io.c
  vector.c
  matrix.c
  quat.c
  tcb.c
  ease.c
  chunktable.h
  chunk.c
  file.c
  background.c
  atmosphere.c
  shadow.c
  viewport.c
  material.c
  mesh.c
  camera.c
  light.c
  tracks.c
  node.c
  )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  )

add_library(3ds ${3ds_SRCS})

# Install
install(TARGETS 3ds 
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

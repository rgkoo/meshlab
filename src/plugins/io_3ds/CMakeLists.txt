set(3DS_INCLUDE_DIR ../../other/lib3ds)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${3DS_INCLUDE_DIR}
  )

QT4_WRAP_CPP(moc_files meshio.h)

set(io_3ds_SRCS
  meshio.cpp
  ${moc_files}
  )

add_library(io_3ds SHARED ${io_3ds_SRCS})
target_link_libraries(io_3ds 3ds ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS io_3ds
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

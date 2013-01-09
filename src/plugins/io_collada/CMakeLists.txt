include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files io_collada.h)

set(io_collada_SRCS
  io_collada.cpp
  ../../other/vcglib/wrap/dae/xmldocumentmanaging.cpp
  ${moc_files}
  )

add_library(io_collada SHARED ${io_collada_SRCS})
target_link_libraries(io_collada ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS io_collada
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

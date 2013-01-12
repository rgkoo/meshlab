include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files io_x3d.h)

set(io_x3d_SRCS
  io_x3d.cpp
  vrml/Parser.cpp
  vrml/Scanner.cpp
  ${moc_files}
  )

add_library(io_x3d SHARED ${io_x3d_SRCS})
target_link_libraries(io_x3d ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS io_x3d
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

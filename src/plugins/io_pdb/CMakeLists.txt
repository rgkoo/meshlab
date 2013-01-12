include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files io_pdb.h)

set(io_pdb_SRCS
  io_pdb.cpp
  ../../other/vcglib/wrap/ply/plylib.cpp
  ${moc_files}
  )

add_library(io_pdb SHARED ${io_pdb_SRCS})
target_link_libraries(io_pdb ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS io_pdb
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

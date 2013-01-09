set(OPENCTM_INCLUDE_DIRS ../../other/openctm/lib)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${OPENCTM_INCLUDE_DIRS}
  )

QT4_WRAP_CPP(moc_files io_ctm.h)

set(io_ctm_SRCS
  io_ctm.cpp
  ${moc_files}
  )

add_library(io_ctm SHARED ${io_ctm_SRCS})
target_link_libraries(io_ctm openctm ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS io_ctm
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

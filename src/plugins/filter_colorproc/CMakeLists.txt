include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_colorproc.h)

set(filter_colorproc_SRCS
  filter_colorproc.cpp
  ${moc_files}
  )

add_library(filter_colorproc SHARED ${filter_colorproc_SRCS})
target_link_libraries(filter_colorproc ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_colorproc
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

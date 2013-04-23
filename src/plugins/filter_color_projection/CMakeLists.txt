include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_color_projection.h)

set(filter_color_projection_SRCS
  filter_color_projection.cpp
  ${moc_files}
  )

add_library(filter_color_projection SHARED ${filter_color_projection_SRCS})
target_link_libraries(filter_color_projection ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_color_projection
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

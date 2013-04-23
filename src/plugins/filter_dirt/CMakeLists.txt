include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_dirt.h)

set(filter_dirt_SRCS
  filter_dirt.cpp
  dirt_utils.cpp
  ${moc_files}
  )

add_library(filter_dirt SHARED ${filter_dirt_SRCS})
target_link_libraries(filter_dirt ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_dirt
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

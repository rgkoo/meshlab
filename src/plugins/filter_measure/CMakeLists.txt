include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_measure.h)

set(filter_measure_SRCS
  filter_measure.cpp
  ${moc_files}
  )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/filter_measure.xml ${MESHLAB_BINARY_DIR}/${BIN_DIR}/filter_measure.xml COPYONLY)

add_library(filter_measure SHARED ${filter_measure_SRCS})
target_link_libraries(filter_measure ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_measure
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

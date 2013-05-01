include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../io_x3d
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/structuresynth/ssynth
  )

QT4_WRAP_CPP(moc_files filter_ssynth.h)

set(filter_ssynth_SRCS
  filter_ssynth.cpp
  ${moc_files}
  )

add_library(filter_ssynth SHARED ${filter_ssynth_SRCS})
target_link_libraries(filter_ssynth ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_ssynth
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

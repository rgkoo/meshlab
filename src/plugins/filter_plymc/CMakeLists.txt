include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_plymc.h)

set(filter_plymc_SRCS
  filter_plymc.cpp
  ../../other/vcglib/wrap/ply/plylib.cpp
  ${moc_files}
  )

add_library(filter_plymc SHARED ${filter_plymc_SRCS})
target_link_libraries(filter_plymc ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_plymc
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

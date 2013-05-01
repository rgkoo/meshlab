include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files meshfilter.h)

set(filter_meshing_SRCS
  meshfilter.cpp
  quadric_simp.cpp
  quadric_tex_simp.cpp
  ${moc_files}
  )

add_library(filter_meshing SHARED ${filter_meshing_SRCS})
target_link_libraries(filter_meshing ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_meshing
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

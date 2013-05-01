include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/qhull-2003.1/src
  )

QT4_WRAP_CPP(moc_files filter_qhull.h)

set(filter_qhull_SRCS
  filter_qhull.cpp
  qhull_tools.cpp
  ../../other/qhull-2003.1/src/geom.c 
  ../../other/qhull-2003.1/src/geom2.c 
  ../../other/qhull-2003.1/src/global.c 
  ../../other/qhull-2003.1/src/io.c 
  ../../other/qhull-2003.1/src/mem.c 
  ../../other/qhull-2003.1/src/merge.c 
  ../../other/qhull-2003.1/src/poly.c 
  ../../other/qhull-2003.1/src/poly2.c 
  ../../other/qhull-2003.1/src/qconvex.c 
  ../../other/qhull-2003.1/src/qhull.c 
  ../../other/qhull-2003.1/src/qset.c 
  ../../other/qhull-2003.1/src/stat.c 
  ../../other/qhull-2003.1/src/user.c
  ${moc_files}
  )

add_library(filter_qhull SHARED ${filter_qhull_SRCS})
target_link_libraries(filter_qhull qhull ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_qhull
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

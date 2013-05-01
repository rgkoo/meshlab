include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/levmar-2.6
  )

QT4_WRAP_CPP(moc_files filter_isoparametrization.h)

set(filter_isoparametrization_SRCS
  filter_isoparametrization.cpp
  ${moc_files}
  )

add_definitions(-D_USE_OMP)

add_library(filter_isoparametrization SHARED ${filter_isoparametrization_SRCS})
target_link_libraries(filter_isoparametrization ${QT_LIBRARIES} ${OPENGL_LIBRARIES} levmar ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_isoparametrization
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

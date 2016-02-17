include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other
  )

QT4_WRAP_CPP(moc_files decorate_base.h)

set(decorate_base_SRCS
  decorate_base.cpp
  ../../other/vcglib/wrap/gui/coordinateframe.cpp
  ${moc_files}
  )

add_library(decorate_base SHARED ${decorate_base_SRCS})
target_link_libraries(decorate_base common ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS decorate_base
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

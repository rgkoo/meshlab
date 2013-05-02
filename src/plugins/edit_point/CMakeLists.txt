include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files edit_point.h)
QT4_ADD_RESOURCES(rcc_files edit_point.qrc)
set(edit_point_SRCS
  edit_point_factory.cpp 
  edit_point.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_point SHARED ${edit_point_SRCS})
target_link_libraries(edit_point ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_point
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other
  )

QT4_WRAP_CPP(moc_files edit_measure.h)
QT4_ADD_RESOURCES(rcc_files edit_measure.qrc)
set(edit_measure_SRCS
  edit_measure_factory.cpp 
  edit_measure.cpp 
  ../../other/vcglib/wrap/gui/rubberband.cpp
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_measure SHARED ${edit_measure_SRCS})
target_link_libraries(edit_measure ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_measure
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

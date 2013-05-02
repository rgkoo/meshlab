include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other
  )

QT4_WRAP_CPP(moc_files edit_manipulators.h)
QT4_ADD_RESOURCES(rcc_files edit_manipulators.qrc)
set(edit_manipulators_SRCS
  edit_manipulators_factory.cpp 
  edit_manipulators.cpp 
  ../../other/vcglib/wrap/gui/trackball.cpp
  ../../other/vcglib/wrap/gui/trackmode.cpp
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_manipulators SHARED ${edit_manipulators_SRCS})
target_link_libraries(edit_manipulators ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_manipulators
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

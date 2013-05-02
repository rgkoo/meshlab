include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../meshlab
  )

QT4_WRAP_CPP(moc_files editpickpoints.h)
QT4_WRAP_UI(uic_files pickpointsDialog.ui)
QT4_ADD_RESOURCES(rcc_files editpickpoints.qrc)
set(edit_pickpoints_SRCS
  edit_pickpoints_factory.cpp 
  editpickpoints.cpp 
  pickpointsDialog.cpp
  pickedPoints.cpp
  pickPointsTemplate.cpp
  ../../meshlab/stdpardialog.cpp
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_pickpoints SHARED ${edit_pickpoints_SRCS})
target_link_libraries(edit_pickpoints ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_pickpoints
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

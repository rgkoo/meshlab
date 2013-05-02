include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files edit_hole.h)
QT4_WRAP_UI(uic_files edit_hole.ui)
QT4_ADD_RESOURCES(rcc_files edit_hole.qrc)
set(edit_hole_SRCS
  edit_hole_factory.cpp 
  edit_hole.cpp 
  fillerDialog.cpp 
  holeListModel.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_hole SHARED ${edit_hole_SRCS})
target_link_libraries(edit_hole ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_hole
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

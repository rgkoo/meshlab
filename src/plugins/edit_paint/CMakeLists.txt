include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files edit_paint.h)
QT4_WRAP_UI(uic_files paintbox.ui)
QT4_ADD_RESOURCES(rcc_files edit_paint.qrc)
set(edit_paint_SRCS
  edit_paint_factory.cpp 
  edit_paint.cpp 
  paintbox.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_paint SHARED ${edit_paint_SRCS})
target_link_libraries(edit_paint ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_paint
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

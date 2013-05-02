include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files edit_select.h)
QT4_ADD_RESOURCES(rcc_files edit_select.qrc)
set(edit_select_SRCS
  edit_select_factory.cpp 
  edit_select.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_select SHARED ${edit_select_SRCS})
target_link_libraries(edit_select ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_select
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

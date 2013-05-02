include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/vcglib
  )

QT4_WRAP_CPP(moc_files editslice.h)
QT4_WRAP_UI(uic_files slicedialog.ui svgpro.ui)
set(editslice_SRCS
  edit_slice_factory.cpp 
  editslice.cpp 
  slicedialog.cpp
  ../../other/vcglib/wrap/gui/trackball.cpp
  ../../other/vcglib/wrap/gui/trackmode.cpp
  svgpro.cpp
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(editslice SHARED ${editslice_SRCS})
target_link_libraries(editslice ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS editslice
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

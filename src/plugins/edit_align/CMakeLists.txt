include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other
  )

QT4_WRAP_CPP(moc_files edit_align.h)
QT4_WRAP_UI(uic_files alignDialog.ui)
QT4_ADD_RESOURCES(rcc_files edit_align.qrc)
set(edit_align_SRCS
  edit_align_factory.cpp 
  point_matching_scale.cpp 
  edit_align.cpp 
  meshtree.cpp 
  alignDialog.cpp 
  AlignPairWidget.cpp 
  align/AlignPair.cpp 
  align/AlignGlobal.cpp 
  align/OccupancyGrid.cpp 
  align/align_parameter.cpp 
  ../../meshlab/stdpardialog.cpp 
  ../../other/vcglib/wrap/ply/plylib.cpp
  ../../other/vcglib/wrap/gui/trackball.cpp
  ../../other/vcglib/wrap/gui/trackmode.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_align SHARED ${edit_align_SRCS})
target_link_libraries(edit_align ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_align
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

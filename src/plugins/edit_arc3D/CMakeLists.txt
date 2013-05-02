include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other
  )

QT4_WRAP_CPP(moc_files edit_arc3D.h)
QT4_WRAP_UI(uic_files ui/v3dImportDialog.ui)
QT4_ADD_RESOURCES(rcc_files edit_arc3D.qrc)
set(edit_arc3D_SRCS
  edit_arc3D.cpp   
  edit_arc3D_factory.cpp   
  arc3D_camera.cpp 
  radial_distortion.cpp 
  scalar_image.cpp 
  v3dImportDialog.cpp  
  maskRenderWidget.cpp 
  maskImageWidget.cpp 
  fillImage.cpp 
  ../../other/vcglib/wrap/ply/plylib.cpp 
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_arc3D SHARED ${edit_arc3D_SRCS})
target_link_libraries(edit_arc3D ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} bzip2)
install(TARGETS edit_arc3D
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

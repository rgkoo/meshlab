


set(JHEAD_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/jhead)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..
  ${JHEAD_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../IBR
  )

set(meshlab_basic_SRCS
  additionalgui.cpp
  changetexturename.cpp
  customDialog.cpp
  filterScriptDialog.cpp
  filterthread.cpp
  glarea.cpp
  glarea_setting.cpp
  layerDialog.cpp
  main.cpp
  mainwindow_Init.cpp
  mainwindow_RunTime.cpp
  multiViewer_Container.cpp
  plugindialog.cpp
  savemaskexporter.cpp
  saveSnapshotDialog.cpp
  stdpardialog.cpp
  xmlgeneratorgui.cpp
  xmlstdpardialog.cpp
  ../other/vcglib/wrap/gui/trackball.cpp
  ../other/vcglib/wrap/gui/trackmode.cpp
  )

set(moc_files
  ../common/interfaces.h
  mainwindow.h
  glarea.h
  multiViewer_Container.h
  plugindialog.h
  customDialog.h
  filterScriptDialog.h
  saveSnapshotDialog.h
  savemaskexporter.h
  changetexturename.h
  layerDialog.h
  stdpardialog.h
  xmlstdpardialog.h
  additionalgui.h
  xmlgeneratorgui.h
  filterthread.h
  )
QT4_WRAP_CPP(moc_SRCS ${moc_files})

set(uic_files
  ui/layerDialog.ui
  ui/filterScriptDialog.ui
  ui/customDialog.ui
  ui/savesnapshotDialog.ui
  ui/aboutDialog.ui
  ui/renametexture.ui
  ui/savemaskexporter.ui
  ui/congratsDialog.ui 
  ui/filtergui.ui
  ui/filtercreatortab.ui
  )
QT4_WRAP_UI(uic_SRCS ${uic_files})

QT4_ADD_RESOURCES(rcc_SRCS meshlab.qrc)

set(meshlab_SRCS
  ${meshlab_basic_SRCS}
  ${uic_SRCS}
  ${moc_SRCS}
  ${rcc_SRCS}
  )
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(meshlab ${meshlab_SRCS})
target_link_libraries(meshlab common jhead opengl32.lib IBR
  ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${GLEW_LIBRARIES}
  ${OpenCV_LIBS})
install(TARGETS meshlab
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

set(target meshlab)
acmake_append_runtime_dirs(${target} ${runtime_dirs})
acmake_copy_dependencies(${target})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

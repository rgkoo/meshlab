include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/common
  )

QT4_WRAP_CPP(moc_files qualitymapper.h)
QT4_WRAP_UI(uic_files qualitymapperdialog.ui)
QT4_ADD_RESOURCES(rcc_files qualitymapper.qrc)
set(edit_quality_SRCS
  edit_quality_factory.cpp 
  qualitymapper.cpp
  qualitymapperdialog.cpp
  common/transferfunction.cpp
  common/util.cpp 
  common/meshmethods.cpp
  handle.cpp
  eqhandle.cpp 
  tfhandle.cpp
  ${moc_files}
  ${uic_files}
  ${rcc_files}
  )

add_library(edit_quality SHARED ${edit_quality_SRCS})
target_link_libraries(edit_quality ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS edit_quality
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

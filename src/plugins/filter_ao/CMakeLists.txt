include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_ao.h)
QT4_ADD_RESOURCES(rcc_files filter_ao.qrc)

set(filter_ao_SRCS
  filter_ao.cpp
  ${moc_files}
  ${rcc_files}
  )

add_library(filter_ao SHARED ${filter_ao_SRCS})
target_link_libraries(filter_ao ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_ao
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

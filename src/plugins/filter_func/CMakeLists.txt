include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/muparser_v132/include
  )

QT4_WRAP_CPP(moc_files filter_func.h)

set(filter_func_SRCS
  filter_func.cpp
  ${moc_files}
  )

add_library(filter_func SHARED ${filter_func_SRCS})
target_link_libraries(filter_func ${QT_LIBRARIES} ${OPENGL_LIBRARIES} muParser ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_func
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

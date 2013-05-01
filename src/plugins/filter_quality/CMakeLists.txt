include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../edit_quality/common
  )

QT4_WRAP_CPP(moc_files filterqualitymapper.h)

set(filter_quality_SRCS
  ../edit_quality/common/transferfunction.cpp
  ../edit_quality/common/util.cpp
  ../edit_quality/common/meshmethods.cpp
  filterqualitymapper.cpp
  ${moc_files}
  )

add_library(filter_quality SHARED ${filter_quality_SRCS})
target_link_libraries(filter_quality ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_quality
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

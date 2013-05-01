include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../filter_mls
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/ann_1.1.2/include
  )

QT4_WRAP_CPP(moc_files filter_feature_alignment.h)

set(filter_feature_alignment_SRCS
  filter_feature_alignment.cpp
  ../filter_mls/apss.cpp
  ../filter_mls/balltree.cpp
  ../filter_mls/apss.tpp
  ../filter_mls/mlssurface.tpp
  ../edit_pickpoints/pickedPoints.cpp
  ${moc_files}
  )

add_library(filter_feature_alignment SHARED ${filter_feature_alignment_SRCS})
target_link_libraries(filter_feature_alignment ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_feature_alignment
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

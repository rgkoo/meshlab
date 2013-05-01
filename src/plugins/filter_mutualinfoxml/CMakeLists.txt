include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../other/levmar-2.6
  )

QT4_WRAP_CPP(moc_files filter_mutualinfo.h)

set(filter_mutualinfoxml_SRCS
  filter_mutualinfo.cpp 
  alignset.cpp 
  levmarmethods.cpp 
  mutual.cpp 
  parameters.cpp  
  pointCorrespondence.cpp 
  solver.cpp
  ${moc_files}
  )

add_library(filter_mutualinfoxml SHARED ${filter_mutualinfoxml_SRCS})
target_link_libraries(filter_mutualinfoxml ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_mutualinfoxml
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

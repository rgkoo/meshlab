set(JHEAD_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/jhead)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${JHEAD_INCLUDE_DIR}
  )

set(common_basic_SRCS
  filterparameter.cpp
  filterscript.cpp
  GLLogStream.cpp
  interfaces.cpp
  meshlabdocumentbundler.cpp
  meshlabdocumentxml.cpp
  meshmodel.cpp
  mlapplication.cpp
  pluginmanager.cpp
  scriptinterface.cpp
  scriptsyntax.cpp
  searcher.cpp
  xmlfilterinfo.cpp
  )

set(moc_HDRS
  interfaces.h
  meshmodel.h 
  scriptinterface.h 
  scriptsyntax.h
  )
QT4_WRAP_CPP(moc_interfaces_MOC ${moc_HDRS})

set(common_SRCS
  ${common_basic_SRCS}
  ${moc_interfaces_MOC}
  )

if(BUILD_SHARED_LIBS)
  add_library(common SHARED ${common_SRCS})
  target_link_libraries(common glew ${JHEAD_LIBRARY} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  install(TARGETS common
    RUNTIME DESTINATION ${BIN_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR})
endif(BUILD_SHARED_LIBS)

if(BUILD_STATIC_LIBS)
  add_library(common-static STATIC ${common_SRCS})
  target_link_libraries(common-static glew ${JHEAD_LIBRARY} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  if(NOT MSVC)
    set_target_properties(common-static PROPERTIES OUTPUT_NAME "common")
  endif(NOT MSVC)
  install(TARGETS common-static
    RUNTIME DESTINATION ${BIN_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR})
endif(BUILD_STATIC_LIBS)


# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

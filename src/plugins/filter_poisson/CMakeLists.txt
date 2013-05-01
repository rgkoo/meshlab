include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

QT4_WRAP_CPP(moc_files filter_poisson.h)

set(filter_poisson_SRCS
  filter_poisson.cpp
  src/Factor.cpp
  src/Geometry.cpp
  src/MarchingCubes.cpp
  src/MultiGridOctest.cpp
  ${moc_files}
  )

  

add_library(filter_poisson SHARED ${filter_poisson_SRCS})
if(NOT MSVC)
  set_property(TARGET filter_poisson APPEND PROPERTY COMPILE_FLAGS -fpermissive)
endif(NOT MSVC)
target_link_libraries(filter_poisson ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_poisson
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../render_radiance_scaling
  )

QT4_WRAP_CPP(moc_files filter_sdfgpu.h)

set(filter_sdfgpu_SRCS
  filter_sdfgpu.cpp
  ../render_radiance_scaling/gpuProgram.cpp
  ../render_radiance_scaling/framebufferObject.cpp
  ../render_radiance_scaling/gpuShader.cpp
  ../render_radiance_scaling/textureParams.cpp
  ../render_radiance_scaling/textureFormat.cpp
  ${moc_files}
  )

add_library(filter_sdfgpu SHARED ${filter_sdfgpu_SRCS})
target_link_libraries(filter_sdfgpu ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS filter_sdfgpu
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

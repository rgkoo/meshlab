# Temporary settings until third party build logic is
# up and working
set(VCG_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/vcglib)
set(GLEW_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/glew/include)

# Common include directories used by most MeshLab code
include_directories(
  ${VCG_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${X11_X11_INCLUDE_PATH}
  ${MESHLAB_SOURCE_DIR}/src
  ${QT_MKSPECS_DIR}
  )

add_subdirectory(common)
add_subdirectory(meshlab)
add_subdirectory(plugins)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

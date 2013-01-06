# Temporary settings until third party build logic is
# up and working
set(VCG_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/vcglib)
set(GLEW_INCLUDE_DIR ${MESHLAB_SOURCE_DIR}/src/other/glew/include)

add_definitions(
  -D_REENTRANT 
  -DQT_WEBKIT
  -DGLEW_STATIC 
  -DQT_NO_DEBUG 
  -DQT_SCRIPT_LIB 
  -DQT_XMLPATTERNS_LIB 
  -DQT_XML_LIB 
  -DQT_OPENGL_LIB 
  -DQT_GUI_LIB 
  -DQT_CORE_LIB 
  -DQT_SHARED
)

# Common include directories used by most MeshLab code
include_directories(
  ${VCG_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${X11_X11_INCLUDE_PATH}
  )

add_subdirectory(common)
add_subdirectory(meshlab)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

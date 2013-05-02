# Plugins constitute the majority of MeshLab's functionality.
# Directories below are grouped by category.

# Plugins need to go into the 'plugins' directory in the same
# directory as the meshlab executable, so for this set of targets
# we need to override the toplevel defaults:

set(BIN_DIR_TMP ${BIN_DIR})
set(LIB_DIR_TMP ${LIB_DIR})
set(BIN_DIR ${BIN_DIR}/plugins)
set(LIB_DIR ${BIN_DIR})
if(NOT CMAKE_CONFIGURATION_TYPES)
  set(LIBOUT_TMP ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${LIB_DIR} CACHE INTERNAL "Single output directory for building all libraries.")
  set(ARCHIVEOUT_TMP ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${LIB_DIR} CACHE INTERNAL "Single output directory for building all archives.")
  set(RUNTIMEOUT_TMP ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${BIN_DIR} CACHE INTERNAL "Single output directory for building all executables.")
else(NOT CMAKE_CONFIGURATION_TYPES)
  set(CFG_ROOT ${MESHLAB_BINARY_DIR})
  foreach(CFG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    if(NOT "${CMAKE_CFG_INTDIR}" STREQUAL ".")
      set(CFG_ROOT ${MESHLAB_BINARY_DIR}/${CFG_TYPE})
    endif(NOT "${CMAKE_CFG_INTDIR}" STREQUAL ".")
    string(TOUPPER "${CFG_TYPE}" CFG_TYPE_UPPER)
    set(LIBOUT_TMP_${CFG_TYPE_UPPER} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}})
    set("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${LIB_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} libraries.")
    set(ARCHIVEOUT_TMP_${CFG_TYPE_UPPER} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}})
    set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${LIB_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} archives.")
    set(RUNTIMEOUT_TMP_${CFG_TYPE_UPPER} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}})
    set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${BIN_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} executables.")
  endforeach()
endif(NOT CMAKE_CONFIGURATION_TYPES)

# Qt Plugin definition
add_definitions(-DQT_PLUGIN)

# ********************************
# ***** Input/Output plugins *****
# ********************************

# Basic IO
add_subdirectory(io_base)
# 3DS (3D-Studio Release 3 and 4) file support
add_subdirectory(io_3ds)
# Breuckmann file format (bre)
add_subdirectory(io_bre)
# Collada
add_subdirectory(io_collada)
# Open Compressed Triangle Mesh format 
add_subdirectory(io_ctm)
# JSON
add_subdirectory(io_json)
# U3D
add_subdirectory(io_u3d)
# tri
add_subdirectory(io_tri)
# X3D
add_subdirectory(io_x3d)
# gts
add_subdirectory(io_gts)
# expe
add_subdirectory(io_expe)
# pdb
add_subdirectory(io_pdb)

# ************************
# ***** Edit plugins *****
# ************************

add_subdirectory(edit_align)
add_subdirectory(edit_arc3D)
add_subdirectory(edit_hole)
add_subdirectory(edit_manipulators)
add_subdirectory(edit_measure)
add_subdirectory(edit_paint)
add_subdirectory(edit_pickpoints)
add_subdirectory(edit_point)
add_subdirectory(edit_quality)
add_subdirectory(edit_select)
#add_subdirectory(edit_slice)
add_subdirectory(edit_texture)


# **************************
# ***** Filter plugins *****
# **************************

add_subdirectory(filter_aging)
add_subdirectory(filter_ao)
add_subdirectory(filter_autoalign)
add_subdirectory(filter_bnpts)
add_subdirectory(filter_camera)
add_subdirectory(filter_clean)
add_subdirectory(filter_colorize)
add_subdirectory(filter_colorproc)
add_subdirectory(filter_color_projection)
add_subdirectory(filter_create)
add_subdirectory(filter_csg)
add_subdirectory(filter_dirt)
#add_subdirectory(filter_feature_alignment)
add_subdirectory(filter_fractal)
add_subdirectory(filter_func)
add_subdirectory(filter_img_patch_param)
add_subdirectory(filter_isoparametrization)
add_subdirectory(filter_layer)
add_subdirectory(filter_measure)
add_subdirectory(filter_meshing)
add_subdirectory(filter_mls)
add_subdirectory(filter_mutualinfoxml)
#add_subdirectory(filter_photosynth)
add_subdirectory(filter_plymc)
add_subdirectory(filter_poisson)
add_subdirectory(filter_qhull)
add_subdirectory(filter_quality)
add_subdirectory(filter_sampling)
add_subdirectory(filter_sdf)
add_subdirectory(filter_sdfgpu)
add_subdirectory(filter_select)
add_subdirectory(filter_ssynth)
add_subdirectory(filter_texture)
add_subdirectory(filter_trioptimize)
add_subdirectory(filter_unsharp)
add_subdirectory(filter_zippering)



# Restore previous ouput directory settings

set(BIN_DIR ${BIN_DIR_TMP})
set(LIB_DIR ${LIB_DIR_TMP})
if(NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBOUT_TMP}  CACHE INTERNAL "Single output directory for building all libraries.")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVEOUT_TMP}  CACHE INTERNAL "Single output directory for building all archives.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIMEOUT_TMP}  CACHE INTERNAL "Single output directory for building all executables.")
else(NOT CMAKE_CONFIGURATION_TYPES)
  foreach(CFG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${CFG_TYPE}" CFG_TYPE_UPPER)
    set("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${LIBOUT_TMP_${CFG_TYPE_UPPER}} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} libraries.")
    set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${ARCHIVEOUT_TMP_${CFG_TYPE_UPPER}} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} archives.")
    set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${RUNTIMEOUT_TMP_${CFG_TYPE_UPPER}} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} executables.")
  endforeach()
endif(NOT CMAKE_CONFIGURATION_TYPES)


# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

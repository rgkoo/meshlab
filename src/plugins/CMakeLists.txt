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

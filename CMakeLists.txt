#                     C M A K E L I S T S . T X T
# BRL-CAD
#
# Copyright (c) 2010-2012 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following
# disclaimer in the documentation and/or other materials provided
# with the distribution.
#
# 3. The name of the author may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# *******************************************************************
# ***                 MeshLab's CMakeLists.txt                    ***
# *******************************************************************
#
# This file defines the toplevel CMake build logic for MeshLab.
# As best as is reasonably possible, proper ordering and
# separation of tests and settings should be maintained per the
# recommended standard layout.  The tests should be added to the
# labeled sections below so that they are organized as follows:
#
#     0) information on the package and toplevel CMake settings
#     1) define top level options
#     2) define detailed options
#     3) check compiler characteristics
#     4) check libraries
#     5) check headers
#     6) check types/structures
#     7) check functions
#     8) check system services
#     9) output a summary
#
# The output summary should report key information about the final
# configuration of the build.  Comprehensive information is available
# in the CMake cache file in the build directory, so just hit the
# high points in the summary.


# *******************************************************************
# ***                 Top Level Settings                          ***
# *******************************************************************
# This file contains the top level CMakeLists.txt logic for the
# BRL-CAD software package.

# Minimum required version of CMake
cmake_minimum_required(VERSION 2.8.4)
if(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
  CMAKE_POLICY(SET CMP0007 OLD)
  if(${CMAKE_VERSION} VERSION_GREATER 2.8.3)
    CMAKE_POLICY(SET CMP0017 OLD)
  endif(${CMAKE_VERSION} VERSION_GREATER 2.8.3)
endif(COMMAND CMAKE_POLICY)

# set CMake project name
project(MESHLAB)

#---------------------------------------------------------------------
# Define the current MeshLab version.

file(READ ${MESHLAB_SOURCE_DIR}/misc/conf/MAJOR MESHLAB_MAJOR_VERSION)
string(STRIP ${MESHLAB_MAJOR_VERSION} MESHLAB_MAJOR_VERSION)
file(READ ${MESHLAB_SOURCE_DIR}/misc/conf/MINOR MESHLAB_MINOR_VERSION)
string(STRIP ${MESHLAB_MINOR_VERSION} MESHLAB_MINOR_VERSION)
file(READ ${MESHLAB_SOURCE_DIR}/misc/conf/PATCH MESHLAB_PATCH_VERSION)
string(STRIP ${MESHLAB_PATCH_VERSION} MESHLAB_PATCH_VERSION)

set(MESHLAB_VERSION "${MESHLAB_MAJOR_VERSION}.${MESHLAB_MINOR_VERSION}.${MESHLAB_PATCH_VERSION}")

#---------------------------------------------------------------------
# Define relative install locations.  Don't set these if they have already
# been set by some other means (like a higher level CMakeLists.txt file
# including this one.)

# The location in which to install MeshLab executables.
if(NOT BIN_DIR)
  set(BIN_DIR bin)
endif(NOT BIN_DIR)

# The location in which to install MeshLab header files.
if(NOT INCLUDE_DIR)
  set(INCLUDE_DIR include)
endif(NOT INCLUDE_DIR)

# The location in which to install MeshLab libraries.
if(NOT LIB_DIR)
  set(LIB_DIR lib)
endif(NOT LIB_DIR)

# The location in which to install MeshLab configuration files.
if(NOT CONF_DIR)
  set(CONF_DIR etc)
endif(NOT CONF_DIR)

# The location in which to install MeshLab data files
if(NOT DATA_DIR)
  set(DATA_DIR share)
endif(NOT DATA_DIR)

# The location in which to install MeshLab Manual pages
if(NOT MAN_DIR)
  set(MAN_DIR ${DATA_DIR}/man)
endif(NOT MAN_DIR)

# The location in which to install MeshLab documentation files
if(NOT DOC_DIR)
  set(DOC_DIR ${DATA_DIR}/doc)
endif(NOT DOC_DIR)

# Make sure no absolute paths have been supplied to these variables
set(INSTALL_DIRS BIN INCLUDE LIB CONF DATA MAN DOC)
foreach(instdir ${INSTALL_DIRS})
  get_filename_component(instdir_full ${${instdir}_DIR} ABSOLUTE)
  if("${${instdir}_DIR}" STREQUAL "${instdir_full}")
    message(FATAL_ERROR "Error - absolute path supplied for ${instdir}_DIR.  This path must be relative - e.g. \"bin\" instead of \"/usr/bin\"")
    set(HAVE_INSTALL_DIR_FULL_PATH 1)
  endif("${${instdir}_DIR}" STREQUAL "${instdir_full}")
endforeach(instdir ${INSTALL_DIRS})

#---------------------------------------------------------------------
# CMake derives much of its functionality from modules, typically
# stored in one directory - let CMake know where to find them.  If we
# are a subbuild, let the parent's CMAKE_MODULE_PATH supply files before
# our own, otherwise ${MESHLAB_SOURCE_DIR}/CMake takes first priority.
set(MESHLAB_CMAKE_DIR "${MESHLAB_SOURCE_DIR}/CMake")
if(MESHLAB_IS_SUBBUILD)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${MESHLAB_CMAKE_DIR}")
else(MESHLAB_IS_SUBBUILD)
  set(CMAKE_MODULE_PATH "${MESHLAB_CMAKE_DIR};${CMAKE_MODULE_PATH}")
endif(MESHLAB_IS_SUBBUILD)


#---------------------------------------------------------------------
# include some pre-packaged macros
include(${MESHLAB_CMAKE_DIR}/MESHLAB_Options.cmake)

#---------------------------------------------------------------------
# Save the current LC_ALL, LC_MESSAGES, and LANG environment variables
# and set them to "C" so things like date output are as expected.
set(_orig_lc_all      $ENV{LC_ALL})
set(_orig_lc_messages $ENV{LC_MESSAGES})
set(_orig_lang        $ENV{LANG})
if(_orig_lc_all)
  set(ENV{LC_ALL}      C)
endif(_orig_lc_all)
if(_orig_lc_messages)
  set(ENV{LC_MESSAGES} C)
endif(_orig_lc_messages)
if(_orig_lang)
  set(ENV{LANG}        C)
endif(_orig_lang)

#---------------------------------------------------------------------
# Package creation with CMake depends on the value of umask - if permissions
# are such that temporary files are created without permissions needed for
# generated packages, the resulting packages may behave badly when installed.
# In particular, RPM packages may improperly reset permissions on core
# directories such as /usr.
macro(CHECK_UMASK umask_val status_var)
  string(REGEX REPLACE "[^x]" "" umask_x "${umask_val}")
  string(REGEX REPLACE "[^r]" "" umask_r "${umask_val}")
  string(LENGTH "${umask_r}" UMASK_HAVE_R)
  set(${status_var} 0)
  if(UMASK_HAVE_R AND "${umask_x}" STREQUAL "xxx")
    set(${status_var} 1)
  endif(UMASK_HAVE_R AND "${umask_x}" STREQUAL "xxx")
endmacro(CHECK_UMASK)
IF(NOT WIN32)
  exec_program(umask ARGS -S OUTPUT_VARIABLE umask_curr)
  string(STRIP "${umask_curr}" umask_curr)
  CHECK_UMASK("${umask_curr}" UMASK_OK)
  if (NOT UMASK_OK)
    message(" ")
    message(WARNING "umask is set to ${umask_curr} - this setting is not recommended if one of the goals of this build is to generate packages. Use 'umask 022' for improved package behavior.")
    if(SLEEP_EXEC)
      execute_process(COMMAND ${SLEEP_EXEC} 1)
    endif(SLEEP_EXEC)
  endif (NOT UMASK_OK)
ENDIF(NOT WIN32)

#---------------------------------------------------------------------
message("*** Configuring MeshLab Version ${MESHLAB_VERSION} ***" "*")

#---------------------------------------------------------------------
# We want to check /usr/local by default, so add it
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /usr/local)
set(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} /usr/local/include)

#---------------------------------------------------------------------
# The following logic is what allows binaries to run successfully in
# the build directory AND install directory.  Thanks to plplot for
# identifying the necessity of setting CMAKE_INSTALL_NAME_DIR on OSX.
# Documentation of these options is available at
# http://www.cmake.org/Wiki/CMake_RPATH_handling

# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH/INSTALL_NAME_DIR to be used when installing
if (NOT APPLE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${LIB_DIR}:\$ORIGIN/../${LIB_DIR}")
endif(NOT APPLE)
# On OSX, we need to set INSTALL_NAME_DIR instead of RPATH
# http://www.cmake.org/cmake/help/cmake-2-8-docs.html#variable:CMAKE_INSTALL_NAME_DIR
set(CMAKE_INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${LIB_DIR}")

# add the automatically determined parts of the RPATH which point to
# directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#---------------------------------------------------------------------
# Output directories - this is where built library and executable
# files will be placed after building but prior to install.  The
# necessary variables change between single and multi configuration
# build systems, so it is necessary to handle both cases on a
# conditional basis.

if(NOT CMAKE_CONFIGURATION_TYPES)
  # If we're not doing multi-configuration, just set the three main
  # variables to the correct values.
  if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${LIB_DIR} CACHE INTERNAL "Single output directory for building all libraries.")
  endif(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${LIB_DIR} CACHE INTERNAL "Single output directory for building all archives.")
  endif(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MESHLAB_BINARY_DIR}/${BIN_DIR} CACHE INTERNAL "Single output directory for building all executables.")
  endif(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
else(NOT CMAKE_CONFIGURATION_TYPES)
  # Multi-configuration is more difficult.  Not only do we need to
  # properly set the output directories, but we also need to
  # identify the "toplevel" directory for each configuration so
  # we can place files, documentation, etc. in the correct
  # relative positions.  Because files may be placed by CMake
  # without a build target to put them in their proper relative build
  # directory position using these paths, we must fully qualify them
  # without using CMAKE_CFG_INTDIR.
  #
  # We define directories that may not be quite "standard"
  # for a particular build tool - for example, native VS2010 projects use
  # another directory to denote CPU type being compiled for - but CMake only
  # supports multi-configuration setups having multiple configurations,
  # not multiple compilers.
  #
  # One additional wrinkle we must watch for here is the case where
  # a multi-configuration setup uses "." for its internal directory -
  # if that's the case, we need to just set the various config output
  # directories to the same value.
  set(CFG_ROOT ${MESHLAB_BINARY_DIR})
  foreach(CFG_TYPE ${CMAKE_CONFIGURATION_TYPES})
    if(NOT "${CMAKE_CFG_INTDIR}" STREQUAL ".")
      set(CFG_ROOT ${MESHLAB_BINARY_DIR}/${CFG_TYPE})
    endif(NOT "${CMAKE_CFG_INTDIR}" STREQUAL ".")
    string(TOUPPER "${CFG_TYPE}" CFG_TYPE_UPPER)
    if(NOT "CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
      set("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${LIB_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} libraries.")
    endif(NOT "CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
    if(NOT "CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
      set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${LIB_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} archives.")
    endif(NOT "CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
    if(NOT "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
      set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}" ${CFG_ROOT}/${BIN_DIR} CACHE INTERNAL "Single output directory for building ${CFG_TYPE} executables.")
    endif(NOT "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CFG_TYPE_UPPER}")
    if(NOT "CMAKE_BINARY_DIR_${CFG_TYPE_UPPER}")
      set("CMAKE_BINARY_DIR_${CFG_TYPE_UPPER}" ${CFG_ROOT} CACHE INTERNAL "Toplevel binary dir for ${CFG_TYPE} building.")
    endif(NOT "CMAKE_BINARY_DIR_${CFG_TYPE_UPPER}")
    if(NOT "MESHLAB_BINARY_DIR_${CFG_TYPE_UPPER}")
      set("MESHLAB_BINARY_DIR_${CFG_TYPE_UPPER}" ${CFG_ROOT} CACHE INTERNAL "Toplevel binary dir for ${CFG_TYPE} building.")
    endif(NOT "MESHLAB_BINARY_DIR_${CFG_TYPE_UPPER}")
  endforeach()
endif(NOT CMAKE_CONFIGURATION_TYPES)

# Auto-reconfiguration - by default, a CMake generated build system
# will re-run CMake if it detects that build system logic has changed.
# This is normally a good thing, but becomes problematic when using
# Visual Studio - recent versions of MSVC will individually prompt for
# a re-loading of generated solution files one at a time. Currently, the 
# only viable approach is to close Visual Studio, re-run CMake manually,
# and re-open the project in Visual Studio.
if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
  set(CMAKE_SUPPRESS_REGENERATION ON)
endif("${CMAKE_GENERATOR}" MATCHES "Visual Studio")

# *******************************************************************
# ***        Top Level Configure Options - Stage 1 of 9           ***
# *******************************************************************
# Build shared libs by default.  Mark this as advanced. Note that 
# turning this option off will not disable libraries specifically 
# added as SHARED.
if(NOT DEFINED BUILD_SHARED_LIBS)
  option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif(NOT DEFINED BUILD_SHARED_LIBS)
mark_as_advanced(BUILD_SHARED_LIBS)

# Build static libs by default unless we're debugging. Note: this
# option will not disable libraries specifically added as STATIC even
# when OFF.  For multi-configuration options the build type determination
# is made at build time, so just default to "ON".
if(NOT DEFINED BUILD_STATIC_LIBS)
  if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT "${CMAKE_BUILD_TYPE}" MATCHES "Debug")
      option(BUILD_SHARED_LIBS "Build shared libraries" ON)
    else(NOT "${CMAKE_BUILD_TYPE}" MATCHES "Debug")
      option(BUILD_SHARED_LIBS "Build shared libraries" ON)
    endif(NOT "${CMAKE_BUILD_TYPE}" MATCHES "Debug")
  else(NOT CMAKE_CONFIGURATION_TYPES)
    set(BUILD_STATIC_LIBS ON)
  endif(NOT CMAKE_CONFIGURATION_TYPES)
endif(NOT DEFINED BUILD_STATIC_LIBS)

# On Mac OS X, it is common to have third party package managers
# present for easy software installation (currently we're aware of
# Fink and MacPorts).  This can seriously complicate find_* results,
# so provide an option to specify whether or which of the third
# party setup to use.
include(${MESHLAB_CMAKE_DIR}/Fink_MacPorts.cmake)

# Global third party controls - these options enable and disable ALL
# local copies of libraries in src/other.  Forcing all local
# libraries off is not usually recommended unless attempting to
# build packages for a distribution.  If both of these options are
# on the enabling of local packages is the "senior" option and will
# force the system libs option to off.
if(MSVC)
  set(MESHLAB_BUNDLED_LIBS_DEFAULT "BUNDLED")
else(MSVC)
  set(MESHLAB_BUNDLED_LIBS_DEFAULT "AUTO")
endif(MSVC)
MESHLAB_OPTION(MESHLAB_BUNDLED_LIBS "Build bundled libraries.")

# *******************************************************************
# ***        Set up Find-Grained Options - Stage 2 of 9           ***
# *******************************************************************



# *******************************************************************
# ***      Check for Compiler Characteristics - Stage 3 of 9      ***
# *******************************************************************

# At this point, it's time to handle the external libraries - we do
# this *before* defining any global characteristics for MeshLab,
# in order to allow the sub-builds to do their own thing without
# overriding anything except what we *need* to override (which is
# already defined before this point.)
#add_subdirectory(src/other)

# MeshLab compiler checks...

# *******************************************************************
# ***            Check for Libraries - Stage 4 of 9               ***
# *******************************************************************

# While the primary purpose of this section is to identify libraries,
# some of the headers we are looking for are associated with the
# libraries checked here.  In those cases, we will handle the header
# logic here as opposed to separating the header logic from the
# find_package call.

# Check for Qt and OpenGL - no point in proceeding without those
find_package(OpenGL REQUIRED)
find_package(Qt 4.7 REQUIRED)

# Look for threads (doesn't check for headers)
# The variable CMAKE_THREAD_LIBS_INIT is the one of interest
# when writing target_link_libraries lists.
find_package(Threads)

# Check for CoreFoundation, Carbon and Cocoa on Apple
if(APPLE)
  include(CMakeFindFrameworks)
  CMAKE_FIND_FRAMEWORKS(CoreFoundation)
  if(CoreFoundation_FRAMEWORKS)
    set(CoreFoundation_LIBRARIES "-framework CoreFoundation" CACHE FILEPATH "CoreFoundation framework" FORCE)
  endif(CoreFoundation_FRAMEWORKS)
  CMAKE_FIND_FRAMEWORKS(Carbon)
  if(Carbon_FRAMEWORKS)
    set(Carbon_LIBRARIES "-framework Carbon" CACHE FILEPATH "Carbon framework" FORCE)
  endif(Carbon_FRAMEWORKS)
  CMAKE_FIND_FRAMEWORKS(Cocoa)
  if(Cocoa_FRAMEWORKS)
    set(Cocoa_LIBRARIES "-framework Cocoa" CACHE FILEPATH "Cocoa framework" FORCE)
  endif(Cocoa_FRAMEWORKS)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES CMAKE_OSX_DEPLOYMENT_TARGET CMAKE_OSX_SYSROOT)
  mark_as_advanced(CoreFoundation_LIBRARIES Carbon_LIBRARIES Cocoa_LIBRARIES)
endif(APPLE)

# *******************************************************************
# ***             Check for Headers - Stage 5 of 9                ***
# *******************************************************************

# C89 headers: assert.h, ctype.h, errno.h, float.h, limits.h, locale.h,
# math.h, setjmp.h, signal.h, stdarg.h, stddef.h, stdio.h, stdlib.h,
# string.h, time.h

# C95 headers: wchar.h, wctype.h, iso646.h

# C99 headers: complex.h, fenv.h, inttypes.h, stdbool.h, stdint.h,
# tgmath.h

# POSIX.1 headers includes C89, C95, and C99 plus the following:
# aio.h, arpa/inet.h, cpio.h, dirent.h, dlfcn.h, fcntl.h, fmtmsg.h,
# fnmatch.h, ftw.h, glob.h, grp.h, iconv.h, langinfo.h, libgen.h,
# monetary.h, mqueue.h, ndbm.h, net/if.h, netdb.h, netinet/in.h,
# netinet/tcp.h, nl_types.h, poll.h, pthread.h, pwd.h, regex.h,
# sched.h, search.h, semaphore.h, spawn.h, strings.h, stropts.h,
# sys/ipc.h, sys/mman.h, sys/msg.h, sys/resource.h, sys/select.h,
# sys/stat.h, sys/statvfs.h, sys/time.h, sys/timeb.h, sys/times.h,
# sys/types.h, sys/uio.h, sys/un.h, sys/utsname.h, sys/wait.h,
# syslog.h, tar.h, termios.h, trace.h, ucontext.h, ulimit.h, unistd.h,
# utime.h, utmpx.h, wordexp.h

# *******************************************************************
# ***          Check for System Services - Stage 8 of 9           ***
# *******************************************************************

# For Windows, we need some dlls to be redistributed with the
# installer
if(MSVC)
  # By default, do not warn when built on machines using only VS Express
  # From: http://www.cmake.org/pipermail/cmake/2011-May/044166.html
  if(NOT DEFINED CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_NO_WARNINGS ON)
  endif()
  include(InstallRequiredSystemLibraries)
endif(MSVC)

# We've done the toplevel configure steps, now add the subdirectories
#add_subdirectory(src)
#add_subdirectory(include)
#add_subdirectory(misc)

# *******************************************************************
# ***              Summarize Results - Stage 9 of 9               ***
# *******************************************************************

# Now that everything is configured, print a summary of the build
# settings.
if(NOT MESHLAB_DISABLE_SUMMARY)
  #include(${MESHLAB_CMAKE_DIR}/MESHLAB_Summary.cmake)
endif(NOT MESHLAB_DISABLE_SUMMARY)


# CPack is used to produce tgz files, RPMS, etc.  If SUBBUILD is enabled this
# becomes the responsibility of the parent project.
if(NOT MESHLAB_IS_SUBBUILD)
  option(MESHLAB_VERSIONED_RPM_NAME "Incorporate MeshLab version into RPM package name" OFF)
  mark_as_advanced(MESHLAB_VERSIONED_RPM_NAME)
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MeshLab - a powerful cross-platform open source solid modeling system")
  set(CPACK_PACKAGE_VENDOR "MeshLab Development Team")
  set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README)
  set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
  set(CPACK_PACKAGE_VERSION_MAJOR ${MESHLAB_MAJOR_VERSION})
  set(CPACK_PACKAGE_VERSION_MINOR ${MESHLAB_MINOR_VERSION})
  set(CPACK_PACKAGE_VERSION_PATCH ${MESHLAB_PATCH_VERSION})
  if(MESHLAB_VERSIONED_RPM_NAME)
    set(CPACK_RPM_PACKAGE_NAME "MeshLab_${MESHLAB_VERSION}")
  endif(MESHLAB_VERSIONED_RPM_NAME)

  if(UNIX)
    set(CPACK_STRIP_FILES TRUE)
  endif(UNIX)

  if(UNIX)
    set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
  endif(UNIX)

  if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR TGZ TBZ2)

    find_program(RPMBUILD_EXEC rpmbuild)
    mark_as_advanced(RPMBUILD_EXEC)
    if(RPMBUILD_EXEC)
      # Since RPM packages present a particular problem with bad umask
      # settings and RPM package building is enabled, raise the issue again
      # with a longer wait time.
      if (NOT UMASK_OK)
	message(" ")
	message(WARNING "umask is set to ${umask_curr} and RPM package building is enabled - this is not a 'standard' umask setting for MeshLab RPM packages.  Double check that these umask permissions will have the desired results when installed - RPM packages can impact permissions on system directories such as /usr\nIf the umask settings need to be changed, it is recommended that the build directory be cleared and cmake re-run after the umask setting has been changed.")
	if(SLEEP_EXEC)
	  execute_process(COMMAND ${SLEEP_EXEC} 5)
	endif(SLEEP_EXEC)
      endif (NOT UMASK_OK)

      set(CPACK_GENERATOR ${CPACK_GENERATOR} RPM)
      set(CPACK_RPM_PACKAGE_LICENSE "LGPL 2.1")
      set(CPACK_RPM_PACKAGE_GROUP "Applications/Engineering")
      #set(CPACK_RPM_PACKAGE_NAME "brlcad_${MESHLAB_MAJOR_VERSION}_${MESHLAB_MINOR_VERSION}_${MESHLAB_PATCH_VERSION}")
      #if(EXISTS /etc/redhat-release)
      #	file(READ /etc/redhat-release REDHAT_RELEASE)
      #	string(REGEX MATCH "[0-9]+" REDHAT_VERSION ${REDHAT_RELEASE})
      #	string(REGEX MATCH "Enterprise Linux" LINUX_DIST_TYPE ${REDHAT_RELEASE})
      #	if(LINUX_DIST_TYPE)
      #		set(LINUX_DIST_TYPE "el")
      #	else(LINUX_DIST_TYPE)
      #		set(LINUX_DIST_TYPE "rh")
      #	endif(LINUX_DIST_TYPE)
      #	set(CPACK_RPM_PACKAGE_RELEASE 1.${LINUX_DIST_TYPE}${REDHAT_VERSION})
      #else(EXISTS /etc/redhat-release)
      #	#set(CPACK_RPM_PACKAGE_RELEASE 2)
      #endif(EXISTS /etc/redhat-release)
    endif(RPMBUILD_EXEC)
    set(CPACK_RPM_PACKAGE_ARCHITECTURE "${CMAKE_SYSTEM_PROCESSOR}")
    if(NOT CPACK_RPM_PACKAGE_RELEASE)
      set(CPACK_RPM_PACKAGE_RELEASE 1)
    endif(NOT CPACK_RPM_PACKAGE_RELEASE)
    set(CPACK_PACKAGE_FILE_NAME "MeshLab_${MESHLAB_VERSION}_${CMAKE_SYSTEM_PROCESSOR}_${CMAKE_SYSTEM_NAME}_${CPACK_RPM_PACKAGE_RELEASE}")
  else(UNIX AND NOT APPLE)
    set(CPACK_PACKAGE_FILE_NAME "MeshLab_${MESHLAB_VERSION}_${CMAKE_SYSTEM_PROCESSOR}")
  endif(UNIX AND NOT APPLE)

  if(WIN32)
    set(CPACK_GENERATOR NSIS)
    set(CPACK_NSIS_PACKAGE_NAME "MeshLab")
    set(CPACK_SOURCE_DIR ${CMAKE_SOURCE_DIR})
    set(CPACK_DATA_DIR "${DATA_DIR}")
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backslashes.
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/misc/nsis\\\\meshlab.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/misc/nsis\\\\uninstall.ico")
    set(CPACK_NSIS_DISPLAY_NAME "MeshLab")
    set(CPACK_NSIS_MODIFY_PATH ON)
  endif(WIN32)
  if(CMAKE_CL_64)
    set(CPACK_PACKAGE_FILE_NAME "MeshLab_${MESHLAB_VERSION}_x64")
  endif(CMAKE_CL_64)

  set(CPACK_SOURCE_GENERATOR TGZ TBZ2 ZIP)
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "MeshLab-${MESHLAB_VERSION}")
  set(CPACK_SOURCE_IGNORE_FILES "\\\\.git/")

  configure_file("${MESHLAB_CMAKE_DIR}/MESHLAB_CPackOptions.cmake.in" "${CMAKE_BINARY_DIR}/MESHLAB_CPackOptions.cmake" @ONLY)
  set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_BINARY_DIR}/MESHLAB_CPackOptions.cmake")

  include(CPack)
endif(NOT MESHLAB_IS_SUBBUILD)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

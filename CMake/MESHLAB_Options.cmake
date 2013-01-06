# Copyright (c) 2011-2012 United States Government as represented by
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
###

macro(MESHLAB_OPTION opt comment)
  if(NOT DEFINED ${${opt}})
    set(${opt} AUTO)
  endif(NOT DEFINED ${${opt}})
  # Put ${opt} into the cache, so set_property has something
  # to work on
  set(${opt} "${${opt}}" CACHE STRING "${comment}" FORCE)
  set_property(CACHE ${opt} PROPERTY STRINGS AUTO BUNDLED SYSTEM)
  string(TOUPPER "${${opt}}" ${opt}_UPPER)
  set(${opt} "${${opt}_UPPER}" CACHE STRING "${comment}" FORCE)
  if(${${opt}} MATCHES "ON")
    set(${opt} "BUNDLED" CACHE STRING "${comment}" FORCE)
  endif(${${opt}} MATCHES "ON")
  if(${${opt}} MATCHES "OFF")
    set(${opt} "SYSTEM" CACHE STRING "${comment}" FORCE)
  endif(${${opt}} MATCHES "OFF")
  if(NOT "${${opt}}" MATCHES "AUTO" AND NOT "${${opt}}" MATCHES "BUNDLED" AND NOT "${${opt}}" MATCHES "SYSTEM")
    message(WARNING "Unknown value ${opt} supplied for ${opt} - defaulting to AUTO")
    message(WARNING "Valid options are AUTO, BUNDLED and SYSTEM")
    set(${opt} "AUTO" CACHE STRING "Build   bundled libraries." FORCE)
  endif(NOT "${${opt}}" MATCHES "AUTO" AND NOT "${${opt}}" MATCHES "BUNDLED" AND NOT "${${opt}}" MATCHES "SYSTEM")
endmacro(MESHLAB_OPTION)

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

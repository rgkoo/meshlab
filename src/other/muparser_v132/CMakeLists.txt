include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(muParser_SRCS 
  src/muParser.cpp
  src/muParserBase.cpp
  src/muParserBytecode.cpp
  src/muParserCallback.cpp
  src/muParserComplex.cpp
  src/muParserDLL.cpp
  src/muParserError.cpp
  src/muParserInt.cpp
  src/muParserTest.cpp
  src/muParserTokenReader.cpp
  )

add_library(muParser ${muParser_SRCS})

# Install
if(NOT BIN_DIR)
  set(BIN_DIR bin)
endif(NOT BIN_DIR)
if(NOT LIB_DIR)
  set(LIB_DIR lib)
endif(NOT LIB_DIR)
install(TARGETS muParser 
  RUNTIME DESTINATION ${BIN_DIR}
  LIBRARY DESTINATION ${LIB_DIR}
  ARCHIVE DESTINATION ${LIB_DIR})

# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8

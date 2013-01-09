add_definitions(-DOPENCTM_BUILD)
add_definitions(-DLZMA_PREFIX_CTM)

set(ctm_SRCS
	openctm.c
	stream.c
	compressRAW.c
	compressMG1.c
	compressMG2.c
	liblzma/Alloc.c
	liblzma/LzFind.c
	liblzma/LzmaDec.c
	liblzma/LzmaEnc.c
	liblzma/LzmaLib.c
)

add_library(openctm ${ctm_SRCS})
install(TARGETS openctm
	RUNTIME DESTINATION ${BIN_DIR}
	LIBRARY DESTINATION ${LIB_DIR}
	ARCHIVE DESTINATION ${LIB_DIR})


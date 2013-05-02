set(bzip2_SRCS 
	#bzip2.c 
	#bzip2recover.c 
	#dlltest.c 
	#mk251.c 
	#spewG.c 
	#unzcrash.c
	blocksort.c 
	bzlib.c 
	compress.c 
	crctable.c 
	decompress.c 
	huffman.c 
	randtable.c 
	)

add_library(bzip2 ${bzip2_SRCS})
# Install
if(NOT BIN_DIR)
	set(BIN_DIR bin)
endif(NOT BIN_DIR)
if(NOT LIB_DIR)
	set(LIB_DIR lib)
endif(NOT LIB_DIR)
install(TARGETS bzip2
	RUNTIME DESTINATION ${BIN_DIR}
	LIBRARY DESTINATION ${LIB_DIR}
	ARCHIVE DESTINATION ${LIB_DIR})

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
project(SSYNTH)


find_package(OpenGL REQUIRED)
set(Qt4_FIND_COMPONENTS QtCore QtGui QtWebKit QtScript QtXmlPatterns QtXml QtOpenGL QtNetwork)
find_package(Qt 4.7 REQUIRED)
include(${QT_USE_FILE})


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/ssynth
	${X11_X11_INCLUDE_PATH}
	${QT_MKSPECS_DIR}
	)

#ssynth/StructureSynth/Model
#ssynth/StructureSynth/Parser
#ssynth/SyntopiaCore/Exceptions
#ssynth/SyntopiaCore/GLEngine
#ssynth/SyntopiaCore/GLEngine/Raytracer
#ssynth/SyntopiaCore/Logging
#ssynth/SyntopiaCore/Math
#ssynth/ThirdPartyCode/MersenneTwister
#ssynth/StructureSynth/Model/Rendering


set(ssynth_SOURCES 
	ssynth/StructureSynth/Model/Action.cpp 
	ssynth/StructureSynth/Model/AmbiguousRule.cpp 
	ssynth/StructureSynth/Model/Builder.cpp 
	ssynth/StructureSynth/Model/ColorPool.cpp 
	ssynth/StructureSynth/Model/CustomRule.cpp 
	ssynth/StructureSynth/Model/ExecutionStack.cpp 
	ssynth/StructureSynth/Model/PrimitiveClass.cpp 
	ssynth/StructureSynth/Model/PrimitiveRule.cpp 
	ssynth/StructureSynth/Model/RandomStreams.cpp 
	ssynth/StructureSynth/Model/Rule.cpp 
	ssynth/StructureSynth/Model/RuleRef.cpp 
	ssynth/StructureSynth/Model/RuleSet.cpp 
	ssynth/StructureSynth/Model/State.cpp 
	ssynth/StructureSynth/Model/Transformation.cpp 
	ssynth/StructureSynth/Model/TransformationLoop.cpp 
	ssynth/StructureSynth/Parser/EisenParser.cpp 
	ssynth/StructureSynth/Parser/Preprocessor.cpp 
	ssynth/StructureSynth/Parser/Tokenizer.cpp 
	ssynth/SyntopiaCore/GLEngine/Box.cpp 
	ssynth/SyntopiaCore/GLEngine/Dot.cpp 
	#ssynth/SyntopiaCore/GLEngine/EngineWidget.cpp 
	ssynth/SyntopiaCore/GLEngine/Grid.cpp 
	ssynth/SyntopiaCore/GLEngine/Line.cpp 
	ssynth/SyntopiaCore/GLEngine/Mesh.cpp 
	ssynth/SyntopiaCore/GLEngine/Object3D.cpp 
	ssynth/SyntopiaCore/GLEngine/Raytracer/AtomicCounter.cpp 
	#ssynth/SyntopiaCore/GLEngine/Raytracer/RayTracer.cpp 
	ssynth/SyntopiaCore/GLEngine/Raytracer/RenderThread.cpp 
	ssynth/SyntopiaCore/GLEngine/Raytracer/Sampler.cpp 
	ssynth/SyntopiaCore/GLEngine/Raytracer/VoxelStepper.cpp 
	ssynth/SyntopiaCore/GLEngine/RaytraceTriangle.cpp 
	#ssynth/SyntopiaCore/GLEngine/Sphere.cpp 
	ssynth/SyntopiaCore/GLEngine/Triangle.cpp 
	ssynth/SyntopiaCore/Logging/ListWidgetLogger.cpp 
	ssynth/SyntopiaCore/Logging/Logging.cpp 
	ssynth/SyntopiaCore/Math/Matrix4.cpp 
	ssynth/SyntopiaCore/Math/Random.cpp 
	ssynth/SyntopiaCore/Math/Vector3.cpp 
	ssynth/SyntopiaCore/Misc/ColorUtils.cpp 
	ssynth/SyntopiaCore/Misc/MiniParser.cpp 
	ssynth/SyntopiaCore/Misc/Persistence.cpp 
	ssynth/SyntopiaCore/Misc/Version.cpp 
	#ssynth/StructureSynth/Model/Rendering/OpenGLRenderer.cpp 
	ssynth/StructureSynth/Model/Rendering/Renderer.cpp 
	ssynth/StructureSynth/Model/Rendering/TemplateRenderer.cpp
	)

add_library(ssynth ${ssynth_SOURCES})
target_link_libraries(ssynth ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS ssynth 
	RUNTIME DESTINATION ${BIN_DIR}
	LIBRARY DESTINATION ${LIB_DIR}
	ARCHIVE DESTINATION ${LIB_DIR})


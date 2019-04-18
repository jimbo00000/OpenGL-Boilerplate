CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( OpenGLBoilerplate )

IF( MINGW )
    MESSAGE("MINGW...")
    SET( LIBS_HOME "C:/lib" CACHE STRING "Location of support libraries Glut, Glew and others"  )
    SET( GLFW_ROOT "${LIBS_HOME}/glfw-3.2.1.bin.WIN64" CACHE STRING "GLFW root" )
    INCLUDE_DIRECTORIES( "${GLFW_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLFW_ROOT}/lib-mingw-w64" )
    SET( PLATFORM_LIBS opengl32 glfw3 )
ELSEIF( WIN32 )
    SET( LIBS_HOME "C:/lib" CACHE STRING "Location of support libraries Glut, Glew and others"  )

    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        MESSAGE("64-bit build")
        SET( GLFW_ROOT "${LIBS_HOME}/glfw-3.2.1.bin.WIN64" CACHE STRING "GLFW root" )
    else ()
        MESSAGE("32-bit build")
        SET( GLFW_ROOT "${LIBS_HOME}/glfw-3.2.1.bin.WIN32" CACHE STRING "GLFW root" )
    endif ()
    SET( FRAMEWORK_LIBS glfw3 )

    INCLUDE_DIRECTORIES( "${GLFW_ROOT}/include" )
    LINK_DIRECTORIES( "${GLFW_ROOT}/lib-vc2015" )
    SET( PLATFORM_LIBS opengl32 ${FRAMEWORK_LIBS} )
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT OpenGLBoilerplate)
ELSEIF( APPLE )
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(IOKIT_LIBRARY IOKit)
    FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      IOKIT_LIBRARY
                      OpenGL_LIBRARY)
    
    INCLUDE_DIRECTORIES( "/opt/local/include" )
    LINK_DIRECTORIES   ( "/opt/local/lib" )

    SET( FRAMEWORK_LIBS glfw3 )

    SET(PLATFORM_LIBS ${FRAMEWORK_LIBS} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY} -lGLEW)
ELSEIF( UNIX )
    FIND_PACKAGE( OpenGL REQUIRED )
    INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIRS} )
    LINK_DIRECTORIES   ( "/usr/local/lib" )
    SET( FRAMEWORK_LIBS glfw3 )

    SET( PLATFORM_LIBS ${FRAMEWORK_LIBS} ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} X11 -pthread -ldl)
ENDIF()

ADD_EXECUTABLE( ${PROJECT_NAME} src/glfw3_boilerplate.cpp )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${PLATFORM_LIBS} )

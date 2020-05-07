# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CM_definitions.cmake 2549 2018-06-08 18:48:31Z stephane $


IF ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	SET ( GeoLite2PP_BIT_SIZE 64 )
ELSEIF ( CMAKE_SIZEOF_VOID_P EQUAL 4 )
	SET ( GeoLite2PP_BIT_SIZE 32 )
ELSE ()
	MESSAGE ( FATAL_ERROR "CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P}" )
ENDIF ()

ADD_DEFINITIONS ( "-std=gnu++11" )
ADD_DEFINITIONS ( "-fPIC" )
ADD_DEFINITIONS ( "-Wall" )
ADD_DEFINITIONS ( "-Wextra" )
ADD_DEFINITIONS ( "-Werror" )
ADD_DEFINITIONS ( "-Wno-unused-parameter" )
#ADD_DEFINITIONS ( "-fdiagnostics-color" )
#ADD_DEFINITIONS ( "-fmessage-length=120" )
ADD_DEFINITIONS ( "-fdiagnostics-show-location=every-line" )


STRING (FIND "${CMAKE_CXX_COMPILER}" "arm-linux-gnueabihf-g++" pos)
IF ( ${pos} EQUAL -1 )
	SET ( GeoLite2PP_CROSS_COMPILE_FOR_ARM7 FALSE )
ELSE ()
	MESSAGE ( "Cross compiling for ARM7" )
	SET ( GeoLite2PP_CROSS_COMPILE_FOR_ARM7 TRUE )
ENDIF ()


STRING (FIND "${CMAKE_SYSTEM_PROCESSOR}" "arm" pos)
IF ( ${pos} EQUAL -1 )
	SET ( GeoLite2PP_COMPILE_FOR_ARM7 FALSE )
ELSE ()
	MESSAGE ( "Compiling for ARM" )
	SET ( GeoLite2PP_COMPILE_FOR_ARM7 TRUE )
ENDIF ()


IF ( ${GeoLite2PP_CROSS_COMPILE_FOR_ARM7} OR ${GeoLite2PP_COMPILE_FOR_ARM7} )
	SET ( GeoLite2PP_SYSTEM_NAME "armhf-${GeoLite2PP_BIT_SIZE}" )
ELSE ()
	IF ( GeoLite2PP_BIT_SIZE EQUAL 32 )
		SET ( GeoLite2PP_SYSTEM_NAME "x86-${GeoLite2PP_BIT_SIZE}" )
	ELSE ()
		SET ( GeoLite2PP_SYSTEM_NAME "amd-${GeoLite2PP_BIT_SIZE}" )
	ENDIF ()
ENDIF ()

MESSAGE ( "Building with ${CMAKE_C_COMPILER}" )
MESSAGE ( "Building with ${CMAKE_CXX_COMPILER}" )
MESSAGE ( "Building for ${GeoLite2PP_BIT_SIZE}-bit" )
MESSAGE ( "Building for ${GeoLite2PP_SYSTEM_NAME}" )

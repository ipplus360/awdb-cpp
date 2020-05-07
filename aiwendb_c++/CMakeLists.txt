# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CMakeLists.txt 2549 2018-06-08 18:48:31Z stephane $

PROJECT ( GeoLite2PP C CXX )

CMAKE_MINIMUM_REQUIRED ( VERSION 2.8 )
IF ( NOT CMAKE_BUILD_TYPE )
	SET ( CMAKE_BUILD_TYPE Release )
ENDIF ()

INCLUDE ( CM_version.cmake		)	# get the version number
INCLUDE ( CM_definitions.cmake	)	# compiler definitions
INCLUDE ( CM_dependencies.cmake	)	# find all required dependencies
INCLUDE ( CM_source.cmake		)	# source code that needs to be built
INCLUDE ( CM_package.cmake		)	# create .deb or .rpm packages

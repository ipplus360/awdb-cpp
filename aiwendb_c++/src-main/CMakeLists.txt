# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CMakeLists.txt 2549 2018-06-08 18:48:31Z stephane $

FILE ( GLOB MAIN_SOURCE *.cpp )
LIST ( SORT MAIN_SOURCE )

ADD_EXECUTABLE			(			geolite2pp ${MAIN_SOURCE}						)
TARGET_LINK_LIBRARIES	(			geolite2pp ${CMAKE_THREAD_LIBS_INIT} geolite2++	)
INSTALL					( TARGETS	geolite2pp DESTINATION bin						)

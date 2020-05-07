# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CM_source.cmake 2549 2018-06-08 18:48:31Z stephane $


INCLUDE_DIRECTORIES ( BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src-lib )
INCLUDE_DIRECTORIES ( BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src-main )

ADD_SUBDIRECTORY ( src-lib	)
ADD_SUBDIRECTORY ( src-main	)
ADD_SUBDIRECTORY ( doc		)

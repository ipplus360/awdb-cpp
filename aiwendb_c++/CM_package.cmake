# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CM_package.cmake 2549 2018-06-08 18:48:31Z stephane $


SET ( CPACK_PACKAGE_VENDOR				"Stephane Charette"				)
SET ( CPACK_PACKAGE_CONTACT				"stephanecharette@gmail.com"	)
SET ( CPACK_PACKAGE_DESCRIPTION_SUMMARY	"GeoLite2 C++ Interface"		)
SET ( CPACK_PACKAGE_DESCRIPTION			"GeoLite2 C++ Interface"		)
SET ( CPACK_PACKAGE_NAME				"geolite2++"					)
SET ( CPACK_PACKAGE_VERSION				${GeoLite2PP_VERSION}			)
SET ( CPACK_PACKAGE_VERSION_MAJOR		${GeoLite2PP_VER_MAJOR}			)
SET ( CPACK_PACKAGE_VERSION_MINOR		${GeoLite2PP_VER_MINOR}			)
SET ( CPACK_PACKAGE_VERSION_PATCH		${GeoLite2PP_VER_PATCH}			)
SET ( CPACK_SYSTEM_NAME					${GeoLite2PP_SYSTEM_NAME}		)

INCLUDE ( CM_package_ubuntu.cmake )
INCLUDE ( CM_package_redhat.cmake )

SET ( CPACK_GENERATOR "DEB" )

SET ( CPACK_SOURCE_IGNORE_FILES ".svn" ".kdev4" "build" "generate_and_upload.sh" "GeoLite2-City.awdb" )
SET ( CPACK_SOURCE_GENERATOR "TGZ" )

INCLUDE( CPack )

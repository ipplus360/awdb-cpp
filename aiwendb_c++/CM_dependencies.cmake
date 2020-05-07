# GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
# $Id: CM_dependencies.cmake 2549 2018-06-08 18:48:31Z stephane $


FIND_PACKAGE ( Threads		REQUIRED		)
FIND_LIBRARY ( aiwendb	NAMES aiwendb	)

SET ( GeoLite2PP_EXTERNAL_LIBS "${aiwendb}" )

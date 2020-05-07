/* GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
 * $Id: main.cpp 2549 2018-06-08 18:48:31Z stephane $
 */


#include <iostream>
#include <GeoLite2PP.hpp>


int main( int argc, char *argv[] )
{
	GeoLite2PP::DB db( "IP_city_2020W16_single_WGS84.awdb" );

	std::cout << "AWDB version:   " << db.get_lib_version_awdb()		<< std::endl;
	std::cout << "GeoLite2PP ver: " << db.get_lib_version_geolite2pp()	<< std::endl;

	if (argc < 2)
	{
		std::cout	<< "Database metadata: "	<< std::endl
					<< db.get_metadata()		<< std::endl;
	}

	
	//print all
	std::string json = db.lookup( "1.192.90.183" );
	std::cout << json << std::endl;
	
	//print single field

	std::string     accuracy = db.get_field( "1.192.90.183","", GeoLite2PP::VCStr {"accuracy"} );	
	
	std::cout << "精度:"<<accuracy << std::endl;
	
		std::string      continent= db.get_field( "1.192.90.183","", GeoLite2PP::VCStr {"continent"} );	
	
	std::cout << "洲:"<<continent << std::endl;
	
	
		std::string     country = db.get_field( "1.192.90.183","", GeoLite2PP::VCStr {"country"} );	
	
	std::cout << "国家:"<<country << std::endl;
	return 0;
}

/* GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
 * $Id: main.cpp 2549 2018-06-08 18:48:31Z stephane $
 */


#include <iostream>
#include <GeoLite2PP.hpp>


int main( int argc, char *argv[] )
{
	GeoLite2PP::DB db( "/home/ant/awdb-c/awdb.awdb" );

	std::cout << "AWDB version:   " << db.get_lib_version_awdb()		<< std::endl;
	std::cout << "GeoLite2PP ver: " << db.get_lib_version_geolite2pp()	<< std::endl;

	if (argc < 2)
	{
		std::cout	<< "Database metadata: "	<< std::endl
					<< db.get_metadata()		<< std::endl;
	}

	
	//print all
	std::string json = db.lookup( "166.111.4.100" );
	std::cout << json << std::endl;
	
	//print single field

	std::string      continent= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"continent"} );	
	
	std::cout << "洲:"<<continent << std::endl;

	std::string      areacode= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"areacode"} );	
	
	std::cout << "国家编码:"<<areacode << std::endl;

	std::string      country= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"country"} );	
	
	std::cout << "国家:"<<country << std::endl;

	std::string      zipcode= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"zipcode"} );	
	
	std::cout << "邮编:"<<zipcode << std::endl;

	std::string      timezone= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"timezone"} );	
	
	std::cout << "时区:"<<timezone << std::endl;

	std::string     accuracy = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"accuracy"} );	
	
	std::cout << "定位精度:"<<accuracy << std::endl;

	std::string      source= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"source"} );	
	
	std::cout << "定位方式:"<<source << std::endl;

	
	 //地区可能有多个 这里取第一个省
	
	std::string     prov = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"province"} );	
	
	std::cout << "省:"<<prov << std::endl;
	
	//地区可能有多个 这里取第一个市
	
	std::string     city = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"city"} );	
	
	std::cout << "城市:"<<city<< std::endl;

	std::string     district = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"district"} );	
	
	std::cout << "区县:"<<district<< std::endl;

	std::string     lonwgs = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"lngwgs"} );	
	
	std::cout << "经度:"<<lonwgs << std::endl;
	
	std::string     latwgs = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"latwgs"} );	
	
	std::cout << "纬度:"<<latwgs << std::endl;

	std::string     radius = db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"radius"} );	
	
	std::cout << "半径:"<<radius << std::endl;

	
	//其他字段 同样这个格式 
	
	std::string      isp= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"isp"} );	
	
	std::cout << "运营商:"<<isp << std::endl;

	std::string      asnumber= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"asnumber"} );	
	
	std::cout << "AS编号:"<<asnumber << std::endl;

	std::string      owner= db.get_field( "166.111.4.100","", GeoLite2PP::VCStr {"owner"} );	
	
	std::cout << "拥有者:"<<owner << std::endl;

	return 0;
}

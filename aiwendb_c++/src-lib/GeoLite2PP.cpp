
#include <GeoLite2PP.hpp>
#include <GeoLite2PP_error_category.hpp>
#include <GeoLite2PP_version.hpp>


GeoLite2PP::DB::~DB( void )
{
	AWDB_close( &awdb );

	return;
}


GeoLite2PP::DB::DB( const std::string &database_filename )
{
	const int status = AWDB_open( database_filename.c_str(), AWDB_MODE_MMAP, &awdb );

	if (status != AWDB_SUCCESS)
	{
		const ErrorCategory	&	cat( get_error_category() );
		const std::error_code	ec( status, cat );
		const std::string		msg = "Failed to open the AWDB database \"" + database_filename + "\"";

		/** @throw std::system_error if the database file cannot be opened.
		 * @see @ref GeoLite2PP::AWDBStatus
		 * @see @ref GeoLite2PP::ErrorCategory
		 */
		throw std::system_error( ec, msg );
	}

	return;
}


std::string GeoLite2PP::DB::get_lib_version_awdb( void ) const
{
	return AWDB_lib_version();
}


std::string GeoLite2PP::DB::get_lib_version_geolite2pp( void ) const
{
	return GEOLITE2PP_VERSION;
}


AWDB_metadata_s GeoLite2PP::DB::get_metadata_raw( void )
{
	return awdb.metadata;
}


std::string GeoLite2PP::DB::get_metadata( void )
{
	AWDB_entry_data_list_s *node = nullptr;
	const int status = AWDB_get_metadata_as_entry_data_list( &awdb, &node );
	if (status)
	{
		/// @throw std::system_error if the lookup resulted in a AWDB error
		const ErrorCategory	&	cat( get_error_category() );
		const std::error_code	ec( status, cat );
		const std::string		msg = "Failed to lookup up meta data";
		throw std::system_error( ec, msg );
	}

	return to_json( node );
}


AWDB_lookup_result_s GeoLite2PP::DB::lookup_raw( const std::string &ip_address )
{
	int gai_error	= 0;	// get_address_info() error
	int awdb_error	= 0;

	AWDB_lookup_result_s result = AWDB_lookup_string( &awdb, ip_address.c_str(), &gai_error, &awdb_error );

	if (gai_error)
	{
		/// @throw std::invalid_argument if the address is invalid
		throw std::invalid_argument( gai_strerror(gai_error) );
	}
	if (awdb_error)
	{
		/// @throw std::system_error if the lookup resulted in a AWDB error
		const ErrorCategory	&	cat( get_error_category() );
		const std::error_code	ec( awdb_error, cat );
		const std::string		msg = "Database error while looking up address \"" + ip_address + "\"";
		throw std::system_error( ec, msg );
	}
	if (result.found_entry == false)
	{
		/// @throw std::length_error if an entry was not found in the database
		throw std::length_error( "Failed to find address \"" + ip_address + "\"" );
	}

	return result;
}


void GeoLite2PP::DB::create_json_from_entry( std::stringstream &ss, size_t depth, uint32_t data_size, AWDB_entry_data_list_s * &node, const bool in_array )
{
	// we're normally dealing with pairs (keys + values) so double the data_size
	if ( ! in_array )
	{
		data_size *= 2;
	}

	if (data_size == 0)
	{
		// nothing left to do
		return;
	}

	if (node == nullptr)
	{
		/// @throw std::runtime_error if the data_size is non-zero but the next pointer is null
		throw std::runtime_error( "invalid entry pointer or data size value" );
	}

	while (node && data_size)
	{
		const bool is_value		= in_array || (data_size % 2);
		const bool is_key		= in_array || (! is_value);

		data_size --;

		if (node->entry_data.has_data == false)
		{
			/// @throw std::runtime_error if a node contains no data
			throw std::runtime_error( "invalid entry has no data" );
		}

		if (is_key)
		{
			ss << std::string( depth * 4, ' ' );
		}

		switch (node->entry_data.type)
		{
			
			case AWDB_DATA_TYPE_BYTES:
			case AWDB_DATA_TYPE_UTF8_STRING:
			{
				ss << "\"" << std::string(node->entry_data.utf8_string, node->entry_data.data_size) << "\"";
				if ( ! is_value )
				{
					ss << " : ";
				}
				break;
			}
			case AWDB_DATA_TYPE_MAP:
			{
				ss << std::endl << std::string( depth * 4, ' ' ) << "{" << std::endl;
				create_json_from_entry( ss, depth + 1, node->entry_data.data_size, node->next );
				ss << std::endl << std::string( depth * 4, ' ' ) << "}";
				break;
			}
			case AWDB_DATA_TYPE_ARRAY:
			{
				ss << std::endl << std::string( depth * 4, ' ' ) << "[" << std::endl;
				create_json_from_entry( ss, depth + 1, node->entry_data.data_size, node->next, true );
				ss << std::endl << std::string( depth * 4, ' ' ) << "]";
				break;
			}
			case AWDB_DATA_TYPE_DOUBLE:		ss << node->entry_data.double_value;					break;
			case AWDB_DATA_TYPE_UINT16:		ss << node->entry_data.uint16;							break;
			case AWDB_DATA_TYPE_UINT32:		ss << node->entry_data.uint32;							break;
			case AWDB_DATA_TYPE_INT32:		ss << node->entry_data.uint32;							break;
			case AWDB_DATA_TYPE_UINT64:		ss << node->entry_data.uint64;							break;
			case AWDB_DATA_TYPE_FLOAT:		ss << node->entry_data.float_value;						break;
			case AWDB_DATA_TYPE_BOOLEAN:	ss << (node->entry_data.boolean ? "true" : "false");	break;
			case AWDB_DATA_TYPE_EXTENDED:
			case AWDB_DATA_TYPE_POINTER:
			case AWDB_DATA_TYPE_CONTAINER:
			case AWDB_DATA_TYPE_END_MARKER:
			{
				/// @throw std::runtime_error if the data type is invalid
				throw std::runtime_error( "entry data type #" + std::to_string(node->entry_data.type) + " indicates a damaged or corrupt database" );
			}
			
			case AWDB_DATA_TYPE_UINT128:
			default:
			{
				/// @throw std::runtime_error if the data type is not supported (raw bytes or uint128)
				throw std::runtime_error( "unhandled data type #" + std::to_string(node->entry_data.type) + " cannot be processed" );
			}
		}

		if (is_value && data_size)
		{
			ss << "," << std::endl;
		}

		node = node->next;
	}

	return;
}


std::string GeoLite2PP::DB::lookup( const std::string &ip_address )
{
	AWDB_lookup_result_s result = lookup_raw( ip_address );

	AWDB_entry_data_list_s *node = nullptr;
	const int status = AWDB_get_entry_data_list( &result.entry, &node );
	if (status)
	{
		/// @throw std::system_error if the lookup resulted in a AWDB error
		const ErrorCategory	&	cat( get_error_category() );
		const std::error_code	ec( status, cat );
		const std::string		msg = "Failed to lookup up address \"" + ip_address + "\"";
		throw std::system_error( ec, msg );
	}

	return to_json( node );
}


std::string GeoLite2PP::DB::to_json( AWDB_entry_data_list_s *node )
{
	#if 0
	// for debug purposes:
	AWDB_dump_entry_data_list( stdout, node, 0 );
	#endif

	std::stringstream ss;

	try
	{
		const size_t			depth	= 0;
		const size_t			nodes	= 1;
		AWDB_entry_data_list_s *next	= node;
		create_json_from_entry( ss, depth, nodes, next );
	}
	catch (...)
	{
		AWDB_free_entry_data_list( node );
		throw;
	}

	AWDB_free_entry_data_list( node );

	return ss.str();
}


GeoLite2PP::MStr GeoLite2PP::DB::get_all_fields( const std::string &ip_address, const std::string &language )
{
	AWDB_lookup_result_s result = lookup_raw( ip_address );

	MStr m;
	add_to_map( m, &result, "continent"				, language	, VCStr{ "continent"			, "names"			} );
	add_to_map( m, &result, "registered_country"	, language	, VCStr{ "registered_country"	, "names"			} );
	add_to_map( m, &result, "country"				, language	, VCStr{ "country"				, "names"			} );
	add_to_map( m, &result, "city"					, language	, VCStr{ "city"					, "names"			} );
	add_to_map( m, &result, "subdivision"			, language	, VCStr{ "subdivisions", "0"	, "names"			} );
	add_to_map( m, &result, "subdivision_iso_code"	, ""		, VCStr{ "subdivisions", "0"	, "iso_code"		} );
	add_to_map( m, &result, "country_iso_code"		, ""		, VCStr{ "country"				, "iso_code"		} );
	add_to_map( m, &result, "accuracy_radius"		, ""		, VCStr{ "location"				, "accuracy_radius"	} );
	add_to_map( m, &result, "latitude"				, ""		, VCStr{ "location"				, "latitude"		} );
	add_to_map( m, &result, "longitude"				, ""		, VCStr{ "location"				, "longitude"		} );
	add_to_map( m, &result, "time_zone"				, ""		, VCStr{ "location"				, "time_zone"		} );
	add_to_map( m, &result, "postal_code"			, ""		, VCStr{ "postal"				, "code"			} );

	m[ "query_ip_address"	] = ip_address;
	m[ "query_language"		] = language;

	return m;
}


std::string GeoLite2PP::DB::get_field( const std::string &ip_address, const std::string &language, const VCStr &v )
{
	AWDB_lookup_result_s lookup = lookup_raw( ip_address );

	return get_field( &lookup, language, v );
}


std::string GeoLite2PP::DB::get_field( AWDB_lookup_result_s *lookup, const std::string &language, const VCStr &v )
{
	std::string str;

	if (lookup)
	{
		AWDB_entry_s *entry = &lookup->entry;

		VCStr lookup_path = v;
		if (language.empty() == false)
		{
			lookup_path.push_back( language.c_str() );
		}
		if (lookup_path.size() == 0 || *lookup_path.rbegin() != nullptr)
		{
			// last vector entry when calling AWDB_aget_value() must be a NULL
			lookup_path.push_back( nullptr );
		}

		AWDB_entry_data_s result;
		AWDB_aget_value( entry, &result, lookup_path.data() );

		if (result.has_data)
		{
			switch (result.type)
			{
				case AWDB_DATA_TYPE_BYTES:
				case AWDB_DATA_TYPE_UTF8_STRING:	str = std::string( result.utf8_string, result.data_size	);	break;
				case AWDB_DATA_TYPE_DOUBLE:			str = std::to_string( result.double_value				);	break;
				case AWDB_DATA_TYPE_UINT16:			str = std::to_string( result.uint16						);	break;
				case AWDB_DATA_TYPE_UINT32:			str = std::to_string( result.uint32						);	break;
				case AWDB_DATA_TYPE_INT32:			str = std::to_string( result.uint32						);	break;
				case AWDB_DATA_TYPE_UINT64:			str = std::to_string( result.uint64						);	break;
				case AWDB_DATA_TYPE_FLOAT:			str = std::to_string( result.float_value				);	break;
				case AWDB_DATA_TYPE_BOOLEAN:		str = (result.boolean ? "true" : "false"				);	break;
				default:	/* data type not supported for this "quick" retrieval */							break;
			}
		}
		else if (language == "en")
		{
			// ignore the language and grab the first one available
			str = get_field( lookup, "0", v );
		}
		else if (language != "0" && language != "en")
		{
			// ignore the language and grab the English name
			str = get_field( lookup, "0", v );
		}
	}

	return str;
}


void GeoLite2PP::DB::add_to_map( GeoLite2PP::MStr &m, AWDB_lookup_result_s *node, const std::string &name, const std::string &language, const VCStr &v )
{
	const std::string result = get_field( node, language, v );

	if (result.empty() == false)
	{
		// try and find a decent key name to use to store this value into the map
		std::string key = name;
		if (key.empty() || m.count(key) != 0)
		{
			// try a different name
			key = *v.begin();
		}
		if (key.empty() || m.count(key) != 0)
		{
			// try a different name
			key = *v.rbegin();
		}
		m[ key ] = result;
	}

	return;
}

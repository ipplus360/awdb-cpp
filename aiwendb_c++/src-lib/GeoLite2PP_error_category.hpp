/* GeoLite2++ (C) 2016-2018 Stephane Charette <stephanecharette@gmail.com>
 * $Id: GeoLite2PP_error_category.hpp 2549 2018-06-08 18:48:31Z stephane $
 */

#pragma once

#include <string>
#include <system_error>
#include <aiwendb.h>


namespace GeoLite2PP
{
	/// Errors defined in aiwendb.h, converted to C++ enums.
	enum class AWDBStatus
	{
		success						= AWDB_SUCCESS								,	///<= 0
		file_open					= AWDB_FILE_OPEN_ERROR						,	///<= 1
		corrupt_search_tree			= AWDB_CORRUPT_SEARCH_TREE_ERROR			,	///<= 2
		invalid_metadata			= AWDB_INVALID_METADATA_ERROR				,	///<= 3
		io							= AWDB_IO_ERROR								,	///<= 4
		out_of_memory				= AWDB_OUT_OF_MEMORY_ERROR					,	///<= 5
		unknown_db_format			= AWDB_UNKNOWN_DATABASE_FORMAT_ERROR		,	///<= 6
		invalid_data				= AWDB_INVALID_DATA_ERROR					,	///<= 7
		invalid_lookup_path			= AWDB_INVALID_LOOKUP_PATH_ERROR			,	///<= 8
		lookup_path_does_not_match	= AWDB_LOOKUP_PATH_DOES_NOT_MATCH_DATA_ERROR,	///<= 9
		invalid_node_number			= AWDB_INVALID_NODE_NUMBER_ERROR			,	///<= 10
		ipv6_lookup_in_ipv4_db		= AWDB_IPV6_LOOKUP_IN_IPV4_DATABASE_ERROR		///<= 11
	};


	/** Error class used to return libaiwendb error codes and messages when C++ exceptions are thrown.
	 * @see @p AWDB_strerror()
	 */
	class ErrorCategory : public std::error_category
	{
		public:

			/// Returns a unique name.
			virtual const char *name( void ) const noexcept;

			/// Convert a MaxMindDB error/status code into a readable text string message.
			virtual std::string message( int code ) const;
	};

	/// All error category objects should actually be references to the exact same object, which is provided by this function.
	const ErrorCategory &get_error_category( void ) noexcept;

	/// Associate an error value with the category.
	std::error_code make_error_code( AWDBStatus s );

	/// Associate an error_condition with the category.
	std::error_condition make_error_condition( AWDBStatus s );
}


namespace std
{
	/// Make sure that AWDBStatus enums can be converted to error codes.
	template <>
	struct is_error_code_enum<GeoLite2PP::AWDBStatus> : public true_type {};
}

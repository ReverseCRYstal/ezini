#pragma once
#include <string>
#include <stdexcept>
#include <map>
#include <fstream>

namespace ezini
{
	class parse_error :private std::invalid_argument
	{
	public:
		using base = std::invalid_argument;
		parse_error(const std::string& msg);
		parse_error(const char* const msg);

	};

	using section_data = std::map<std::string, std::string>;
	using inifile_data = std::map<std::string, section_data>;

	std::pair<std::string, std::string> parse(const std::string& line);
	
	inifile_data get_file_data(const std::string& file_name);

	std::filebuf& filebuf_to_next_line(std::filebuf& file_buf, char delimiter = '\n');
	std::ifstream& ifstream_to_next_line(std::ifstream& stream, char delimiter = '\n');
}
#include "ezini_utility.h"

namespace ezini
{
	inline parse_error::parse_error(const std::string& msg) :base(msg) {}
	inline parse_error::parse_error(const char* const msg) : base(msg) {}

	std::pair<std::string, std::string> parse(const std::string& line)
	{
		if (line.empty())
			throw parse_error("'line' can't be empty");
		bool in_dquat = false, in_squat = false;

		bool at_left = true;

		std::string right, left, * ref;
		ref = &left;

		for (auto& c : line) {
			switch (c) {
			case ' ':
				if (in_dquat || in_squat)
					ref->push_back(c);
				break;
			case '\'':
				if (at_left)
					throw parse_error("Failed to parse the argument 'line',a unexpect chararcter appeared.");
				if (in_dquat) {
					ref->push_back('\'');
					break;
				}
				if (in_squat)
					return std::make_pair(left, right);
				else
					in_squat = true;
			case '"':
				if (at_left)
					throw parse_error("Failed to parse the argument 'line',a unexpect chararcter appeared.");
				if (in_squat) {
					ref->push_back('"');
					break;
				}
				if (in_dquat)
					return std::make_pair(left, right);
				else
					in_dquat = true;
			case '=':

				if (in_squat || in_dquat) {
					ref->push_back('=');
					break;
				}
				at_left = false;
				ref = &right;
				break;
			default:
				ref->push_back(c);
				break;
			}
		}

		if (in_dquat || in_squat)
			throw parse_error("Quotation marks are not closed.");

		return std::make_pair(left, right);
	}

	inifile_data get_file_data(const std::string& file_name)
	{
		std::ifstream reader(file_name);
		if (reader.is_open())
			throw std::runtime_error("Failed to open file");

		int c;

		std::string line, section_name;
		section_data section;
		inifile_data data;
		
		while (reader.good()) {
			c = reader.get();
			switch (c)
			{
			case ';':
			case '#':
				ifstream_to_next_line(reader);
				continue;
			case '[':
				if (!section.empty()) {
					data.insert(std::make_pair(section_name, section));
					section.clear();
				}
				std::getline(reader, section_name, ']');
				continue;
			default:
				std::getline(reader, line);
				section.insert(parse(char(c) + line));
				break;
			}

		}
		return data;
	}

	std::filebuf& filebuf_to_next_line(std::filebuf& file_buf, char delimiter)
	{
		int c = file_buf.snextc();
		while (c != EOF && c != '\n')
			c = file_buf.snextc();
		return file_buf;
	}

	std::ifstream& ifstream_to_next_line(std::ifstream& stream, char delimiter) {
		filebuf_to_next_line(*stream.rdbuf());
		return stream;
	}
}
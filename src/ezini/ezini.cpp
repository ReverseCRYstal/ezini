#include "ezini.h"

namespace ezini {

	void ini::Load(std::string&& file_name) {
		std::ifstream reader(file_name);
		if (!reader.is_open())
			throw std::runtime_error("Failed to open file");

		Load(std::move(reader));
	}

	void ini::Load(const std::string& file_name) {
		Load(std::move(const_cast<std::string&>(file_name)));
	}

	void ini::Load(const char* const file_name) {
		std::ifstream reader(file_name);
		if (!reader.is_open())
			throw std::runtime_error("Failed to open file");

		Load(std::move(reader));
	}

	void ini::Load(const char* const file_name, const char* const section_name) {
		std::ifstream ifs(file_name);
		if (!ifs.is_open())
			throw std::runtime_error("Failed to open the file");

		Load(std::move(ifs), section_name);
	}


	const inifile_data& ini::data() const noexcept {
		return _data;
	}

	void ini::Load(std::ifstream&& ifstr) {
		int c;

		std::string line, section_name;
		section_data section;

		while ((c = ifstr.get()) != EOF) {
			switch (c)
			{
			case ' ':
			case '\n':
				break;
			case ';':
			case '#':
				ifstream_to_next_line(ifstr);
				continue;
			case '[':
				if (!section.empty()) {
					_data.insert(std::make_pair(section_name, section));
					section.clear();
				}
				std::getline(ifstr, section_name, ']');
				continue;
			default:
				std::getline(ifstr, line);
				section.insert(parse(char(c) + line));
				break;
			}
		}
	}

	void ini::Load(std::ifstream&& ifstr, const std::string& section_name) {
		int c;

		std::string line, cur_section_name;
		section_data section;

		while ((c = ifstr.get()) != EOF) {
			switch (c)
			{
			case ' ':
			case '\n':
				break;
			case ';':
			case '#':
				ifstream_to_next_line(ifstr);
				continue;
			case '[':
				if (!section.empty()) {
					_data.insert(std::make_pair(cur_section_name, section));
					section.clear();
				}
				std::getline(ifstr, cur_section_name, ']');
				continue;
			default:
				std::getline(ifstr, line);
				section.insert(parse(char(c) + line));
				break;
			}

			if (!section.empty()) {
				_data.insert(std::make_pair(cur_section_name, section));
				section.clear();
			}
		}
	}
}
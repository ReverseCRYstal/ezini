#pragma once
#include "ezini_utility.h"

#include <map>

namespace ezini {
	class ini
	{
	public:
		void Load(const std::string& file_name);
		void Load(const char* const file_name);
		void Load(const char* const file_name,const char* const section_name);
		void Load(std::string&& file_name);

		const inifile_data& data() const noexcept;
	private:
		void Load(std::ifstream&& ifstr);
		void Load(std::ifstream&& ifstr, const std::string& section_name);

		inifile_data _data;
	};

}
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>


namespace splited_string
{
	class SplitedString
	{
	public:
		explicit SplitedString(const std::string& string, const char& delimiter);
		std::vector<std::string> ToVector();
		std::string At(const size_t index);

	private:
		std::vector<std::string> _splited_string;
	};

}
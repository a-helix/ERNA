#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "splited_string.h"

namespace splited_string
{
	class SplitedString
	{
	public:
		explicit SplitedString(const std::string& string, const char& delimiter);
		virtual ~SplitedString();
		std::vector<std::string> ToVector();

	private:
		std::vector<std::string> _splited_string;
	};

}
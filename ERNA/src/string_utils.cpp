#include "string_utils.hpp"

namespace splited_string
{
	SplitedString::SplitedString(const std::string& input_data, const char& delimiter)
	{

		std::stringstream string_stream(input_data);
		std::string temp;

		while(std::getline(string_stream, temp, delimiter))
		{
			_splited_string.push_back(temp);
		}

	}

	std::string SplitedString::At(const size_t index)
	{
		return _splited_string.at(index);
	}

	std::vector<std::string> SplitedString::ToVector() { return _splited_string; }
}

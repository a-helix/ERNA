#pragma once

#include <filesystem>
#include "bioutilities.hpp"
#include "input.hpp"

namespace app
{
	class App
	{
		public:
			explicit App(int32_t argc, char* argv[]);
			void Run();

		private:
			inline void WrongArgumentFormat(const int32_t &iteration);
			inline char ProcessDelimiter(const char& delimiter);

			bioutilities::GeneticCodeFactory factory;
			int32_t _argc;
			char** _argv;
			std::filesystem::path input_file;
			std::filesystem::path output_file;
			char input_delimiter;
			char output_delimiter;

			std::unordered_map<char, char> comand_line_delimiters =
			{
				{'n', '\n'},
				{'t', '\t'},
				{'s', ' '}
			};
	};
}



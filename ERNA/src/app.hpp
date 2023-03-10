#pragma once

#include <filesystem>
#include "bioutilities.hpp"
#include "iofile.hpp"

namespace app
{
	class App
	{
		public:
			explicit App(int32_t argc, char* argv[]);
			void Run();

		private:
			void IdentifyDelimeters();
			void IdentifyIOFiles();

			inline void WrongArgumentFormat(int32_t iteration);
			inline char ProcessDelimiter(char delimiter);

			bioutilities::GeneticCodeFactory factory;
			int32_t _argc;
			char** _argv;
			std::filesystem::path _input_file;
			std::filesystem::path _output_file;
			char _input_delimiter;
			char _output_delimiter;

			std::unordered_map<char, char> comand_line_delimiters =
			{
				{'n', '\n'},
				{'t', '\t'},
				{'s', ' '}
			};

			std::vector<std::string> analysys_id =
			{
				//RNA tools
				"uorfs",		//calculate all upstream ORFs
				"stemloops",	//identify all stemloops with minimal specified size (-a) default 4 nt
				"translate",	//translate main ORF
				"rt"			//preforme reverse translation
				"comprna"		//find complementary sequences inside file with minimal specified size (-a) default 4 nt
			};
	};
}

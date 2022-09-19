#pragma once

#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include "bioutilities.h"
#include "db_data.h"

namespace input
{
	class InputFile
	{
		public:
			explicit InputFile(const std::filesystem::path& path_to_file);
			virtual ~InputFile();
			virtual void Save(const std::filesystem::path& path_to_file, const char& delimiter) = 0;

		protected:
			std::vector<std::string> _file_data;
	};

	class WormBaseRnaSequencesFile : InputFile
	{
		public:
			explicit WormBaseRnaSequencesFile(const std::filesystem::path& path_to_file, const char& delimiter, bioutilities::GeneticCodeFactory& factory);
			virtual ~WormBaseRnaSequencesFile();

			void Save(const std::filesystem::path& path_to_file, const char& delimiter) override;

		protected:
			std::vector<db_data::WormBaseComplementaryDna> _delimited_rna_data;
	};

	
}
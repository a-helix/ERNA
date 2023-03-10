#pragma once

#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include "bioutilities.hpp"
#include "db_data.hpp"

namespace iofile
{
	class InputFile
	{
		public:
			explicit InputFile(const std::filesystem::path& path_to_file);
			virtual void Save(const std::filesystem::path& path_to_file, const char& delimiter) = 0;

		protected:
			std::vector<std::string> _file_data;
	};

	class WormBaseRnaSequencesFile : InputFile
	{
		public:
			explicit WormBaseRnaSequencesFile(const std::filesystem::path& path_to_file, const char& delimiter, bioutilities::GeneticCodeFactory& factory);

			void Save(const std::filesystem::path& path_to_file, const char& delimiter) override;

		protected:
			std::vector<db_data::WormBaseRnaComplementaryDna> _delimited_rna_data;
	};

	
}
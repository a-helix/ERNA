#include "input.hpp"

namespace input
{
	InputFile::InputFile(const std::filesystem::path& path_to_file)
	{
		std::ifstream input_file_stream(path_to_file);

		if (!input_file_stream.is_open()) 
		{
			throw std::invalid_argument(std::format("ERROR! File couldn't be opened : {}\n", path_to_file.string()));
		}


		for (std::string line; std::getline(input_file_stream, line);)
		{
			_file_data.push_back(line);
		}

		if (_file_data.empty())
		{
			throw std::invalid_argument(std::format("ERROR! File is empty : {}\n", path_to_file.string()));
		}
	}

	WormBaseRnaSequencesFile::WormBaseRnaSequencesFile(const std::filesystem::path& path_to_file, const char& delimiter, bioutilities::GeneticCodeFactory& factory)
		: InputFile(path_to_file)
	{
		for (auto& x : _file_data)
		{
			_delimited_rna_data.push_back(db_data::WormBaseRnaComplementaryDna(x, delimiter, factory));
		}
	}

	void WormBaseRnaSequencesFile::Save(const std::filesystem::path& path_to_file, const char& delimiter)
	{
		std::ofstream file_stream;
		file_stream.open(path_to_file);
		int32_t distance; // Distance between ORF start and uORF stop codone

		if (!file_stream.is_open())
		{
			throw std::invalid_argument(std::format("ERROR! File couldn't be opened : {}\n", path_to_file.string()));
		}

		//Coulumn names
		file_stream << "WormBase ID" << delimiter;
		file_stream << "Gene" << delimiter;
		file_stream << "Transcript" << delimiter;
		file_stream << "5` UTR size" << delimiter;
		file_stream << "ORF size" << delimiter;
		file_stream << "3` UTR size" << delimiter;
		file_stream << "true uUTR (size, relative position)" << delimiter;
		file_stream << "true uUTR count" << delimiter;
		file_stream << "pseudo-uUTR (size, relative position)" << delimiter;
		file_stream << "pseudo-uUTR count" << delimiter;
		file_stream << "\n";

		for (auto& x : _delimited_rna_data)
		{

			file_stream << x.DatabaseID() << delimiter;
			file_stream << x.Gene() << delimiter;
			file_stream << x.TranscriptID() << delimiter;
			file_stream << x.FivePrimeUTR().length() << delimiter;
			file_stream << x.MainORF().SizeInNucleotides() << delimiter;
			file_stream << x.RawRnaDataString().length() - x.MainORF().End() << delimiter;

			//true uORFs
			size_t UORFs_count = x.SumOfuORFs();
			for (auto& y : x.uORFs())
			{
				distance = static_cast<int32_t>(x.MainORF().Start()) - static_cast<int32_t>(y.End());
				//distance -= 1;
				if (distance >= 0)
				{
					file_stream << std::format("({}, {})", static_cast<int32_t>(y.SizeInNucleotides()), distance) << " ";
				}
				else
				{
					UORFs_count -= 1;
				}
			}
			file_stream << delimiter << UORFs_count << delimiter;

			//pseudo-uORFs
			UORFs_count = x.SumOfuORFs();
			for (auto& y : x.uORFs())
			{
				distance = static_cast<int32_t>(x.MainORF().Start()) - static_cast<int32_t>(y.End());
				if (distance < 0)
				{
					file_stream << std::format("({}, {})", static_cast<int32_t>(y.SizeInNucleotides()), distance) << " ";
				}
				else
				{
					UORFs_count -= 1;
				}
			}
			file_stream << delimiter << UORFs_count << delimiter;
			file_stream << "\n";
		}
		file_stream.close();
	}
}

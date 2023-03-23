#include "app.hpp"




namespace app
{
	App::App(int32_t argc, char* argv[])
	{
		_argc = argc;
		_argv = argv;
		_config = Config();
	}

	bool App::_CorrectArgumentFormat(size_t iteration)
	{
		if (iteration + 1 <= _argc)
			return true;
		return false;
	}

	void App::_IdentifyDelimeters()
	{
		bool input_delimiter_found = false;
		bool output_delimiter_found = false;

		std::string console_argument;
		char delimiter;

		for (size_t i = 1; i < _argc; ++i)
		{
			console_argument = _argv[i];
			if (console_argument == "-id")
			{
				if (_CorrectArgumentFormat(i))
				{
					delimiter = *_argv[i + 1];
					(_comand_line_delimiters.find(delimiter) == _comand_line_delimiters.end())
						? _config.input_delimiter = delimiter
						: _config.input_delimiter = _comand_line_delimiters.at(delimiter);
				}
				else
				{
					throw std::invalid_argument("ERROR! Inappropriate argument format. No value provided for tag -id.\n");
				}
				input_delimiter_found = true;
			}

			if (_argv[i] == "-od")
			{
				if (_CorrectArgumentFormat(i))
				{
					delimiter = *_argv[i + 1];
					(_comand_line_delimiters.find(delimiter) == _comand_line_delimiters.end())
						? _config.output_delimiter = delimiter
						: _config.output_delimiter = _comand_line_delimiters.at(delimiter);
				}
				else
					throw std::invalid_argument("ERROR! Inappropriate argument format. No value provided for tag -od.\n");

				output_delimiter_found = true;
			}
		}

		if (!input_delimiter_found)
			_config.input_delimiter = ',';
		if (!output_delimiter_found)
			_config.output_delimiter = ',';
	}

	void App::_IdentifyIOFiles()
	{
		std::string console_argument;
		std::filesystem::path input_file;
		std::filesystem::path output_file;


		for (size_t i = 1; i < _argc; ++i)
		{
			console_argument = _argv[i];
			if (console_argument == "-if"
				&& _CorrectArgumentFormat(i))
			{
				
				input_file = std::format(R"({})", _argv[i + 1]);
				if (!std::filesystem::exists(input_file))
					throw std::invalid_argument("ERROR! Inappropriate argument format. File from -if tag does not exhist.\n");
				else
					_config.input_file = input_file;
			}

			if (console_argument == "-of"
				&& _CorrectArgumentFormat(i))
			{
				output_file = std::format(R"({})", _argv[i + 1]);
				if (!std::filesystem::exists(output_file.parent_path()))
					throw std::invalid_argument("ERROR! Inappropriate argument format. Folder from -of tag does not exhist.\n");
				else
					_config.output_file = output_file;
			}
		}
	}

	void App::_IdentifyKeySequenceIndexes()
	{
		bool key_found = false;
		bool sequence_found = false;

		std::string console_argument;

		for (uint32_t i = 1; i < _argc; ++i)
		{
			if (_argv[i] == "-k")
			{
				if (_CorrectArgumentFormat(i) 
					&& *_argv[i + 1] != 0)
					_config.key_column = *_argv[i + 1] - 1; //-1 id requiered since enumaration in array starts from 0, while people count columns in input csv from 1
				else
					throw std::invalid_argument("ERROR! Inappropriate argument format. No value provided for tag -k.\n");

				key_found = true;
			}

			if (_argv[i] == "-s")
			{
				if (_CorrectArgumentFormat(i) 
					&& *_argv[i + 1] != 0)
					_config.sequence_column = *_argv[i + 1] - 1; //-1 id requiered since enumaration in array starts from 0, while people count columns in input csv from 1
				else
					throw std::invalid_argument("ERROR! Inappropriate argument format. No value provided for tag -s.\n");

				sequence_found = true;
			}
		}

		if (!key_found)
			_config.key_column = 0;
		if (!sequence_found)
			_config.sequence_column = 1;
	}

	void App::_IdentifyAdditionalArguments()
	{
		for (size_t i = 1; i < _argc; ++i)
		{
			if (_argv[i] == "-ap")
			{
				if (_CorrectArgumentFormat(i))
					_config.additional_argument = *_argv[i + 1]; //-1 id requiered since enumaration in array starts from 0, while people count columns in input csv from 1
				else
					throw std::invalid_argument("ERROR! Inappropriate argument format. No value provided for tag -ap.\n");
			}
		}
	}

	void App::_IdentifyAnalysys()
	{
		std::string console_argument;
		_config.operation = Operation::NONE;

		for (size_t i = 1; i < _argc; ++i)
		{
			console_argument = _argv[i];

			if (console_argument == "-help")
			{
				std::cout << "Not written yet. Sorry about that." << std::endl;
				return std::exit(0);
			}

			for (auto& x : _analysys_id)
			{
				if (x.first == console_argument)
				{
					_config.operation = x.second;
					break;
				}
			}
		}
	}

	void App::_ReadFile()
	{
		std::ifstream file_stream(_config.input_file);

		if (!file_stream.is_open())
			throw std::invalid_argument(std::format("ERROR! File could not be opened : {}\n", _config.input_file.string()));
		
		for (std::string line; std::getline(file_stream, line);)
			_file_data.push_back(line);

		if (_file_data.empty())
			throw std::invalid_argument(std::format("ERROR! File is empty : {}\n", _config.input_file.string()));

		file_stream.close();
	}

	void App::_Execute()
	{
		std::unique_ptr<bioutilities::Report> report;
		switch(_config.operation)
		{
		case Operation::UpstreamORFs:
			report = std::make_unique<bioutilities::UpstreamOrfReport>(_file_data, _config);
			break;
		case Operation::Translation:
			report = std::make_unique<bioutilities::TranslationReport>(_file_data, _config);
			break;
		}
		_WriteFile(report->GetDataVector());
	}

	void App::_WriteFile(const std::vector<std::string>& report)
	{
		std::ofstream file_stream;
		file_stream.open(_config.output_file);

		if (!file_stream.is_open())
			throw std::invalid_argument(std::format("ERROR! File couldn't be opened : {}\n", _config.output_file.string()));

		for (const auto& x : report)
		{
			for (const auto& y : x)
				file_stream << y;
		}

		file_stream.close();
	}

	void App::Run()
	{
		if (_argc == 1)
		{
			std::cout << "ERROR! No arguments provided.\n";
			return std::exit(1);
		}

		try
		{
			_IdentifyAnalysys();
			_IdentifyDelimeters();
			_IdentifyIOFiles();
			_IdentifyKeySequenceIndexes();
			_IdentifyAdditionalArguments();
			_ReadFile();
			_Execute();
		}
		catch (const std::bad_alloc&)
		{
			std::cout << "ERROR! Check delimiters format.";
			return std::exit(1);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			return std::exit(1);
		}

		return std::exit(0);
	}
}

namespace bioutilities
{
	std::vector<std::string> SplitStringToVector(const std::string& string, char delimiter)
	{
		std::vector<std::string> splited_string;
		std::stringstream string_stream(string);
		std::string temp;

		while (std::getline(string_stream, temp, delimiter))
			splited_string.push_back(temp);

		if (splited_string.size() == 1)
			throw std::invalid_argument(std::format("ERROR! Wrong delimiter: \'{}\' in string \'{}\'.\n", delimiter, string));

		return splited_string;
	}

	uint32_t StringCodonToUintCodon(const std::string& string_codon)
	{
		if (string_codon.size() != 3)
			throw std::invalid_argument(std::format("ERROR! Codon is expected to be 3 char long: \"{}\".\n", string_codon));

		uint32_t uint_codon = 0;

		const std::array<uint32_t, 3> indexes = { 16, 4, 1 };

		for (size_t i = 0; i < indexes.size(); ++i)
		{
			switch (string_codon.at(i))
			{
			case 'A':
				uint_codon += 0;	//indexes[i] * 0;
				break;
			case 'C':
				uint_codon += indexes[i] * 1;
				break;
			case 'G':
				uint_codon += indexes[i] * 2;
				break;
			case 'T':
				uint_codon += indexes[i] * 3;
				break;
			case 'U':
				uint_codon += indexes[i] * 3;
				break;
			default:
				throw std::invalid_argument(std::format("ERROR! Unknown char \'{}\' in \"{}\" codon.\n", string_codon.at(i), string_codon));
			}
		}

		return uint_codon;
	}

	uint32_t UintCodonToUintAA(uint32_t uint_codon) { return CODONS_TO_AMINO_ACIDS_INDEXES[uint_codon]; };

	char UintCodonToCharAA(uint32_t uint_codon) { return AMINO_ACIDS[CODONS_TO_AMINO_ACIDS_INDEXES[uint_codon]]; };

	std::string UintCodonToStringRNA(uint32_t uint_codon) { return RNA_CODONS[uint_codon]; };

	std::string UintCodonToStringDNA(uint32_t uint_codon) { return DNA_CODONS[uint_codon]; };

	char UintAAToCharAA(uint32_t uint_codon) { return AMINO_ACIDS[uint_codon]; };

	bool IsRnaSequence(const std::string& sequence)
	{
		std::array<char, 4> references = { 'A', 'U', 'G', 'C' };
		for (size_t i = 0; i < sequence.size(); ++i)
		{
			if (std::find(references.begin(), references.end(), sequence.at(i)) == references.end())
				return false;
		}
		return true;
	};

	bool IsDnaSequence(const std::string& sequence)
	{
		std::array<char, 4> references{ 'A', 'T', 'G', 'C' };
		for (size_t i = 0; i < sequence.size(); ++i)
		{
			if (std::find(references.begin(), references.end(), sequence.at(i)) == references.end())
				return false;
		}
		return true;
	};

	bool IsPeptideSequence(const std::string& sequence)
	{
		for (size_t i = 0; i < sequence.size(); ++i)
		{
			if (std::find(AMINO_ACIDS.begin(), AMINO_ACIDS.end(), sequence.at(i)) == AMINO_ACIDS.end())
				return false;
		}
		return true;
	};

	std::vector<std::vector<uint32_t>> FindThreeFrames(std::string raw_sequence, const std::array<std::string, 64>& codon_library)
	{
		std::transform(raw_sequence.begin(), raw_sequence.end(), raw_sequence.begin(), ::toupper);
		std::vector<std::vector<uint32_t>> three_frames;
		std::vector<uint32_t> buffer;
		for (size_t x = 0; x < 3; ++x)
		{
			buffer.reserve((raw_sequence.length() - x - ((raw_sequence.length() - x) % 3)) / 3);
			for (size_t y = 0; y < raw_sequence.length(); y += 3)
			{
				if (raw_sequence.length() < x + y + 3)
					continue;

				buffer.push_back(StringCodonToUintCodon(raw_sequence.substr(x + y, 3)));
			}
			three_frames.push_back(buffer);
			buffer.clear();
		}
		return three_frames;
	};


	std::vector<std::string> Report::GetDataVector() { return _report; };

	UpstreamOrfReport::UpstreamOrfReport(const std::vector<std::string>& file_content, const app::Config& config)
	{
		std::vector<std::string> separated_input;
		std::string id;
		std::string raw_seequence;
		std::vector<std::vector<uint32_t>> three_frames;
		std::vector<std::pair<size_t, size_t>> all_orfs;
		std::pair<size_t, size_t> main_orf;
		std::vector<std::pair<size_t, size_t>> uorfs;

		std::string title = "";
		title += "ID";
		title += config.output_delimiter;
		title += "Main ORF (start - end - size)";
		title += config.output_delimiter;
		title += "Sum of upstream ORFs";
		title += config.output_delimiter;
		title += "Upstream ORFs (start - end - size)\n";
		_report.push_back(title);

		for (const auto& x : file_content)
		{
			std::vector<std::string> separated_input = SplitStringToVector(x, config.input_delimiter);
			if(separated_input.size() == 1)
				throw std::invalid_argument(std::format("ERROR! Inappropriate delimiter for input file : \"{}\".\n", config.input_delimiter));

			std::string raw_sequence = separated_input[config.sequence_column];
			id = separated_input[config.key_column];

			if (IsRnaSequence(raw_sequence))
				three_frames = FindThreeFrames(raw_sequence, RNA_CODONS);
			else if(IsDnaSequence(raw_sequence))
				three_frames = FindThreeFrames(raw_sequence, DNA_CODONS);
			else
				throw std::invalid_argument(std::format("ERROR! Inappropriate RNA/DNA sequence in input file : \"{}\".\n", id));

			all_orfs = _FindAllORFsIndexes(three_frames);
			main_orf = _FindMainORFIndexes(all_orfs);
			uorfs = _SortOnlyUpstreamORFsIndexes(main_orf, all_orfs);
			_report.push_back(_FinalizeData(id, main_orf, uorfs, config));

			separated_input.clear();
			id.clear();
			raw_seequence.clear();
			three_frames.clear();
			all_orfs.clear();
			std::pair<size_t, size_t> main_orf = std::pair<size_t, size_t>();
			uorfs.clear();
		}
	};

	std::vector<std::pair<size_t, size_t>> UpstreamOrfReport::_FindAllORFsIndexes(const std::vector<std::vector<uint32_t>>& three_frames)
	{
		std::vector<std::pair<size_t, size_t>> orf_buffer;
		uint32_t current_genetic_code_unit;
		size_t start;
		size_t end;

		bool translation = false;
		for (size_t x = 0; x < 3; ++x)
		{
			for (size_t y = 0; y < three_frames.at(x).size(); ++y)
			{	
				current_genetic_code_unit = UintCodonToUintAA(three_frames.at(x).at(y));

				if (current_genetic_code_unit == 12 && !translation) //12 is Met
				{
					start = (y * 3) + x + 1; //ORF enumeration starts from 1
					translation = true;
				}

				if (current_genetic_code_unit == 20 || (y == three_frames.at(x).size() - 1)) //20 is X(Stop)
				{
					if (translation)
					{
						end = (y * 3) + x + 3;
						orf_buffer.push_back(std::make_pair(start, end));
					}
					translation = false;
				}
			};
		}
		return orf_buffer;
	};

	std::pair<size_t, size_t> UpstreamOrfReport::_FindMainORFIndexes(const std::vector<std::pair<size_t, size_t>>& all_orfs)
	{
		std::pair<size_t, size_t> main_orf;
		size_t size = 0;
		size_t temp = 0;

		for (auto& x : all_orfs)
		{
			temp = x.second - x.first;
			if (temp > size)
			{
				main_orf = x;
				size = temp;
			}
		}

		return main_orf;
	};

	std::vector<std::pair<size_t, size_t>> UpstreamOrfReport::_SortOnlyUpstreamORFsIndexes(const std::pair<size_t, size_t>& main_orf, const std::vector<std::pair<size_t, size_t>>& all_orfs)
	{
		std::vector<std::pair<size_t, size_t>> temp;
		for (auto& x: all_orfs)
		{
			if (x.first < main_orf.first)
				temp.push_back(x);
		}
		return temp;
	};

	std::string UpstreamOrfReport::_FinalizeData(std::string id, std::pair<size_t, size_t> main_orf, std::vector<std::pair<size_t, size_t>> micro_orfs, const app::Config& config)
	{
		std::string output = "";
		output += id;
		output += config.output_delimiter;
		output += std::format("({}-{}-{}) ", main_orf.first, main_orf.second, (main_orf.second - main_orf.first));
		output += config.output_delimiter;
		output += std::to_string(micro_orfs.size());
		output += config.output_delimiter;
		for (const auto& x : micro_orfs)
		{
			output += std::format("({}-{}-{}) ", x.first, x.second, (x.second - x.first));
		}
		output += "\n";
		return output;
	};

	TranslationReport::TranslationReport(const std::vector<std::string>& file_content, const app::Config& config)
	{
		std::vector<std::string> separated_input;
		std::string id;
		std::string raw_seequence;
		std::vector<std::vector<uint32_t>> three_frames;
		std::vector<std::vector<uint32_t>> all_orfs;
		std::vector<uint32_t> main_orf;
		std::string str_main_orf;

		std::string title = "";
		title += "ID";
		title += config.output_delimiter;
		title += "Translated main ORF\n";
		_report.push_back(title);

		for (const auto& x : file_content)
		{
			std::vector<std::string> separated_input = SplitStringToVector(x, config.input_delimiter);
			if (separated_input.size() == 1)
				throw std::invalid_argument(std::format("ERROR! Inappropriate delimiter for input file : \"{}\".\n", config.input_delimiter));

			std::string raw_sequence = separated_input[config.sequence_column];
			id = separated_input[config.key_column];

			if (IsRnaSequence(raw_sequence))
				three_frames = FindThreeFrames(raw_sequence, RNA_CODONS);
			else if (IsDnaSequence(raw_sequence))
				three_frames = FindThreeFrames(raw_sequence, DNA_CODONS);
			else
				throw std::invalid_argument(std::format("ERROR! Inappropriate RNA/DNA sequence in input file : \"{}\".\n", id));

			all_orfs = _FindAllORFs(three_frames);
			main_orf = _FindMainORF(all_orfs);
			str_main_orf = _ConvertMainORFToString(main_orf);
			_report.push_back(_FinalizeData(id, str_main_orf, config));

			separated_input.clear();
			id.clear();
			raw_seequence.clear();
			three_frames.clear();
			all_orfs.clear();
			main_orf.clear();
			str_main_orf = "";
		}
	};

	std::vector<std::vector<uint32_t>> TranslationReport::_FindAllORFs(const std::vector<std::vector<uint32_t>>& three_frames)
	{
		std::vector<std::vector<uint32_t>> orf_buffer;
		uint32_t current_genetic_code_unit;
		std::vector<uint32_t> current_frame;

		bool translation = false;
		for (size_t x = 0; x < 3; ++x)
		{
			for (size_t y = 0; y < three_frames.at(x).size(); ++y)
			{
				current_genetic_code_unit = UintCodonToUintAA(three_frames.at(x).at(y));

				if (current_genetic_code_unit == 20 || (y == three_frames.at(x).size() - 1)) //20 is X(Stop)
				{
					if (translation)
					{
						orf_buffer.push_back(current_frame);
						current_frame.clear();
					}
					translation = false;
				}

				if (current_genetic_code_unit == 12) //12 is Met
				{
					current_frame.push_back(current_genetic_code_unit);
					translation = true;
				}
				else if (translation)
					current_frame.push_back(current_genetic_code_unit);	
			};
		}
		return orf_buffer;
	};

	std::vector<uint32_t> TranslationReport::_FindMainORF(const std::vector<std::vector<uint32_t>>& all_orfs)
	{
		std::vector<uint32_t> main_orf;

		for (auto& x : all_orfs)
			if (x.size() > main_orf.size())
				main_orf = x;

		return main_orf;
	};

	std::string TranslationReport::_ConvertMainORFToString(const std::vector<uint32_t>& main_orf)
	{
		std::string str_main_orf = "";
		for (const auto& x : main_orf)
			str_main_orf += UintAAToCharAA(x);

		return str_main_orf;
	};

	std::string TranslationReport::_FinalizeData(std::string id, const std::string& main_orf, const app::Config& config)
	{
		std::string output = "";
		output += id;
		output += config.output_delimiter;
		output += main_orf;
		output += config.output_delimiter;
		output += "\n";
		return output;
	};

	//TranscriptionReport::TranscriptionReport(const std::vector<std::string>& file_content, const app::Config& config);
	//std::string TranscriptionReport::_ConvertToDNA(const std::string& input);
	//std::string TranscriptionReport::_FinalizeData(std::string id, const std::string& final_dna, const app::Config& config);


	//class ReverseTranscriptionReport
	//{
	//public:
	//	explicit ReverseTranscriptionReport(const std::vector<std::string>& file_content, const app::Config& config);

	//private:
	//	std::string _ConvertToRNA(const std::string& input);
	//	std::string _FinalizeData(std::string id, const std::string& final_dna, const app::Config& config);

	//	std::vector<std::string> _report;
	//};
}

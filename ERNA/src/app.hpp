#pragma once

#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <format>


namespace app
{
	enum class Operation
	{
		Help,
		UpstreamORFs,
		StemLoops,
		Translation,
		Transcription,
		ReverseTranscrition,
		Align,
		Find,
		NONE
	};

	struct Config
	{
		#pragma warning(disable:26495)
		Config() = default;
		#pragma warning(default:26495) 


		Operation operation;
		std::filesystem::path input_file;
		std::filesystem::path output_file;
		char input_delimiter;
		char output_delimiter;
		uint32_t key_column;				//enumaration starts from 1, default value 1
		uint32_t sequence_column;			//enumeration starts from 1, default value 2
		std::string additional_argument;
	};

	class App
	{
	public:
		explicit App(int32_t argc, char* argv[]);
		void Run();

	private:
		void _IdentifyDelimeters();
		void _IdentifyIOFiles();
		void _IdentifyKeySequenceIndexes();
		void _IdentifyAdditionalArguments();
		void _IdentifyAnalysys();
		void _ReadFile();
		void _Execute();
		void _WriteFile(const std::vector<std::string>& report);
		bool _CorrectArgumentFormat(size_t iteration);

		size_t _argc;
		char** _argv;
		Config _config;
		std::vector<std::string> _file_data;
		std::vector<std::string> _output_data;

		std::unordered_map<char, char> _comand_line_delimiters
		{
			{'t', '\t'},	//tab
			{'s', ' '}		//space
		};

		std::unordered_map<std::string, Operation> _analysys_id
		{
			{ "-help", Operation::Help },

			{ "-uorfs", Operation::UpstreamORFs },				//calculate all upstream ORFs in (DNA, RNA)
			{ "-stemloops", Operation::StemLoops },				//identify all stemloops with minimal specified size (-a) default 4 nt (DNA, RNA)
			{ "-translate", Operation::Translation },			//translate main ORF from (DNA, RNA)
			{ "-transcribe", Operation::Transcription },		//transcribe (DNA)
			{ "-revtrans", Operation::ReverseTranscrition },	//preforme reverse translation (RNA)
			{ "-align", Operation::Align },						//find complementary sequences within file with minimal specified size (-ap) default 4 nt (DNA, RNA) 3 aa (Peptide)
			{ "-find", Operation::Find }						//Find specific sequence in file (DNA, RNA, Peptide) provided in -ap value
		};
	};
}

namespace bioutilities
{
	const std::array<std::string, 64> DNA_CODONS
	{
		"AAA", "AAC", "AAG", "AAT",
		"ACA", "ACC", "ACG", "ACT",
		"AGA", "AGC", "AGG", "AGT",
		"ATA", "ATC", "ATG", "ATT",

		"CAA", "CAC", "CAG", "CAT",
		"CCA", "CCC", "CCG", "CCT",
		"CGA", "CGC", "CGG", "CGT",
		"CTA", "CTC", "CTG", "CTT",

		"GAA", "GAC", "GAG", "GAT",
		"GCA", "GCC", "GCG", "GCT",
		"GGA", "GGC", "GGG", "GGT",
		"GTA", "GTC", "GTG", "GTT",

		"TAA", "TAC", "TAG", "TAT",
		"TCA", "TCC", "TCG", "TCT",
		"TGA", "TGC", "TGG", "TGT",
		"TTA", "TTC", "TTG", "TTT"
	};

	const std::array<std::string, 64> RNA_CODONS
	{
		"AAA", "AAC", "AAG", "AAU",
		"ACA", "ACC", "ACG", "ACU",
		"AGA", "AGC", "AGG", "AGU",
		"AUA", "AUC", "AUG", "AUU",

		"CAA", "CAC", "CAG", "CAU",
		"CCA", "CCC", "CCG", "CCU",
		"CGA", "CGC", "CGG", "CGU",
		"CUA", "CUC", "CUG", "CUU",

		"GAA", "GAC", "GAG", "GAU",
		"GCA", "GCC", "GCG", "GCU",
		"GGA", "GGC", "GGG", "GGU",
		"GUA", "GUC", "GUG", "GUU",

		"UAA", "UAC", "UAG", "UAU",
		"UCA", "UCC", "UCG", "UCU",
		"UGA", "UGC", "UGG", "UGU",
		"UUA", "UUC", "UUG", "UUU"
	};

	const std::array<char, 21> AMINO_ACIDS
	{
		'A', 'R', 'N', 'D',
		'C', 'E', 'Q', 'G',
		'H', 'I', 'L', 'K',
		'M', 'F', 'P', 'S',
		'T', 'W', 'Y', 'V',
		'X' //Stop
	};

	const std::array<uint32_t, 64> CODONS_TO_AMINO_ACIDS_INDEXES
	{
		11, 2,  11, 2,
		16, 16, 16, 16,
		1,  15, 1,  15,
		9,  9,  12, 9,

		6,  8,  6,  8,
		14, 14, 14, 14,
		1,  1,  1,  1,
		10, 10, 10, 10,

		5,  3,  5,  3,
		0,  0,  0,  0,
		7,  7,  7,  7,
		19, 19, 19, 19,

		20, 18, 20, 18,
		15, 15, 15, 15,
		20, 4,  17, 4,
		10, 13, 10, 13
	};

	inline std::vector<std::string> SplitStringToVector(const std::string& string, char delimiter);

	inline uint32_t StringCodonToUintCodon(const std::string& string_codon);

	inline uint32_t UintCodonToUintAA(uint32_t uint_codon);

	inline char UintCodonToCharAA(uint32_t uint_codon);

	inline std::string UintCodonToStringRNA(uint32_t uint_codon);

	inline std::string UintCodonToStringDNA(uint32_t uint_codon);

	inline char UintAAToCharAA(uint32_t uint_codon);

	inline bool IsRnaSequence(const std::string& sequence);

	inline bool IsDnaSequence(const std::string& sequence);

	inline bool IsPeptideSequence(const std::string& sequence);

	std::vector<std::vector<uint32_t>> FindThreeFrames(std::string raw_sequence, const std::array<std::string, 64>& codon_library);

	class Report
	{
	public:
		Report() = default;
		std::vector<std::string> GetDataVector();

	protected:
		std::vector<std::string> _report;
	};

	class UpstreamOrfReport : public Report
	{
	public:
		explicit UpstreamOrfReport(const std::vector<std::string>& file_content, const app::Config& config);

	private:
		std::vector<std::pair<size_t, size_t>> _FindAllORFsIndexes(const std::vector<std::vector<uint32_t>>& three_frames);
		std::pair<size_t, size_t> _FindMainORFIndexes(const std::vector<std::pair<size_t, size_t>>& all_orfs);
		std::vector<std::pair<size_t, size_t>> _SortOnlyUpstreamORFsIndexes(const std::pair<size_t, size_t>& main_orf, const std::vector<std::pair<size_t, size_t>>& all_orfs);
		std::string _FinalizeData(std::string id, std::pair<size_t, size_t> main_orf, std::vector<std::pair<size_t, size_t>> micro_orfs, const app::Config& config);
	};

	class TranslationReport : public Report
	{
	public:
		explicit TranslationReport(const std::vector<std::string>& file_content, const app::Config& config);

	private:
		std::vector< std::vector<uint32_t>> _FindAllORFs(const std::vector<std::vector<uint32_t>>& three_frames);
		std::vector<uint32_t> _FindMainORF(const std::vector< std::vector<uint32_t>>& all_orfs);
		std::string _ConvertMainORFToString(const std::vector<uint32_t>& main_orf);
		std::string _FinalizeData(std::string id, const std::string& main_orf, const app::Config& config);
	};

	class TranscriptionReport : public Report
	{
	public:
		explicit TranscriptionReport(const std::vector<std::string>& file_content, const app::Config& config);

	private:
		std::string _ConvertToDNA(const std::string& input);
		std::string _FinalizeData(std::string id, const std::string& final_dna, const app::Config& config);
	};

	class ReverseTranscriptionReport : public Report
	{
	public:
		explicit ReverseTranscriptionReport(const std::vector<std::string>& file_content, const app::Config& config);

	private:
		std::string _ConvertToRNA(const std::string& input);
		std::string _FinalizeData(std::string id, const std::string& final_dna, const app::Config& config);
	};
}

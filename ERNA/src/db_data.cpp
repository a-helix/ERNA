#include "db_data.h"

namespace db_data
{
	WormBaseComplementaryDna::WormBaseComplementaryDna(const std::string& input_data, const char& delimiter, bioutilities::GeneticCodeFactory& factory)
	{ 
		_ORF = bioutilities::CodonSequence();
		_delimiter_separated_input = splited_string::SplitedString(input_data, delimiter).ToVector();
		AssignSplitedData();
		CalculateThreeFrames(_raw_rna_data_string, factory);
		CalculateAllORFs();
		SetLongestORF();
		CalculateUtrRegions(factory);
		_uORFs.clear();
		_frames.clear();
		std::string five_prime_UTR_with_main_ORF = _5primeUTR + _ORF.ToDnaString(factory);
		CalculateThreeFrames(five_prime_UTR_with_main_ORF, factory);
		CalculateAllORFs();
		SortOnlyMicroORFs();
		_sum_of_uORFs = _uORFs.size();
		FindAATAAASequences();
	};

	WormBaseComplementaryDna::~WormBaseComplementaryDna() {};
	
	void WormBaseComplementaryDna::AssignSplitedData()
	{
		_database_id = _delimiter_separated_input[0];
		_gene_name = _delimiter_separated_input[1];
		_transcript_id = _delimiter_separated_input[2];
		std::string _raw_rna_data_string_no_case = _delimiter_separated_input[3];

		std::transform(_raw_rna_data_string_no_case.begin(), _raw_rna_data_string_no_case.end(), _raw_rna_data_string_no_case.begin(), ::toupper);
		_raw_rna_data_string = _raw_rna_data_string_no_case;

	}
}

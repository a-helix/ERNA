#include "bioutilities.h"

namespace bioutilities
{
	//Codon class implementation start
	Codon::Codon(DNA_Codon dna_codon, RNA_Codon rna_codon, AA_3Char aa_3char, AA_1Char aa_1char)
		: _dna_codon(dna_codon), _rna_codon(rna_codon), _aa_3char(aa_3char), _aa_1char(aa_1char) {}

	Codon::~Codon() {}

	DNA_Codon Codon::DnaCodon() { return _dna_codon; }
	RNA_Codon Codon::RnaCodon() { return _rna_codon; }
	AA_3Char Codon::AA3Char() { return _aa_3char; }
	AA_1Char Codon::AA1Char() { return _aa_1char; }

	bool Codon::operator==(Codon& rhs)
	{
		if (_dna_codon == rhs.DnaCodon() &&
			_rna_codon == rhs.RnaCodon() &&
			_aa_3char == rhs.AA3Char() &&
			_aa_1char == rhs.AA1Char())
			return true;
		return false;
	}

	GeneticCodeFactory::GeneticCodeFactory()
	{
		_dna_codon_map =
		{
			{ "TTT", DNA_Codon::TTT }, { "TTC", DNA_Codon::TTC }, { "TTA", DNA_Codon::TTA }, { "TTG", DNA_Codon::TTG },
			{ "ATT", DNA_Codon::ATT }, { "ATC", DNA_Codon::ATC }, { "ATA", DNA_Codon::ATA }, { "ATG", DNA_Codon::ATG },
			{ "TCT", DNA_Codon::TCT }, { "TCC", DNA_Codon::TCC }, { "TCA", DNA_Codon::TCA }, { "TCG", DNA_Codon::TCG },
			{ "ACT", DNA_Codon::ACT }, { "ACC", DNA_Codon::ACC }, { "ACA", DNA_Codon::ACA }, { "ACG", DNA_Codon::ACG },

			{ "TAT", DNA_Codon::TAT }, { "TAC", DNA_Codon::TAC }, { "TAA", DNA_Codon::TAA }, { "TAG", DNA_Codon::TAG },
			{ "AAT", DNA_Codon::AAT }, { "AAC", DNA_Codon::AAC }, { "AAA", DNA_Codon::AAA }, { "AAG", DNA_Codon::AAG },
			{ "TGT", DNA_Codon::TGT }, { "TGC", DNA_Codon::TGC }, { "TGA", DNA_Codon::TGA }, { "TGG", DNA_Codon::TGG },
			{ "AGT", DNA_Codon::AGT }, { "AGC", DNA_Codon::AGC }, { "AGA", DNA_Codon::AGA }, { "AGG", DNA_Codon::AGG },

			{ "CTT", DNA_Codon::CTT }, { "CTC", DNA_Codon::CTC }, { "CTA", DNA_Codon::CTA }, { "CTG", DNA_Codon::CTG },
			{ "GTT", DNA_Codon::GTT }, { "GTC", DNA_Codon::GTC }, { "GTA", DNA_Codon::GTA }, { "GTG", DNA_Codon::GTG },
			{ "CCT", DNA_Codon::CCT }, { "CCC", DNA_Codon::CCC }, { "CCA", DNA_Codon::CCA }, { "CCG", DNA_Codon::CCG },
			{ "GCT", DNA_Codon::GCT }, { "GCC", DNA_Codon::GCC }, { "GCA", DNA_Codon::GCA }, { "GCG", DNA_Codon::GCG },

			{ "CAT", DNA_Codon::CAT }, { "CAC", DNA_Codon::CAC }, { "CAA", DNA_Codon::CAA }, { "CAG", DNA_Codon::CAG },
			{ "GAT", DNA_Codon::GAT }, { "GAC", DNA_Codon::GAC }, { "GAA", DNA_Codon::GAA }, { "GAG", DNA_Codon::GAG },
			{ "CGT", DNA_Codon::CGT }, { "CGC", DNA_Codon::CGC }, { "CGA", DNA_Codon::CGA }, { "CGG", DNA_Codon::CGG },
			{ "GGT", DNA_Codon::GGT }, { "GGC", DNA_Codon::GGC }, { "GGA", DNA_Codon::GGA }, { "GGG", DNA_Codon::GGG }
		};

		_rna_codon_map =
		{
			{ "UUU", RNA_Codon::UUU }, { "UUC", RNA_Codon::UUC }, { "UUA", RNA_Codon::UUA }, { "UUG", RNA_Codon::UUG },
			{ "AUU", RNA_Codon::AUU }, { "AUC", RNA_Codon::AUC }, { "AUA", RNA_Codon::AUA }, { "AUG", RNA_Codon::AUG },
			{ "UCU", RNA_Codon::UCU }, { "UCC", RNA_Codon::UCC }, { "UCA", RNA_Codon::UCA }, { "UCG", RNA_Codon::UCG },
			{ "ACU", RNA_Codon::ACU }, { "ACC", RNA_Codon::ACC }, { "ACA", RNA_Codon::ACA }, { "ACG", RNA_Codon::ACG },

			{ "UAU", RNA_Codon::UAU }, { "UAC", RNA_Codon::UAC }, { "UAA", RNA_Codon::UAA }, { "UAG", RNA_Codon::UAG },
			{ "AAU", RNA_Codon::AAU }, { "AAC", RNA_Codon::AAC }, { "AAA", RNA_Codon::AAA }, { "AAG", RNA_Codon::AAG },
			{ "UGU", RNA_Codon::UGU }, { "UGC", RNA_Codon::UGC }, { "UGA", RNA_Codon::UGA }, { "UGG", RNA_Codon::UGG },
			{ "AGU", RNA_Codon::AGU }, { "AGC", RNA_Codon::AGC }, { "AGA", RNA_Codon::AGA }, { "AGG", RNA_Codon::AGG },

			{ "CUU", RNA_Codon::CUU }, { "CUC", RNA_Codon::CUC }, { "CUA", RNA_Codon::CUA }, { "CUG", RNA_Codon::CUG },
			{ "GUU", RNA_Codon::GUU }, { "GUC", RNA_Codon::GUC }, { "GUA", RNA_Codon::GUA }, { "GUG", RNA_Codon::GUG },
			{ "CCU", RNA_Codon::CCU }, { "CCC", RNA_Codon::CCC }, { "CCA", RNA_Codon::CCA }, { "CCG", RNA_Codon::CCG },
			{ "GCU", RNA_Codon::GCU }, { "GCC", RNA_Codon::GCC }, { "GCA", RNA_Codon::GCA }, { "GCG", RNA_Codon::GCG },

			{ "CAU", RNA_Codon::CAU }, { "CAC", RNA_Codon::CAC }, { "CAA", RNA_Codon::CAA }, { "CAG", RNA_Codon::CAG },
			{ "GAU", RNA_Codon::GAU }, { "GAC", RNA_Codon::GAC }, { "GAA", RNA_Codon::GAA }, { "GAG", RNA_Codon::GAG },
			{ "CGU", RNA_Codon::CGU }, { "CGC", RNA_Codon::CGC }, { "CGA", RNA_Codon::CGA }, { "CGG", RNA_Codon::CGG },
			{ "GGU", RNA_Codon::GGU }, { "GGC", RNA_Codon::GGC }, { "GGA", RNA_Codon::GGA }, { "GGG", RNA_Codon::GGG }
		};

		_aa_3char_map =
		{
			{ "Ala", AA_3Char::Ala }, { "Arg", AA_3Char::Arg }, { "Asn", AA_3Char::Asn }, { "Asp", AA_3Char::Asp }, { "Cys", AA_3Char::Cys },
			{ "Glu", AA_3Char::Glu }, { "Gln", AA_3Char::Gln }, { "Gly", AA_3Char::Gly }, { "His", AA_3Char::His }, { "Ile", AA_3Char::Ile },
			{ "Leu", AA_3Char::Leu }, { "Lys", AA_3Char::Lys }, { "Met", AA_3Char::Met }, { "Phe", AA_3Char::Phe }, { "Pro", AA_3Char::Pro },
			{ "Ser", AA_3Char::Ser }, { "Thr", AA_3Char::Thr }, { "Trp", AA_3Char::Trp }, { "Tyr", AA_3Char::Tyr }, { "Val", AA_3Char::Val },
			{  "x" , AA_3Char::Stop }
		};

		_aa_1char_map =
		{
			{ "A", AA_1Char::A }, { "R", AA_1Char::R }, { "N", AA_1Char::N }, { "D", AA_1Char::D }, { "C", AA_1Char::C },
			{ "E", AA_1Char::E }, { "Q", AA_1Char::Q }, { "G", AA_1Char::G }, { "H", AA_1Char::H }, { "I", AA_1Char::I },
			{ "L", AA_1Char::L }, { "K", AA_1Char::K }, { "M", AA_1Char::M }, { "F", AA_1Char::F }, { "P", AA_1Char::P },
			{ "S", AA_1Char::S }, { "T", AA_1Char::T }, { "W", AA_1Char::W }, { "Y", AA_1Char::Y }, { "V", AA_1Char::V },
			{ "x", AA_1Char::Stop }
		};

		_genetic_code_buffer.insert(_genetic_code_buffer.end(),
		{
			Codon(DNA_Codon::GCT, RNA_Codon::GCU, AA_3Char::Ala,  AA_1Char::A),
			Codon(DNA_Codon::GCC, RNA_Codon::GCC, AA_3Char::Ala,  AA_1Char::A),
			Codon(DNA_Codon::GCG, RNA_Codon::GCG, AA_3Char::Ala,  AA_1Char::A),
			Codon(DNA_Codon::GCA, RNA_Codon::GCA, AA_3Char::Ala,  AA_1Char::A),
			Codon(DNA_Codon::TGT, RNA_Codon::UGU, AA_3Char::Cys,  AA_1Char::C),
			Codon(DNA_Codon::TGC, RNA_Codon::UGC, AA_3Char::Cys,  AA_1Char::C),
			Codon(DNA_Codon::GAT, RNA_Codon::GAU, AA_3Char::Asp,  AA_1Char::D),
			Codon(DNA_Codon::GAC, RNA_Codon::GAC, AA_3Char::Asp,  AA_1Char::D),
			Codon(DNA_Codon::GAA, RNA_Codon::GAA, AA_3Char::Glu,  AA_1Char::E),
			Codon(DNA_Codon::GAG, RNA_Codon::GAG, AA_3Char::Glu,  AA_1Char::E),
			Codon(DNA_Codon::TTT, RNA_Codon::UUU, AA_3Char::Phe,  AA_1Char::F),
			Codon(DNA_Codon::TTC, RNA_Codon::UUC, AA_3Char::Phe,  AA_1Char::F),
			Codon(DNA_Codon::GGT, RNA_Codon::GGU, AA_3Char::Gly,  AA_1Char::G),
			Codon(DNA_Codon::GGC, RNA_Codon::GGC, AA_3Char::Gly,  AA_1Char::G),
			Codon(DNA_Codon::GGA, RNA_Codon::GGA, AA_3Char::Gly,  AA_1Char::G),
			Codon(DNA_Codon::GGG, RNA_Codon::GGG, AA_3Char::Gly,  AA_1Char::G),
			Codon(DNA_Codon::CAT, RNA_Codon::CAU, AA_3Char::His,  AA_1Char::H),
			Codon(DNA_Codon::CAC, RNA_Codon::CAC, AA_3Char::His,  AA_1Char::H),
			Codon(DNA_Codon::ATT, RNA_Codon::AUU, AA_3Char::Ile,  AA_1Char::I),
			Codon(DNA_Codon::ATA, RNA_Codon::AUA, AA_3Char::Ile,  AA_1Char::I),
			Codon(DNA_Codon::ATC, RNA_Codon::AUC, AA_3Char::Ile,  AA_1Char::I),
			Codon(DNA_Codon::AAA, RNA_Codon::AAA, AA_3Char::Lys,  AA_1Char::K),
			Codon(DNA_Codon::AAG, RNA_Codon::AAG, AA_3Char::Lys,  AA_1Char::K),
			Codon(DNA_Codon::TTA, RNA_Codon::UUA, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::TTG, RNA_Codon::UUG, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::CTC, RNA_Codon::CUC, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::CTT, RNA_Codon::CUU, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::CTA, RNA_Codon::CUA, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::CTG, RNA_Codon::CUG, AA_3Char::Leu,  AA_1Char::L),
			Codon(DNA_Codon::ATG, RNA_Codon::AUG, AA_3Char::Met,  AA_1Char::M),
			Codon(DNA_Codon::AAC, RNA_Codon::AAC, AA_3Char::Asn,  AA_1Char::N),
			Codon(DNA_Codon::AAT, RNA_Codon::AAU, AA_3Char::Asn,  AA_1Char::N),
			Codon(DNA_Codon::CCT, RNA_Codon::CCU, AA_3Char::Pro,  AA_1Char::P),
			Codon(DNA_Codon::CCC, RNA_Codon::CCC, AA_3Char::Pro,  AA_1Char::P),
			Codon(DNA_Codon::CCA, RNA_Codon::CCA, AA_3Char::Pro,  AA_1Char::P),
			Codon(DNA_Codon::CCG, RNA_Codon::CCG, AA_3Char::Pro,  AA_1Char::P),
			Codon(DNA_Codon::CAA, RNA_Codon::CAA, AA_3Char::Gln,  AA_1Char::Q),
			Codon(DNA_Codon::CAG, RNA_Codon::CAG, AA_3Char::Gln,  AA_1Char::Q),
			Codon(DNA_Codon::CGA, RNA_Codon::CGA, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::CGG, RNA_Codon::CGG, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::AGA, RNA_Codon::AGA, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::AGG, RNA_Codon::AGG, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::CGT, RNA_Codon::CGU, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::CGC, RNA_Codon::CGC, AA_3Char::Arg,  AA_1Char::R),
			Codon(DNA_Codon::TCT, RNA_Codon::UCU, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::TCC, RNA_Codon::UCC, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::TCA, RNA_Codon::UCA, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::AGC, RNA_Codon::AGC, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::TCG, RNA_Codon::UCG, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::AGT, RNA_Codon::AGU, AA_3Char::Ser,  AA_1Char::S),
			Codon(DNA_Codon::ACT, RNA_Codon::ACU, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::ACC, RNA_Codon::ACC, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::ACA, RNA_Codon::ACA, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::ACG, RNA_Codon::ACG, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::TAT, RNA_Codon::UAU, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::TAC, RNA_Codon::UAC, AA_3Char::Thr,  AA_1Char::T),
			Codon(DNA_Codon::GTT, RNA_Codon::GUU, AA_3Char::Val,  AA_1Char::V),
			Codon(DNA_Codon::GTC, RNA_Codon::GUC, AA_3Char::Val,  AA_1Char::V),
			Codon(DNA_Codon::GTA, RNA_Codon::GUA, AA_3Char::Val,  AA_1Char::V),
			Codon(DNA_Codon::GTG, RNA_Codon::GUG, AA_3Char::Val,  AA_1Char::V),
			Codon(DNA_Codon::TGG, RNA_Codon::UGG, AA_3Char::Trp,  AA_1Char::W),
			Codon(DNA_Codon::TAA, RNA_Codon::UAA, AA_3Char::Stop, AA_1Char::Stop),
			Codon(DNA_Codon::TGA, RNA_Codon::UGA, AA_3Char::Stop, AA_1Char::Stop),
			Codon(DNA_Codon::TAG, RNA_Codon::UAG, AA_3Char::Stop, AA_1Char::Stop)
		});
	}
	//Codon class implementation end

	//GeneticCodeFactory class implementation start
	GeneticCodeFactory::~GeneticCodeFactory() {}

	Codon GeneticCodeFactory::DnaCodon(const std::string& dna_codon)
	{

		auto search = _dna_codon_map.find(dna_codon);
		if (search == _dna_codon_map.end())
		{
			throw std::invalid_argument(std::format("ERROR! Invaslid DNA Codon : {}\n", dna_codon));
		}
		for (auto& x : _genetic_code_buffer)
		{
			if (x.DnaCodon() == search->second)
				return x;
		}
	}

	Codon GeneticCodeFactory::RnaCodon(const std::string& rna_codon)
	{
		auto search = _rna_codon_map.find(rna_codon);
		if (search == _rna_codon_map.end())
		{
			throw std::invalid_argument(std::format("ERROR! Invaslid RNA Codon : {}\n", rna_codon));
		}
		for (auto& x : _genetic_code_buffer)
		{
			if (x.RnaCodon() == (RNA_Codon)search->second)
				return x;
		}
	}

	Codon GeneticCodeFactory::AA3Char(const std::string& aa_3char)
	{
		auto search = _aa_3char_map.find(aa_3char);
		if (search == _aa_3char_map.end())
		{
			throw std::invalid_argument(std::format("ERROR! Invaslid AA 3 char name : {}\n", aa_3char));
		}
		for (auto& x : _genetic_code_buffer)
		{
			if (x.AA3Char() == (AA_3Char)search->second)
				return x;
		}
	}

	Codon GeneticCodeFactory::AA1Char(const std::string& aa_1char)
	{
		auto search = _aa_1char_map.find(aa_1char);
		if (search == _aa_1char_map.end())
		{
			throw std::invalid_argument(std::format("ERROR! Invaslid AA 1 char name : {}\n", aa_1char));
		}
		for (auto& x : _genetic_code_buffer)
		{
			if (x.AA1Char() == (AA_1Char)search->second)
				return x;
		}
	}

	std::string GeneticCodeFactory::CodonToDnaString(Codon& input)
	{
		DNA_Codon input_dna_codon = input.DnaCodon();
		for (auto& x : _dna_codon_map)
		{
			if (x.second == input_dna_codon)
				return x.first;
		}
	}

	std::string GeneticCodeFactory::CodonToRnaString(Codon& input)
	{
		RNA_Codon input_rna_codon = input.RnaCodon();
		for (auto& x : _rna_codon_map)
		{
			if (x.second == input_rna_codon)
				return x.first;
		}
	}

	std::string GeneticCodeFactory::CodonToAA3CharString(Codon& input)
	{
		AA_3Char input_aa_3char = input.AA3Char();
		for (auto& x : _aa_3char_map)
		{
			if (x.second == input_aa_3char)
				return x.first;
		}
	}

	std::string GeneticCodeFactory::CodonToAA1CharString(Codon& input)
	{
		AA_1Char input_aa_1char = input.AA1Char();
		for (auto& x : _aa_1char_map)
		{
			if (x.second == input_aa_1char)
				return x.first;
		}
	}

	CodonSequence::CodonSequence()
	{
		_size_in_codones = 0;
		_start = 0;
		_end = 0;
		std::vector<Codon> _frame;
	};

	CodonSequence::CodonSequence(const std::vector<Codon>& frame, const size_t& start)
	{
		_frame = frame;
		_size_in_codones = frame.size();
		_start = start;
		_end = start + _size_in_codones * 3;
	};

	CodonSequence::~CodonSequence() {};

	size_t CodonSequence::SizeInCodons() { return _size_in_codones; };
	size_t CodonSequence::SizeInNucleotides() { return _size_in_codones * 3; };
	size_t CodonSequence::Start() { return _start; };
	size_t CodonSequence::End() { return _end; };

	Codon& CodonSequence::At(size_t index)
	{
		return _frame.at(index);
	};

	void CodonSequence::PushBack(Codon Codon)
	{
		_frame.push_back(Codon);
	};

	bool CodonSequence::operator==(CodonSequence& obj)
	{
		std::vector<Codon> obj_vector = obj.ToVector();
		if (_frame.size() != obj_vector.size())
			return false;
		for (size_t i = 0; i < _frame.size(); ++i)
		{
			if (_frame.at(i) != obj_vector.at(i))
				return false;
		}
		return true;
	}

	std::vector<Codon> CodonSequence::ToVector()
	{
		return _frame;
	}

	std::string CodonSequence::ToDnaString(GeneticCodeFactory& factory)
	{
		std::stringstream ss;
		for (auto& x : _frame)
		{
			ss << factory.CodonToDnaString(x);
		}
		return ss.str();
	}
	//GeneticCodeFactory class implementation end

	//cDNA class implementation start
	cDNA::~cDNA() {};

									std::string cDNA::DatabaseID() { return _database_id; };
									std::string cDNA::Gene() { return _gene_name; };
									std::string cDNA::TranscriptID() { return _transcript_id; };
									std::string cDNA::RawRnaDataString() { return _raw_rna_data_string; };
									std::string cDNA::FivePrimeUTR() { return _5primeUTR; };
									std::string cDNA::ThreePrimeUTR() { return _3primeUTR; };
					bioutilities::CodonSequence cDNA::MainORF() { return _ORF; };
	   std::vector<bioutilities::CodonSequence> cDNA::Frames() { return _frames; };
	   std::vector<bioutilities::CodonSequence> cDNA::uORFs() { return _uORFs; };
										 size_t cDNA::SumOfuORFs() { return _sum_of_uORFs; };
							std::vector<size_t> cDNA::AataaStartIndexes() { return  _aataaa_start_indexes; };

	void cDNA::CalculateAllORFs()
	{
		std::vector<bioutilities::Codon> uORF_buffer;
		bioutilities::Codon current_genetic_code_unit = bioutilities::Codon(bioutilities::DNA_Codon::TAG,
			bioutilities::RNA_Codon::UAG,
			bioutilities::AA_3Char::Stop,
			bioutilities::AA_1Char::Stop);

		bioutilities::GeneticCodeFactory factory = bioutilities::GeneticCodeFactory();

		bool translation = false;
		for (size_t x = 0; x < _frames.size(); ++x)
		{
			for (size_t y = 0; y < _frames.at(x).SizeInCodons(); ++y)
			{
				current_genetic_code_unit = _frames.at(x).At(y);
				if (current_genetic_code_unit.AA3Char() == bioutilities::AA_3Char::Met)
				{
					translation = true;
					uORF_buffer.push_back(current_genetic_code_unit);
				}

				else if (translation)
				{
					uORF_buffer.push_back(current_genetic_code_unit);
				}

				if ((current_genetic_code_unit.AA3Char() == bioutilities::AA_3Char::Stop) || (y == _frames.at(x).SizeInCodons() - 1))
				{
					translation = false;
					if (!uORF_buffer.empty())
					{
						size_t start_of_uORF_in_frame = (((y + 1) * 3) - (uORF_buffer.size() * 3) + x);  //ORF enumeration starts from 1

						_uORFs.push_back(bioutilities::CodonSequence(uORF_buffer, start_of_uORF_in_frame));
						uORF_buffer.clear();
					}
				}
			};
		}
	}

	void cDNA::CalculateThreeFrames(std::string& raw_sequense, bioutilities::GeneticCodeFactory& factory)
	{
		for (size_t x = 0; x < 3; ++x)
		{
			std::vector<bioutilities::Codon> buffer;
			size_t y = 0;
			for (; y < raw_sequense.length(); y += 3)
			{
				if (raw_sequense.length() < x + y + 3)
					continue;
				buffer.push_back(factory.DnaCodon(raw_sequense.substr(x + y, 3)));
			}
			_frames.push_back(bioutilities::CodonSequence(buffer, 0));
		}
	}

	void cDNA::SortOnlyMicroORFs()
	{
		std::vector<bioutilities::CodonSequence> temp_uORFs;
		for (size_t x = 0; x < _uORFs.size(); ++x)
		{
			if (_uORFs.at(x).Start() < _ORF.Start())
				temp_uORFs.push_back(_uORFs.at(x));

		}
		_uORFs.clear();
		for (size_t x = 0; x < temp_uORFs.size(); ++x)
		{
			_uORFs.push_back(temp_uORFs.at(x));
		}
		_sum_of_uORFs = _uORFs.size();
	}

	void cDNA::SetLongestORF()
	{
		for (auto& x : _uORFs)
		{
			if (_ORF.SizeInCodons() < x.SizeInCodons())
				_ORF = x;
		}
	}

	void cDNA::CalculateUtrRegions(bioutilities::GeneticCodeFactory& factory)
	{
		_5primeUTR = _raw_rna_data_string.substr(0, _ORF.Start());
		_3primeUTR = _raw_rna_data_string.substr(_ORF.End(), _raw_rna_data_string.length());
	}

	void cDNA::FindAATAAASequences()
	{
		std::string aataaa = "AATAAA";
		std::size_t position = _3primeUTR.find(aataaa);
		while (position != std::string::npos)
		{
			_aataaa_start_indexes.push_back(_ORF.End() + position);
			position = _3primeUTR.find(aataaa, position + aataaa.size());
		}
	}
	//cDNA class implementation end
}
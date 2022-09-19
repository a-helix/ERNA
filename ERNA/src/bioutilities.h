#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <format>
#include "splited_string.h"

namespace bioutilities
{
	enum class DNA_Codon
	{
		TTT, TTC, TTA, TTG, CTT, CTC, CTA, CTG,
		ATT, ATC, ATA, ATG, GTT, GTC, GTA, GTG,
		TCT, TCC, TCA, TCG, CCT, CCC, CCA, CCG,
		ACT, ACC, ACA, ACG, GCT, GCC, GCA, GCG,
		TAT, TAC, TAA, TAG, CAT, CAC, CAA, CAG,
		AAT, AAC, AAA, AAG, GAT, GAC, GAA, GAG,
		TGT, TGC, TGA, TGG, CGT, CGC, CGA, CGG,
		AGT, AGC, AGA, AGG, GGT, GGC, GGA, GGG
	};

	enum class RNA_Codon
	{
		UUU, UUC, UUA, UUG, CUU, CUC, CUA, CUG,
		AUU, AUC, AUA, AUG, GUU, GUC, GUA, GUG,
		UCU, UCC, UCA, UCG, CCU, CCC, CCA, CCG,
		ACU, ACC, ACA, ACG, GCU, GCC, GCA, GCG,
		UAU, UAC, UAA, UAG, CAU, CAC, CAA, CAG,
		AAU, AAC, AAA, AAG, GAU, GAC, GAA, GAG,
		UGU, UGC, UGA, UGG, CGU, CGC, CGA, CGG,
		AGU, AGC, AGA, AGG, GGU, GGC, GGA, GGG
	};

	enum class AA_3Char
	{
		Ala, Arg, Asn, Asp, Cys,
		Glu, Gln, Gly, His, Ile,
		Leu, Lys, Met, Phe, Pro,
		Ser, Thr, Trp, Tyr, Val,
		Stop
	};

	enum class AA_1Char
	{
		A, R, N, D, C,
		E, Q, G, H, I,
		L, K, M, F, P,
		S, T, W, Y, V,
		Stop
	};

	class Codon
	{
	public:
		 Codon() = delete;
		 explicit Codon(DNA_Codon dna_codon,
						RNA_Codon rna_codon,
						AA_3Char aa_3char,
						AA_1Char aa_1char);
		 virtual ~Codon();

		DNA_Codon DnaCodon();
		RNA_Codon RnaCodon();
		AA_3Char AA3Char();
		AA_1Char AA1Char();
		bool operator==(Codon& rhs);

	protected:
		DNA_Codon _dna_codon;
		RNA_Codon _rna_codon;
		 AA_3Char _aa_3char;
		 AA_1Char _aa_1char;
	};

	class GeneticCodeFactory
	{
	public:
		explicit GeneticCodeFactory();
		virtual ~GeneticCodeFactory();

		Codon DnaCodon(const std::string& dna_codon);
		Codon RnaCodon(const std::string& rna_codon);
		Codon AA3Char(const std::string& aa_3char);
		Codon AA1Char(const std::string& aa_1char);

		std::string CodonToDnaString(Codon& input);
		std::string CodonToRnaString(Codon& input);
		std::string CodonToAA3CharString(Codon& input);
		std::string CodonToAA1CharString(Codon& input);

	protected:
		std::vector<Codon> _genetic_code_buffer;
		std::unordered_map<std::string, DNA_Codon> _dna_codon_map;
		std::unordered_map<std::string, RNA_Codon> _rna_codon_map;
		std::unordered_map<std::string, AA_3Char> _aa_3char_map;
		std::unordered_map<std::string, AA_1Char> _aa_1char_map;
	};

	class CodonSequence
	{
	public:
		explicit CodonSequence();
		explicit CodonSequence(const std::vector<Codon>& frame, const size_t& start);
		virtual ~CodonSequence();

		size_t SizeInCodons();
		size_t SizeInNucleotides();
		size_t Start();
		size_t End();
		Codon& At(size_t index);
		void PushBack(Codon codon);
		bool operator==(CodonSequence& obj);
		std::vector<Codon> ToVector();
		std::string ToDnaString(GeneticCodeFactory& factory);

	protected:
		std::vector<Codon> _frame;
		size_t _size_in_codones;
		size_t _start;
		size_t _end;
	};

	class cDNA
	{
	public:
		virtual ~cDNA();

					std::string DatabaseID();
					std::string Gene();
					std::string TranscriptID();
					std::string RawRnaDataString();
	 std::vector<CodonSequence> Frames();
				  CodonSequence MainORF();
					std::string FivePrimeUTR();
					std::string ThreePrimeUTR();
	 std::vector<CodonSequence> uORFs();
						 size_t SumOfuORFs();
			std::vector<size_t> AataaStartIndexes();

	protected:
		virtual void AssignSplitedData() = 0;
		void CalculateThreeFrames(std::string& raw_sequense, bioutilities::GeneticCodeFactory& factory);
		void SetLongestORF();
		void CalculateUtrRegions(bioutilities::GeneticCodeFactory& factory);
		void CalculateAllORFs();
		void SortOnlyMicroORFs();
		void FindAATAAASequences();

		//Basic info
	   std::vector<std::string> _delimiter_separated_input;
					std::string _raw_rna_data_string;
					std::string _database_id;
					std::string _gene_name;
					std::string _transcript_id;
		//cDNA structure elements 
		 std::vector<bioutilities::CodonSequence> _frames; // Three posible reading frames
					  bioutilities::CodonSequence _ORF; // Longest uORF
									  std::string _5primeUTR;
									  std::string _3primeUTR;
		//uORFs
		 std::vector<bioutilities::CodonSequence> _uORFs;
										   size_t _sum_of_uORFs;
		//Specific seqences
							  std::vector<size_t> _aataaa_start_indexes; //AATAAA sequences in 3'-UTR
	};
}
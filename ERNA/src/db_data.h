#pragma once

#include "bioutilities.h"
#include <algorithm>

namespace db_data
{
	class WormBaseComplementaryDna : public bioutilities::cDNA
	{
	public:
		explicit WormBaseComplementaryDna(const std::string& input_data, const char& delimiter, bioutilities::GeneticCodeFactory& factory);
		virtual ~WormBaseComplementaryDna();

	protected:
		void AssignSplitedData() override;
	};
}

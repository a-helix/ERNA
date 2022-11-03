#pragma once

#include "bioutilities.hpp"
#include <algorithm>

namespace db_data
{
	class WormBaseRnaComplementaryDna : public bioutilities::cDNA
	{
	public:
		explicit WormBaseRnaComplementaryDna(const std::string& input_data, const char& delimiter, bioutilities::GeneticCodeFactory& factory);

	protected:
		void AssignSplitedData() override;
	};
}

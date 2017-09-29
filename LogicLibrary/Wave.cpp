#include "stdafx.h"
#include "Wave.h"
#include "Machine.h"

namespace LogicLibrary
{
	bool comp(pair i, pair j) {
		return i.first < j.first;
	}

	Wave::Wave()
	{
	}

	Wave::Wave(std::shared_ptr<Machine> machi, std::vector<pair> info) :
		machine(machi),
		createInfo(info),
		infoIndex(0)
	{
		std::sort(createInfo.begin(), createInfo.end(), comp);
	}

	Wave::~Wave()
	{

	}

	void Wave::Update(double time)
	{

		if (infoIndex >= createInfo.size()) 
		{
			return;
		}
		while (time < createInfo[infoIndex].first)
		{
			machine->addAttacker(createInfo[infoIndex].second);
			infoIndex++;
			if (infoIndex == createInfo.size()) break;
		}
	}
}
#pragma once
#include "libh.h"
#include "shd.h"

void Reading(string fname, _SearchTextData& safe_std)
{
	ifstream input;
	size_t pos;
	string line;
	cout << " !!!! START READING INPUT file: " << fname << endl;
	input.open(fname);
	if (input.is_open())
	{
		long k = 0;
		long nn = 0;
		string stroki[numStrokiKvant];
		SearchTextData* _std = new SearchTextData;
		while (getline(input, line))
		{
			_std->stroki[k % numStrokiKvant] = line;
			if ((k + 1) % numStrokiKvant == 0)
			{
				_std->numStroki = k % numStrokiKvant;
				_std->nn = nn;
				safe_std.push(*_std);
				nn++;
				delete _std;
				_std = new  SearchTextData;
			};
			k++;
		}
		if ((k + 1) % numStrokiKvant != 0)
		{
			_std->numStroki = k % numStrokiKvant;
			_std->nn = nn;
			safe_std.push(*_std);
			nn++;
			delete _std;
			_std = new  SearchTextData;
		};
		k++;
	}



	//cout << " GetWorkStroki Stop Thread [" << name() << "] Timer" << endl;
	cout << " FINISHED READING INPUT file: " << fname << endl;
	return;
	//system("pause");

}

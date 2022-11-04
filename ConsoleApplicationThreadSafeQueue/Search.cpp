#include "Search.h"

int numQuastionMask(const std::string& mask)
{
	const char questionMark = '?';
	//const char starMark = '*';
	int cols = 0;
	for (size_t i = 0; i < mask.size(); ++i)
	{
		if (mask[i] == questionMark)
		{
			cols++;
		}
	}
	return cols;
}

// ���������� mask � � ��������� � ������� pos, 
//������� ����������� ��������� ��������
int cols_eq_chars(int pos, const std::string& subject, const std::string& mask)
{
	if (pos > subject.length() - mask.length()) return 0;
	//const char questionMark = '?';
	//const char starMark = '*';
	int cols = 0;
	for (size_t i = 0; i < mask.size(); ++i)
	{
		if (mask[i] == subject[i + pos])
		{
			cols++;
		}
	}
	return cols;
}

// ���������� ������� ��������� �����, 0 - ���� �� ���������� � ������
int Col(std::string& subject, const std::string& mask)
{
	int cols = 0;
	int pos = 0;
	int _numQuestionMask = numQuastionMask(mask);
	for (size_t i = 0; i < subject.length() - mask.length(); ++i)
	{
		int num = cols_eq_chars(i, subject, mask);
		if (num == mask.length() - _numQuestionMask) {
			subject = subject.substr(i,mask.length());
			pos = i;
			break;
		}
	}

	return pos;
}

bool match(const std::string& subject, const std::string& mask) {
	const char questionMark = '?';
	const char starMark = '*';

	std::vector<size_t> starIndexes;

	for (size_t i = 0; i < mask.size(); ++i) {
		if (mask[i] == starMark) {
			starIndexes.push_back(i);
		}
	}

	if (starIndexes.empty()) {
		starIndexes.push_back(0);
	}

	std::vector<size_t> starLengthsMax(mask.size(), subject.size());

	for (auto& starIndex : starIndexes) {
		for (size_t i = starIndex + 1; i < mask.size(); ++i) {
			if (mask[i] != starMark) {
				starLengthsMax[starIndex] -= 1;
			}
		}
	}

	std::vector<size_t> starLengths(mask.size(), 0);
	std::vector<size_t> starCountdowns(mask.size(), 0);

	bool matches = false;
	bool carry = false;
	while (!matches && !carry) {
		for (
			;
			(starLengths[starIndexes.front()] <= starLengthsMax[starIndexes.front()]) && !matches;
			starLengths[starIndexes.front()]++
			) {
			matches = true;

			bool starFound = false;
			size_t si = 0;
			size_t mi = 0;
			while (si < subject.size() && mi < mask.size()) {
				if (mask[mi] == questionMark) {
					si++;
					mi++;
					continue;
				}

				if (mask[mi] == starMark) {
					if (starCountdowns[mi] == 0) {
						if (starFound) {
							mi++;
							starFound = false;
						}
						else {
							starCountdowns[mi] = starLengths[mi];
							starFound = true;
						}
					}
					else {
						si++;
						starCountdowns[mi]--;
					}

					continue;
				}

				if (mask[mi] == subject[si]) {
					si++;
					mi++;
					continue;
				}
				else {
					matches = false;
					break;
				}
			}

			//if (si != subject.size()) {
			if (si > subject.size()) {
				matches = false;
			}
			else {
				for (; mi < mask.size(); mi++) {
					if (mask[mi] == starMark) {

					}
					else {
						matches = false;
						break;
					}
				}
			}
		}

		carry = true;
		for (auto& starIndex : starIndexes) {
			if (carry) {
				starLengths[starIndex]++;
				carry = (starLengths[starIndex] > starLengthsMax[starIndexes.front()]);
				if (carry) {
					starLengths[starIndex] = 0;
				}
			}
		}
	}

	return matches;
}

//*******************************************************

void FindSearch(
	string mask,
	SearchTextData _std,
	map_InfoSearchStroki& safe_ResultSearch) {
	for (int k = 0; k < _std.numStroki; k++)
	{
		string line = _std.stroki[k];
		string mask2 = mask;
		if (line.length() < mask.size()) continue;
		int pos = Col(line, mask2);
		if (pos != 0)
		{
			{
				InfoSearchStroka iS;
				iS.pos = pos;
				iS.line = line;  _std.stroki[k];
				iS.num = k + 1 + _std.nn * numStrokiKvant;
				safe_ResultSearch.insert(std::map<int, InfoSearchStroka>::value_type(iS.num, iS));
				std::cerr << "FIND!!! [" << iS.num<< "|"<<line << "] -----------  number stroka.\n";
				//cout << " [pos:" << iS.pos << "][num:"<< iS.num <<"]" << endl;

			}
		}
	}
}


//*********************

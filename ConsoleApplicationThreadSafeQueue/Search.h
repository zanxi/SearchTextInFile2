#pragma once

#include "libh.h"
#include "shd.h"

//*******************************************************
// ������� ����������� ������ �������
int numQuastionMask(const std::string& mask);

// ���������� mask � � ��������� � ������� pos, 
//������� ����������� ��������� ��������
int cols_eq_chars(int pos, const std::string& subject, const std::string& mask);

// ���������� ������� ��������� �����, 0 - ���� �� ���������� � ������
int Col(std::string& subject, const std::string& mask);
bool match(const std::string& subject, const std::string& mask);


void FindSearch(
	string mask,
	SearchTextData _std,
	map_InfoSearchStroki& safe_ResultSearch);


//*******************************************************

#pragma once

#include "libh.h"
#include "shd.h"

//*******************************************************
// считаем колличество знаков вопроса
int numQuastionMask(const std::string& mask);

// сравниваем mask и и подстроку с позиции pos, 
//считаем колличество совпавших символов
int cols_eq_chars(int pos, const std::string& subject, const std::string& mask);

// возвращает позицию вхождения маски, 0 - если не существует в строке
int Col(std::string& subject, const std::string& mask);
bool match(const std::string& subject, const std::string& mask);


void FindSearch(
	string mask,
	SearchTextData _std,
	map_InfoSearchStroki& safe_ResultSearch);


//*******************************************************

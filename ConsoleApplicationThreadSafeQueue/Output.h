#pragma once

#include "libh.h"
#include "shd.h"

void OutPut(string fname, string mask, map_InfoSearchStroki safe_info)
{
	ofstream fout(string("output_") + fname);
	fout << "file: " << fname << " | mask: " << mask << '\n' << endl;
	fout << safe_info.size() << '\n' << endl;
	for (std::map<int, InfoSearchStroka>::iterator it = safe_info.begin(); it != safe_info.end(); ++it)
	{
		//std::cout << it->first << " => " << it->second. << '\n';
		fout << " " << it->second.num << " " << it->second.pos << " " << it->second.line << '\n' << endl;
	}
	fout.close(); // закрываем файл
}


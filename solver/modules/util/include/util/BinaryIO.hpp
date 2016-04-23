
#pragma once
#include <iostream>
#include <fstream>
#include <string>

template <class T>
bool BinaryOut(const std::string& filename,const T& out){
	std::ofstream ofs(filename ,std::ios_base::out | std::ios_base::binary);
	if (!ofs) return false;
	ofs.write((const char*)&out, sizeof(out));
	ofs.close();
	return true;
}

template <class T>
T BinaryIn(const std::string& filename){
	T answer;
	std::ifstream ifs(filename ,std::ios_base::in | std::ios_base::binary);
	if (!ifs) return false;
	ifs.read((char*)&answer,sizeof(answer));
	ifs.close();
	return true;
}

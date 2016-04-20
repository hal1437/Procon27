
#pragma once
#include <iostream>
#include <fstream>
#include <string>

template <class T>
bool BinaryOut(const std::string& filename,const T& out){
	ofstream ofs(filename ,std::ios_base::out | std::ios_base::binary);
	if (!ofs) return false;
	ofs.write((const char*)&out, sizeof(out));
	ofs.close();
	return true;
}

template <class T>
T BinaryIn(const std::string& filename){
	T answer;
	ifstream ifs(filename ,std::ios_base::in | std::ios_base::binary);
	if (!ifs) return false;
	ifs.read((const char*)&answer,sizeof(answer));
	ifs.close();
	return true;
}

#include "stdafx.h"
#include "iostream"     
#include "iterator"    
#include "vector"       
#include "algorithm"  
#include "fstream"    
#include "String"

#pragma once

using namespace std;

#ifndef DRIVERS_H
#define DRIVERS_H
class Drivers
{
public:
	const std::string fileName = "D:\\Documents\\School\\CSC 322 Operating Systems\\Class2\\file\\test3.bin";
	static const unsigned int SectorSize = 65536;
	static const unsigned int TotalSectorsOfMemory = 20;
	static const unsigned int TotalBytesOfMemory = 1310720;
	static const unsigned int TotalWordsOfMemory = 655360;
	static const unsigned int TotalWordsOfSector = 32768;
	static const unsigned int WordSize = 2;
	unsigned char emptyByte = 255; //empty memory is set to 11111111
	std::vector<unsigned char> myvector;
	struct Word {
		unsigned char letter1;
		unsigned char letter2;
	};
	//Word DefineWord(unsigned char letter1, unsigned char letter2);
	Drivers();
	void EraseAllSectors();
	void EraseSector(unsigned int nSectorNr);
	Word ReadWord(unsigned int nAddress);
	void WriteWord(unsigned int wordAddress, Word nWord);
	void Initialize();
	~Drivers();
};

#endif
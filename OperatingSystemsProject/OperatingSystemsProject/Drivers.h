#include "stdafx.h"
#include "iostream"     
#include "iterator"    
#include "vector"       
#include "algorithm"  
#include "fstream"    
#include "String"

#pragma once

#ifndef DRIVERS_H
#define DRIVERS_H
class Drivers
{
public:
	const std::string fileName = "D:\\Documents\\School\\CSC 322 Operating Systems\\Class2\\file\\test3.bin";
	const unsigned int SectorSize = 65536;
	const unsigned int TotalSectorsOfMemory = 20;
	const unsigned int TotalBytesOfMemory = 1310720;
	const unsigned int TotalWordsOfMemory = 655360;
	const unsigned int TotalWordsOfSector = 32768;
	const unsigned int WordSize = 2;
	unsigned char emptyByte = 255; //empty memory is set to 11111111
	std::vector<unsigned char> myvector;
	struct Word {
		unsigned char letter1;
		unsigned char letter2;
	};
	Drivers();
	void CreateMemory();
	void OpenFile();
	void EraseAllSectors();
	void EraseSector(unsigned int nSectorNr);
	void ReadWord(unsigned int nAddress);
	void WriteWord(unsigned int wordAddress, Word nWord);
	void Initialize();

	~Drivers();
};

#endif
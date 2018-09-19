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
	const std::string fileName = "D:\\Documents\\School\\CSC 322 Operating Systems\\Class2\\file\\test2.bin";
	const int SectorSize = 65536;
	const int TotalSectorsOfMemory = 20;
	const int TotalBytesOfMemory = 1310720;
	const int TotalWordsOfMemory = 655360;
	std::vector<unsigned char> myvector;
	struct Word {
		unsigned char letter1;
		unsigned char letter2;
	};
	Drivers();
	//struct Drivers::Word;
	bool TestWordInput(int nAddress);
	bool TestSectorInput(int nSectorNr);
	void OpenFile();
	void SaveFile();
	void EraseAllSectors();
	void EraseSector(int nSectorNr);
	void ReadWord(int nAddress);
	void WriteWord(int nAddress, Word nWord);
	void Initialize();

	~Drivers();
};

#endif
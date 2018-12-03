#include<string>
#include<vector>
#include "Block.h"
#include "Drivers.h"
#pragma once
#ifndef FAT_H
#define FAT_H
class FAT
{
public:
	struct CSC322FILE {
		std::string name;
		unsigned int Sector;
		unsigned int StartBlock;
		unsigned int EndBlock;
		unsigned int TotalBlocks;
		bool Deleted;
		bool Used;
		bool FAT;
	};
	std::vector<CSC322FILE> fileList;
	unsigned int FileLimitPerSector = 10;
	FAT();
	std::vector<Drivers::Word> files;

	void initialize();

	void AddFile(CSC322FILE file);
	std::vector<Drivers::Word> ConvertFilesToVectorWords();
	void LoadFATFromMemory();
	CSC322FILE getCSC322FILE(unsigned int filenumber);
	~FAT();
	Block block;
	Drivers::Word convert_int16_to_word(__int16 __int16_number);
	__int16 convert_word_to_int16(Drivers::Word word);
};
#endif


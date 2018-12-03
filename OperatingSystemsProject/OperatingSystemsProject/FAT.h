#include<string>
#include<vector>
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
	void AddFile(CSC322FILE file);
	void InitializeFAT(CSC322FILE file);
	CSC322FILE getCSC322FILE(unsigned int filenumber);
	~FAT();

};
#endif


#include "stdafx.h"
#include "Drivers.h"
#include "FAT.h"
FAT::FAT()
{
	//initialize files
	//load the files into the FAT
	FAT::CSC322FILE file;
	file.name = "file1";
	file.Sector = 0;
	file.StartBlock = 1;
	file.EndBlock = 3;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = false;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file2;
	file.name = "file2";
	file.Sector = 0;
	file.StartBlock = 4;
	file.EndBlock = 6;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file3;
	file.name = "file3";
	file.Sector = 0;
	file.StartBlock = 7;
	file.EndBlock = 9;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE fileUsed;
	file.name = "UsedBlocks";
	file.Sector = 0;
	file.StartBlock = 10;
	file.EndBlock = 511;
	file.TotalBlocks = 502;
	file.Deleted = false;
	file.Used = false;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE fat1;
	file.name = "fat1";
	file.Sector = 1;
	file.StartBlock = 0;
	file.EndBlock = 0;
	file.TotalBlocks = 1;
	file.Deleted = false;
	file.Used = true;
	file.FAT = true;
	AddFile(file);
}

void FAT::AddFile(CSC322FILE file)
{
	fileList.push_back(file);
}

void FAT::InitializeFAT(CSC322FILE file)
{
	
}

FAT::CSC322FILE FAT::getCSC322FILE(unsigned int filenumber)
{//TODO
	return fileList[0];
}

FAT::~FAT()
{
}

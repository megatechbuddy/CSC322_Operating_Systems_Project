#include "stdafx.h"
#include "FAT.h"
FAT::FAT()
{
	//initialize files
}

void FAT::AddFile(CSC322FILE file)
{
	fileList.push_back(file);
}

FAT::CSC322FILE FAT::getCSC322FILE(unsigned int filenumber)
{//TODO
	return fileList[0];
}

FAT::~FAT()
{
}

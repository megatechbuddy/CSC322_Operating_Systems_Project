//Sean Benson
#include "stdafx.h"
#include "Block.h"
#include "Drivers.h"
#include "FAT.h"
#pragma once
#ifndef MEMORYSTRUCTUREMANAGER_H
#define MEMORYSTRUCTUREMANAGER_H
class MemoryStructureManager
{
public:
	const unsigned int AmountOfBlocks = 512; //unit block
	MemoryStructureManager();
	Block block; 
	std::vector<Drivers::Word> CSC322_fopen(FAT::CSC322FILE fileInformation);
	//opens the specified file
	int CSC322_fclose(FAT::CSC322FILE *stream); //closes the file and cleanup
	void CSC322_fread(std::vector<Drivers::Word> words, size_t nWords); //reads the specified amount of information into memory
	int CSC322_fwrite(void *buffer, size_t nBytes); //Writes count of objects from the given array buffer to the output stream stream.
	int CSC322_fseek(long offset, int origin); //moves the pointer to the files beginning
	long CSC322_ftell(); //Returns the current value of the position indicator of the stream
	int CSC322_remove(const char *path); //removes file
	void CreateMemoryStructure();
	void CreateFileAllocationTables();
	void InitializeAllBlocks();
	void InitializeUnusedBlocks();
	void InitializeTableBlocks();
	void InitializeFileBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	void InitializeTableBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	FAT fat;
	FAT getFAT();
	~MemoryStructureManager();
};

#endif
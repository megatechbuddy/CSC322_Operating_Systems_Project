//Sean Benson
#include "stdafx.h"
#include "Block.h"
#pragma once
#ifndef MEMORYSTRUCTUREMANAGER_H
#define MEMORYSTRUCTUREMANAGER_H
class MemoryStructureManager
{
public:
	const unsigned int AmountOfBlocks = 512; //unit block
	MemoryStructureManager(bool emptySector);
	Block block; 
	struct CSC322FILE {
		string filename;
	};
	CSC322FILE* CSC322_fopen(const char *filename, const char *mode); //opens the specified file
	int CSC322_fclose(CSC322FILE *stream); //closes the file and cleanup
	int CSC322_fread(void *buffer, size_t nBytes, CSC322FILE*stream); //reads the specified amount of information into memory
	int CSC322_fwrite(void *buffer, size_t nBytes, CSC322FILE*stream); //Writes count of objects from the given array buffer to the output stream stream.
	int CSC322_fseek(CSC322FILE *stream, long offset, int origin); //moves the pointer to the files beginning
	long CSC322_ftell(CSC322FILE *stream); //Returns the current value of the position indicator of the stream
	int CSC322_remove(const char *path); //removes file
	void CreateMemoryStructure();
	void CreateFileAllocationTables();
	void InitializeAllBlocks();
	void InitializeUnusedBlocks();
	void InitializeTableBlocks();
	void InitializeFileBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	void InitializeTableBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	~MemoryStructureManager();
};

#endif
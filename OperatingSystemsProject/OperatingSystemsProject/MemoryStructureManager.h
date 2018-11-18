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

	void CreateMemoryStructure();
	void CreateFileAllocationTables();
	void InitializeAllBlocks();
	void InitializeUnusedBlocks();
	void InitializeTableBlocks();
	void InitializeUnusedBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber, unsigned int previousBlockNumber);
	void InitializeFileBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	void InitializeTableBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	~MemoryStructureManager();
};

#endif
//Sean Benson
#include "stdafx.h"
#include "MemoryStructureManager.h"

MemoryStructureManager::MemoryStructureManager()
{
	//if no memory structure here
	//CreateMemoryStructure();

	//Test Block
	Block block(0, 0);
	block.InitializeTailOnBlock();
	block.~Block();

}

void MemoryStructureManager::CreateMemoryStructure()
{
	InitializeTableBlocks();
	InitializeFileBlocks();
	CreateFileAllocationTables();
}

void MemoryStructureManager::InitializeTableBlocks()
{
	InitializeTableBlock(0,0);
}

void MemoryStructureManager::InitializeFileBlocks()
{

}

//TODO: put as child of Block
void MemoryStructureManager::InitializeTableBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{
	//put the table structure in place
	Block block(currentSectorNumber, currentBlockNumber);
	block.InitializeTailOnBlock();
	block.~Block();
}

//TODO: put as child of Block
void MemoryStructureManager::InitializeFileBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{
	//put memory of the original block in the real memory
	Block block(currentSectorNumber, currentBlockNumber);
	block.InitializeTailOnBlock();
	block.~Block();
}

void MemoryStructureManager::CreateFileAllocationTables()
{

}

MemoryStructureManager::~MemoryStructureManager()
{
}

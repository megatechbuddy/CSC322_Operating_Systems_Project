//Sean Benson
#include "stdafx.h"
#include "MemoryStructureManager.h"
#include "Drivers.h"

MemoryStructureManager::MemoryStructureManager(bool emptySector)
{
	//if no memory structure here
	if (emptySector) {
		CreateMemoryStructure();
	}
	

	//Test Block
	//Block block2(0, 1);
	//block2.InitializeTailOnBlock();
	//block2.~Block();
}

void MemoryStructureManager::CreateMemoryStructure()
{
	InitializeAllBlocks(); 
	InitializeTableBlocks();
	CreateFileAllocationTables();
}

void MemoryStructureManager::InitializeAllBlocks()
{
	InitializeUnusedBlocks();
}

void MemoryStructureManager::InitializeUnusedBlocks()
{
	//this traverses 100% of the memory
	for (unsigned int sectorNumber = 0; sectorNumber < Drivers::TotalSectorsOfMemory; sectorNumber++) {
		
		for (unsigned int blockNumber = 0; blockNumber < MemoryStructureManager::AmountOfBlocks; blockNumber++) {
			if (blockNumber != 0) {
				InitializeUnusedBlock(sectorNumber, blockNumber, blockNumber - 1);
				std::cout << "Sector: " << sectorNumber << "Block: " << blockNumber << "\n";
			}
			else {
				InitializeUnusedBlock(sectorNumber, blockNumber, 0); 
				std::cout << "Sector: " << sectorNumber << "Block: " << blockNumber << "\n";
			}
		}
	}
}

//This function makes the an empty table block
void MemoryStructureManager::InitializeUnusedBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber, unsigned int previousBlockNumber)
{
	//put the table structure in place
	block.InitializeBlock(currentSectorNumber, currentBlockNumber, previousBlockNumber);
	block.InitializeTailOnBlock(previousBlockNumber);
	
}

//Puts files in the unused, empty tables
void MemoryStructureManager::InitializeTableBlocks()
{
	//for (unsigned int sectorNumber = 0; sectorNumber < Drivers::TotalSectorsOfMemory; sectorNumber++) {
	//		InitializeTableBlock(sectorNumber, 0);
	//}
}

void MemoryStructureManager::InitializeTableBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{
	//TODO: fill in
	//use InitializeFileBlock

	//point to other table blocks
}

void MemoryStructureManager::InitializeFileBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{
	//put file inside the unused blocks
}

//This function puts files into the empty file allocation table.
void MemoryStructureManager::CreateFileAllocationTables()
{

}

MemoryStructureManager::~MemoryStructureManager()
{
	block.~Block();
}

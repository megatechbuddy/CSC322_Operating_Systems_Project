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

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//opens the specified file
MemoryStructureManager::CSC322FILE* MemoryStructureManager::CSC322_fopen(const char * filename, const char * mode)
{
	return nullptr;
}

//closes the file and cleanup
int MemoryStructureManager::CSC322_fclose(CSC322FILE * stream)
{
	return 0;
}

//reads the specified amount of information into memory
int MemoryStructureManager::CSC322_fread(void * buffer, size_t nBytes, CSC322FILE * stream)
{
	return 0;
}


//Writes count of objects from the given array buffer to the output stream stream.
int MemoryStructureManager::CSC322_fwrite(void *buffer, size_t nBytes, CSC322FILE*stream)
{
	return 0;
}

//moves the pointer to the files beginning
int MemoryStructureManager::CSC322_fseek(CSC322FILE * stream, long offset, int origin)
{
	return 0;
}

//Returns the current value of the position indicator of the stream
long MemoryStructureManager::CSC322_ftell(CSC322FILE * stream)
{
	return 0;
}

//removes file
int MemoryStructureManager::CSC322_remove(const char * path)
{
	return 0;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

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
	//it traverses each sections blocks one by one till the end of the sector then
	//it moves to the next sector, all while putting tails on the blocks.
	for (unsigned int sectorNumber = 0; sectorNumber < Drivers::TotalSectorsOfMemory; sectorNumber++) {
		for (unsigned int blockNumber = 0; blockNumber < MemoryStructureManager::AmountOfBlocks; blockNumber++) {
			if (blockNumber != 0) {
				block.InitializeBlock(sectorNumber, blockNumber, blockNumber + 1);
			}
			else {
				block.InitializeBlock(sectorNumber, blockNumber, 0);
			}
		}
		std::cout << "Sector: " << sectorNumber << "\n";
	}
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

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

MemoryStructureManager::~MemoryStructureManager()
{
	//block.~Block();
}

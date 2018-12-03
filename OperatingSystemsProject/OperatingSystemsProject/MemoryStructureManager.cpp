//Sean Benson
#include "stdafx.h"
#include "MemoryStructureManager.h"

MemoryStructureManager::MemoryStructureManager()
{
	//if no memory structure here
	if (false) {
		CreateMemoryStructure();
	}

	//load the files into the FAT
	FAT::CSC322FILE file;
	file.name = "blabla";
	file.Sector = 0;
	file.StartBlock = 1;
	file.EndBlock = 3;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = false;
	file.FAT = false;
	fat.AddFile(file);

	//Test Block
	//Block block2(0, 1);
	//block2.InitializeTailOnBlock();
	//block2.~Block();
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//opens the specified file
std::vector<Drivers::Word> MemoryStructureManager::CSC322_fopen(FAT::CSC322FILE fileInformation)
{
	//get the files contents into a variable
	std::vector<Drivers::Word> words;
	unsigned int currentBlock = fileInformation.StartBlock;
	for (unsigned int i = 0; i < fileInformation.TotalBlocks; i++) {
		//concatenate data
		std::vector<Drivers::Word> temp = block.GetAllDataWordsFromBlock(fileInformation.Sector,currentBlock);
		words.reserve(temp.size() + words.size());
		words.insert(words.end(), temp.begin(), temp.end());

		//get next block location
		currentBlock = block.GetNextBlockLocationFromTail();
	}
	return words;
}

//closes the file and cleanup
int MemoryStructureManager::CSC322_fclose()
{
	return 0;
}

//reads the specified amount of information into memory
void MemoryStructureManager::CSC322_fread(std::vector<Drivers::Word> words, size_t nWords)
{
	//todo: nwords
	//display files contents onto the screen
	for (unsigned int i = 0; i < words.size(); i++) {
		std::cout << words[0].letter1 << words[0].letter2;
	}
	std::cout << "\n";
	
}

//Writes count of objects from the given array buffer to the output stream stream.
int MemoryStructureManager::CSC322_fwrite(std::vector<Drivers::Word> words, FAT::CSC322FILE fileInformation)
{
	unsigned int currentBlock = fileInformation.StartBlock;
	unsigned int temp = 0;
	//separate vector up into multiple vectors
	std::vector<Drivers::Word> tempWords;
	for (unsigned int i = 0; i < words.size(); i++) {
		tempWords.push_back(words[temp]);
		
		if (temp == block.SizeOfBlock-2) {
			block.PutAllDataWordsInBlock(fileInformation.Sector, currentBlock, tempWords);
			tempWords.clear();
			temp = 0;
			currentBlock++;
		}
		else if (temp < block.SizeOfBlock - 2 && i == words.size()-1) {
			while(temp != block.SizeOfBlock - 2) {
				Drivers::Word tempWord;
				tempWord.letter1 = 255;
				tempWord.letter2 = 255;
				tempWords.push_back(tempWord);
				temp++;
			}
			block.PutAllDataWordsInBlock(fileInformation.Sector, currentBlock, tempWords);
			currentBlock++;
		}
		else {
			temp++;
		}
	}
	return 0;
}

//moves the pointer to the files beginning
int MemoryStructureManager::CSC322_fseek(long offset, int origin)
{
	//TODO: Check if file is apart of FAT.
	//Check to see if the size or offset is messed up.
	bool success = false;
	if (success) {
		return 0;
	}else{
		return 1;
	}
}

//Returns the current value of the position indicator of the stream
long MemoryStructureManager::CSC322_ftell()
{
	return 0;
}

//removes file
int MemoryStructureManager::CSC322_remove(const char * path)
{
	return 0;
}

//------------------------------------------------------------------------------------

FAT MemoryStructureManager::getFAT() {

	return fat;
}

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

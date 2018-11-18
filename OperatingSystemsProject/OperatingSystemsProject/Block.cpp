//Sean Benson
#include "stdafx.h"
#include "Block.h"

Block::Block(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{//TODO: Verify inputs
	this->currentSectorNumber = currentSectorNumber;
	this->currentBlockNumber = currentBlockNumber;
	this->startWordLocation = GetStartLocationOfBlock(currentSectorNumber, currentBlockNumber);
	this->endWordLocation = GetEndLocationOfBlock(currentSectorNumber, currentBlockNumber);
	EraseBlockCompletely();
	InitializeTailOnBlock();
	__int16 num = GetNextBlockLocationFromTail();
	std::cout << "GetNextBlockLocationFromTail __int16 " << num << "\n"; 
}

void Block::EraseBlockCompletely()
{
	for (unsigned int i = startWordLocation; i <= endWordLocation; i++) {
		Drivers::Word word;
		word.letter1 = 1;//TODO:Change 1 to 255
		word.letter2 = 1;
		drivers.WriteWord(i, word);
	}
}

void Block::InitializeTailOnBlock()
{ // The tail on the block has 9 bits that point to block 0 to block 511 in the sector.
	Drivers::Word word;
	__int16 number = 16706;
	word = convert_int16_to_word(number);

	//word.letter1 = 65;//Do something meaningful.
	//word.letter2 = 65;
	drivers.WriteWord(endWordLocation,word);
}

__int16 Block::GetNextBlockLocationFromTail()
{
	Drivers::Word word = drivers.ReadWord(endWordLocation);
	__int16 nextBlockLocationFromTail = convert_word_to_int16(word);
	return nextBlockLocationFromTail;
}

//Gets the location of the first word of the block
unsigned int Block::GetStartLocationOfBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{//TODO: Verify inputs
	unsigned int whereFirstWord = 0;
	whereFirstWord = Drivers::TotalWordsOfSector * currentSectorNumber + SizeOfBlock * currentBlockNumber;
	return whereFirstWord;//returns the starting word of the block
}

//Gets the location of the last word of the block
unsigned int Block::GetEndLocationOfBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{//TODO: Verify inputs
	unsigned int whereFirstWord = 0;
	whereFirstWord = Drivers::TotalWordsOfSector * currentSectorNumber + SizeOfBlock * currentBlockNumber + SizeOfBlock - 1;
	return whereFirstWord;//returns the starting word of the block
}

//convert number to word
//source: https://stackoverflow.com/questions/15035208/how-does-one-access-a-single-byte-of-an-integer
Drivers::Word Block::convert_int16_to_word(__int16 __int16_number)
{//TODO: Verify inputs
	Drivers::Word word;
	word.letter1 = ((__int16_number >> (1 << 3)) & 0xff);
	word.letter2 = ((__int16_number >> (0 << 3)) & 0xff);
	return word;
}

//convert word to number
//source: https://stackoverflow.com/questions/15035208/how-does-one-access-a-single-byte-of-an-integer
//code modified
__int16 Block::convert_word_to_int16(Drivers::Word word)
{//TODO: Verify inputs
	__int16 number;
	unsigned char bytes[] = {word.letter2, word.letter1};
	number = *(int*)(bytes + 0);
	return number;
}

Block::~Block()
{//TODO: make sure everything is deconstructed to prevent memory leaks
	drivers.~Drivers();
}
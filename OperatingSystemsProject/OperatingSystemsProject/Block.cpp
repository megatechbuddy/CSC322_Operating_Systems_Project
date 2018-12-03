//Sean Benson
#include "stdafx.h"
#include "Block.h"

Block::Block()
{//TODO: Verify inputs
	
}

//void Block::SetFileFragment(vector<Drivers::Word> inputFragment)
//{//TODO: make sure check if input vector is the right size
//	for (unsigned int i = startWordLocation; i <= endWordLocation - 1; i++) {
//		drivers.WriteWord(i, inputFragment.at(i));
//	}
//}

//vector<Drivers::Word> Block::GetFileFragment()
//{
//	vector<Drivers::Word> outputFragment;
//	for (unsigned int i = startWordLocation; i <= endWordLocation - 1; i++) {
//		outputFragment.push_back(drivers.ReadWord(i));
//	}
//	return outputFragment;
//}

void Block::EraseBlockCompletely()
{	
	Drivers::Word word;
	word.letter1 = 255;
	word.letter2 = 255;
	StartIO();
	for (unsigned int i = startWordLocation; i <= endWordLocation; i++) {
		
		drivers.WriteWord(i, word);
	}
	StopIO();
}

void Block::StartIO() {
	drivers.StartIO();
}

void Block::StopIO() {
	drivers.StopIO();
}

void Block::InitializeBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber, unsigned int nextBlockNumber)
{
	this->currentSectorNumber = currentSectorNumber;
	this->currentBlockNumber = currentBlockNumber;
	this->startWordLocation = GetStartLocationOfBlock(currentSectorNumber, currentBlockNumber);
	this->endWordLocation = GetEndLocationOfBlock(currentSectorNumber, currentBlockNumber);
	EraseBlockCompletely();
	InitializeTailOnBlock(nextBlockNumber);
}

void Block::InitializeTailOnBlock(unsigned int nextBlockNumber)
{ // The tail on the block has 9 bits that point to block 0 to block 511 in the sector.
	Drivers::Word word;
	__int16 number = nextBlockNumber;
	word = convert_int16_to_word(number);
	word.letter1 = word.letter1 + 186;
	word.letter2 = word.letter2 + 186;
	StartIO();
	drivers.WriteWord(endWordLocation,word);
	StopIO();
}

std::vector<Drivers::Word> Block::GetAllDataWordsFromBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber) {
	//get the block's contents into a variable
	unsigned int startWordLocation = GetStartLocationOfBlock(currentSectorNumber, currentBlockNumber);
	unsigned int endWordLocation = GetEndLocationOfBlock(currentSectorNumber, currentBlockNumber);
	std::vector<Drivers::Word> words;
	StartIO();
	for (unsigned int i = startWordLocation; i < endWordLocation; i++) {
		words.push_back(drivers.ReadWord(i));
	}
	StopIO();
	return words;
}

void Block::PutAllDataWordsInBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber, std::vector<Drivers::Word> words) {
	//get the block's contents into a variable
	unsigned int startWordLocation = GetStartLocationOfBlock(currentSectorNumber, currentBlockNumber);
	unsigned int endWordLocation = GetEndLocationOfBlock(currentSectorNumber, currentBlockNumber);

	StartIO();
	for (unsigned int i = startWordLocation; i < endWordLocation; i++) {
		drivers.WriteWord(i, words[i - startWordLocation]);
	}
	StopIO();
}

__int16 Block::GetNextBlockLocationFromTail(unsigned int currentSectorNumber, unsigned int currentBlockNumber)
{
	unsigned int endWordLocation = GetEndLocationOfBlock(currentSectorNumber, currentBlockNumber);
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
	//drivers.~Drivers();
}
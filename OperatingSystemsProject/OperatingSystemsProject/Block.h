//Sean Benson
#include "Drivers.h"
#pragma once
#ifndef BLOCK_H
#define BLOCK_H
class Block
{
public:
	static const unsigned int SizeOfBlock = 64; //unit words
	unsigned int currentSectorNumber;
	unsigned int currentBlockNumber;
	unsigned int nextBlockNumber;
	unsigned int startWordLocation;
	unsigned int endWordLocation;
	Drivers drivers;
	Block();
	void EraseBlockCompletely();
	void InitializeBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber, unsigned int previousBlockNumber);
	void InitializeTailOnBlock(unsigned int previousBlockNumber);
	__int16 GetNextBlockLocationFromTail();
	unsigned int GetStartLocationOfBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	unsigned int GetEndLocationOfBlock(unsigned int currentSectorNumber, unsigned int currentBlockNumber);
	Drivers::Word convert_int16_to_word(__int16 __int16_number);
	__int16 convert_word_to_int16(Drivers::Word word);
	~Block();
};

#endif



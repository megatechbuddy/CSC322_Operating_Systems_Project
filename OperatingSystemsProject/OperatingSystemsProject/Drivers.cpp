
#include "stdafx.h"
#include "Drivers.h"

Drivers::Drivers()
{
	Initialize();
	Word word;
	word.letter1 = 66;
	word.letter2 = 67;
	WriteWord(0, word);
	WriteWord(3, word);
	//EraseSector(0);
	//EraseAllSectors();
	ReadWord(0);
	ReadWord(3);
}

void Drivers::CreateMemory() {
	std::ofstream outFile;
	outFile.open(fileName, std::ios_base::app);
	for (unsigned int i = 0; i < TotalBytesOfMemory; i++)
	{
		outFile.write(reinterpret_cast<char*>(&emptyByte), 1);
	}
	outFile.close();
	std::cout << "Memory Created\n";	
}

void Drivers::EraseAllSectors() {
	for (unsigned int i = 0; i < TotalSectorsOfMemory; i++)
	{
		EraseSector(i);
	}
	std::cout << "Erased all sectors..\n";
}

void Drivers::EraseSector(unsigned int nSectorNr) {
	if (nSectorNr >= 0 && nSectorNr < TotalSectorsOfMemory) { 
		std::fstream outFile(fileName); //TODO:used too many times
		unsigned int beginning = SectorSize * nSectorNr;
		unsigned int end = SectorSize * nSectorNr + SectorSize;
		outFile.seekp(beginning, std::ios::beg);
		for (unsigned int i = beginning; i < end; i++) //strategically used fstream here instead of using WriteWord for speed because fstream was opened too many times
		{
			outFile.write(reinterpret_cast<char*>(&emptyByte), 1);
		}
		outFile.close();
	}
	else {
		std::cout << "Incorrect input for EraseSector\n";
	}	
}

void Drivers::ReadWord(unsigned int wordAddress) {
	if (wordAddress >= 0 && wordAddress < TotalWordsOfMemory) {
		std::ifstream inFile; //TODO:used too many times
		inFile.open(fileName, std::ios::binary);
		unsigned int beginning = WordSize * wordAddress;
		inFile.seekg(beginning, std::ios::beg);
		char holderVariable;

		inFile.read(&holderVariable,1);
		Word word;
		word.letter1 = (unsigned char)holderVariable;

		inFile.read(&holderVariable, 1);
		word.letter2 = (unsigned char)holderVariable;

		inFile.close();
		std::cout << "Word Binary at " << wordAddress << ": " << word.letter1 << word.letter2 << "\n";
	}
	else {
		std::cout << "Please use a valid wordAddress instead of " << wordAddress << "\n";
	}
}

void Drivers::WriteWord(unsigned int wordAddress, Word nWord) {
	if (wordAddress >= 0 && wordAddress < TotalWordsOfMemory) {
		std::cout << "Writting Word: " << nWord.letter1 << nWord.letter2 << " sectors.  At address: "<< wordAddress<<"\n";
		std::fstream outFile(fileName); //TODO:used too many times
		unsigned int beginning = WordSize * wordAddress;
		outFile.seekp(beginning, std::ios::beg);
		outFile.write(reinterpret_cast<char*>(&nWord.letter1), 1);
		outFile.write(reinterpret_cast<char*>(&nWord.letter2), 1);
		outFile.close();
	} else {
		std::cout << "Please use a valid wordAddress instead of " << wordAddress << "\n";
	}
}

void Drivers::Initialize() {
	std::ifstream ifile(fileName);
	if (ifile) {
		std::cout << "File found at " + fileName << "\n";
		std::cout << "Opening that file now. \n";
	}
	else {
		CreateMemory();
	}
	ifile.close();
}

Drivers::~Drivers()
{
}

//Sean Benson
#include "stdafx.h"
#include "Drivers.h"

Drivers::Drivers()
{
	Initialize();

	//EraseAllSectors();
}

void Drivers::StartIO() {
	file.open(fileName);
}
void Drivers::StopIO() {
	file.close();
}

void Drivers::EraseAllSectors() {
	for (unsigned int i = 0; i < TotalSectorsOfMemory; i++)
	{
		EraseSector(i);
	}
}

void Drivers::EraseSector(unsigned int nSectorNr) {
	if (nSectorNr >= 0 && nSectorNr < TotalSectorsOfMemory) {
		file.open(fileName, ios::out);
		unsigned int beginning = SectorSize * nSectorNr;
		unsigned int end = SectorSize * nSectorNr + SectorSize;
		file.seekp(beginning);
		for (unsigned int i = beginning; i < end; i++)
		{
			file.write(reinterpret_cast<char*>(&emptyByte), 1);
		}
		file.close();
		std::cout << "Erase Sector: "<<nSectorNr<<"\n";
	}
	else {
		std::cout << "Incorrect input for EraseSector\n";
	}
}

void Drivers::WriteWord(unsigned int wordAddress, Word nWord) {
	if (wordAddress >= 0 && wordAddress < TotalWordsOfMemory) {
		unsigned int beginning = WordSize * wordAddress;
		file.seekp(beginning);
		file.write(reinterpret_cast<char*>(&nWord.letter1), 1);
		file.write(reinterpret_cast<char*>(&nWord.letter2), 1);
	}
	else {
		std::cout << "Please use a valid wordAddress instead of " << wordAddress << "\n";
	}
}

Drivers::Word Drivers::ReadWord(unsigned int wordAddress) {
	if (wordAddress >= 0 && wordAddress < TotalWordsOfMemory) {
		unsigned int beginning = WordSize * wordAddress;
		file.seekg(beginning);
		char holderVariable;
		char holderVariable2;
		file.read(&holderVariable, 1);
		Word word;
		//word.letter1 = holderVariable - 138;
		word.letter1 = (unsigned char)holderVariable;
		file.read(&holderVariable2, 1);
		word.letter2 = (unsigned char)holderVariable2;
		return word;
	}
	else {
		Word word;
		word.letter1 = 255;
		word.letter2 = 255;
		//		std::cout << "Please use a valid wordAddress instead of " << wordAddress << "\n";
		return word;
	}
}

void Drivers::Initialize() {
	file.open(fileName);
	if (file) {
		file.close();
		std::cout << "File found at " + fileName << "\n";
		std::cout << "Opening that file now. \n";
	}
	else {
		file.close();
		EraseAllSectors();
	}
}

Drivers::~Drivers()
{
}

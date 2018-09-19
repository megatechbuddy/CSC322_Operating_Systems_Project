#include "stdafx.h"
#include "Drivers.h"

Drivers::Drivers()
{
	Initialize();
	Word word;
	word.letter1 = 66;
	word.letter2 = 67;
	WriteWord(10, word);
	WriteWord(20, word);
	//EraseSector(0);
	//EraseAllSectors();
	ReadWord(10);
	ReadWord(20);
}

/*struct Drivers::Word {
	unsigned char letter1;
	unsigned char letter2;
};*/

bool Drivers::TestWordInput(int nAddress) {//TODO: is it actually a number
	if (nAddress >= 0 && nAddress < TotalWordsOfMemory) {
		return true;
	}
	else {
		std::cout << "Please use a valid nAddress instead of " << nAddress << "\n";
		return false;
	}
}

bool Drivers::TestSectorInput(int nSectorNr) {//TODO: is it actually a number
	if (nSectorNr >= 0 && nSectorNr < TotalSectorsOfMemory) {
		return true;
	}
	else {
		std::cout << "Please use a valid nSectorNr instead of " << nSectorNr << "\n";
		return false;
	}
	return true;
}

void Drivers::OpenFile() {
	//https://stackoverflow.com/questions/4423361/constructing-a-vector-with-istream-iterators and modified their code
	std::ifstream source(fileName, std::ios::binary);
	std::vector<unsigned char> data((std::istreambuf_iterator<char>(source)), std::istreambuf_iterator<char>());
	myvector = data;
}

void Drivers::SaveFile() {
	//https://stackoverflow.com/questions/22876893/how-to-use-ostream-iterator-to-output-result-to-a-newfile and modified their code
	std::ofstream of(fileName);
	std::ostream_iterator<unsigned char> out_it(of, "");
	std::copy(myvector.begin(), myvector.end(), out_it);
}

void Drivers::EraseAllSectors() {
	std::cout << "Erasing all sectors.\n";
	for (int i = 0; i < TotalBytesOfMemory; ++i) myvector[i] = 255;//TODO: Check to see if this works 100% of the time.
	SaveFile();
}

void Drivers::EraseSector(int nSectorNr) {
	if (TestSectorInput(nSectorNr)) {
		int beginning = nSectorNr * SectorSize;
		int end = nSectorNr * SectorSize + SectorSize;
		for (int i = beginning; i < end; ++i) myvector[i] = 255;
		SaveFile();
	}
}

void Drivers::ReadWord(int nAddress) {
	if (TestWordInput(nAddress)) {
		std::vector<unsigned char> v;
		v.push_back(myvector[nAddress * 2]); //Note that a word is two bytes. That is the reason for nAddress * 2.
		v.push_back(myvector[nAddress * 2 + 1]);
		std::string str(v.begin(), v.end());
		std::cout << "Word Binary at " << nAddress << ": " << str << "\n";
	}
}

void Drivers::WriteWord(int nAddress, Word nWord) {
	if (TestWordInput(nAddress)) {
		myvector[nAddress * 2] = nWord.letter1;  //Note that a word is two bytes. That is the reason for nAddress * 2.
		myvector[nAddress * 2 + 1] = nWord.letter2;
		SaveFile();
	}
}

void Drivers::Initialize() {
	std::ifstream ifile(fileName);
	if (ifile) {
		std::cout << "File found at " + fileName << "\n";
		std::cout << "Opening that file now. \n";
		OpenFile();
	}
	else {
		EraseAllSectors();
	}
}

Drivers::~Drivers()
{
}

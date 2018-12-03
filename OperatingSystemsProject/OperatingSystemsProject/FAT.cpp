#include "stdafx.h"
#include "FAT.h"

using namespace std;
FAT::FAT()
{
	//initialize files
	//load the files into the FAT
	FAT::CSC322FILE file;
	file.name = "file1";
	file.Sector = 0;
	file.StartBlock = 1;
	file.EndBlock = 3;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = false;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file2;
	file.name = "file2";
	file.Sector = 0;
	file.StartBlock = 4;
	file.EndBlock = 6;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file3;
	file.name = "file3";
	file.Sector = 0;
	file.StartBlock = 7;
	file.EndBlock = 9;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE fileUsed;
	file.name = "UsedBlocks";
	file.Sector = 0;
	file.StartBlock = 10;
	file.EndBlock = 511;
	file.TotalBlocks = 502;
	file.Deleted = false;
	file.Used = false;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE fat1;
	file.name = "fat1";
	file.Sector = 1;
	file.StartBlock = 0;
	file.EndBlock = 0;
	file.TotalBlocks = 1;
	file.Deleted = false;
	file.Used = true;
	file.FAT = true;
	AddFile(file);

	files = ConvertFilesToVectorWords();

}


void FAT::AddFile(CSC322FILE file)
{
	fileList.push_back(file);
}

std::vector<Drivers::Word> FAT::ConvertFilesToVectorWords()
{
	std::vector<Drivers::Word> words;
	for (unsigned int i = 0; i < fileList.size(); i++) {

		CSC322FILE file = fileList[i];

		//load name into vector
		std::vector<char> data(file.name.begin(), file.name.end());

		while (data.size() < 64) {
			data.push_back(127);
		}
		Drivers::Word temp1;
		for (unsigned int i = 0; i < file.name.size(); i++) {
			
			temp1.letter1 = data[i] - 138;
			temp1.letter2 = data[i + 1] - 138;
			words.push_back(temp1);
		}

		// enter line
		temp1.letter1 = 47;
		temp1.letter2 = 110;
		words.push_back(temp1);

		//load Sector into vector
		__int16 number = file.Sector;
		temp1 = convert_int16_to_word(number);
		words.push_back(temp1);

		//load StartBlock into vector
		number = file.StartBlock;
		temp1 = convert_int16_to_word(number);
		words.push_back(temp1);

		//load EndBlock into vector
		number = file.EndBlock;
		temp1 = convert_int16_to_word(number);
		words.push_back(temp1);

		//load TotalBlocks into vector
		number = file.TotalBlocks;
		temp1 = convert_int16_to_word(number);
		words.push_back(temp1);

		//load Deleted into vector
		
		temp1.letter1 = file.Deleted;
		temp1.letter2 = file.Used;
		words.push_back(temp1);

		//load Used into vector
		//load Fat into vector
		Drivers::Word temp2;
		temp2.letter1 = file.FAT;
		temp2.letter2 = 255;
		words.push_back(temp2);
	}
	return words;
}

void FAT::LoadFATFromMemory()
{

}

FAT::CSC322FILE FAT::getCSC322FILE(unsigned int filenumber)
{//TODO
	return fileList[0];
}


//convert number to word
//source: https://stackoverflow.com/questions/15035208/how-does-one-access-a-single-byte-of-an-integer
Drivers::Word FAT::convert_int16_to_word(__int16 __int16_number)
{//TODO: Verify inputs
	Drivers::Word word;
	word.letter1 = ((__int16_number >> (1 << 3)) & 0xff);
	word.letter2 = ((__int16_number >> (0 << 3)) & 0xff);
	return word;
}

FAT::~FAT()
{
}
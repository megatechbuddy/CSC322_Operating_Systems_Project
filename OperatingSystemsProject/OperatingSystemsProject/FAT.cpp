#include "stdafx.h"
#include "FAT.h"

using namespace std;
FAT::FAT()
{
}

void FAT::initialize()
{
	//initialize files
	//load the files into the FAT
	FAT::CSC322FILE file;
	file.name = "file1";
	file.Sector = 0;
	file.StartBlock = 6;
	file.EndBlock = 8;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file2;
	file.name = "file2";
	file.Sector = 0;
	file.StartBlock = 9;
	file.EndBlock = 11;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE file3;
	file.name = "file3";
	file.Sector = 0;
	file.StartBlock = 12;
	file.EndBlock = 14;
	file.TotalBlocks = 3;
	file.Deleted = false;
	file.Used = true;
	file.FAT = false;
	AddFile(file);

	FAT::CSC322FILE fileUsed;
	file.name = "UsedBlocks";
	file.Sector = 0;
	file.StartBlock = 15;
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
			data.push_back(255);
		}
		Drivers::Word temp1;
		for (unsigned int i = 0; i < data.size(); i++) {
			
			temp1.letter1 = data[i];
			temp1.letter2 = data[i + 1];
			words.push_back(temp1);
			i++;
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
	//get all memory
	std::vector<Drivers::Word> words = block.GetAllDataWordsFromBlock(0, 0);
	std::vector<Drivers::Word> words2 = block.GetAllDataWordsFromBlock(0, 1);
	words.insert(words.end(), words2.begin(), words2.end());
	words2 = block.GetAllDataWordsFromBlock(0, 2);
	words.insert(words.end(), words2.begin(), words2.end());
	words2 = block.GetAllDataWordsFromBlock(0, 3);
	words.insert(words.end(), words2.begin(), words2.end());
	words2 = block.GetAllDataWordsFromBlock(0, 4);
	words.insert(words.end(), words2.begin(), words2.end());
	words2 = block.GetAllDataWordsFromBlock(0, 5);
	words.insert(words.end(), words2.begin(), words2.end());
	words2 = block.GetAllDataWordsFromBlock(0, 6);
	words.insert(words.end(), words2.begin(), words2.end());

	unsigned int pointer = 0;
	for (int i = 0; i < 5; i++) {
		//read in the table
		//use the table
		//load name into vector
		std::vector<Drivers::Word> data;
		std::vector<char> data2;
		for (int j = 0; j < 32; j++) {
			data.push_back(words[pointer]);
			data2.push_back(words[pointer].letter1);
			data2.push_back(words[pointer].letter2);
			pointer++;
		}

		pointer++;
		//load Sector into vector
		Drivers::Word tempWordSector = words[pointer];
		pointer++;

		//load StartBlock into vector
		Drivers::Word tempWordStartBlock = words[pointer];
		pointer++;

		//load EndBlock into vector
		Drivers::Word tempWordEndBlock = words[pointer];
		pointer++;

		//load TotalBlocks into vector
		Drivers::Word tempWordTotalBlocks = words[pointer];
		pointer++;

		//load Deleted into vector
		//load Used into vector
		Drivers::Word tempWordDeletedUsed = words[pointer];
		pointer++;

		//load Fat into vector
		Drivers::Word tempWordLast = words[pointer];
		pointer++;

		CSC322FILE tempFile;
		std::string str(data2.begin(), data2.end());
		tempFile.name = str;
		tempFile.Sector = convert_word_to_int16(tempWordSector);
		tempFile.StartBlock = convert_word_to_int16(tempWordStartBlock);
		tempFile.EndBlock = convert_word_to_int16(tempWordEndBlock);
		tempFile.TotalBlocks = convert_word_to_int16(tempWordTotalBlocks);
		tempFile.Deleted = tempWordDeletedUsed.letter1;
		tempFile.Used = tempWordDeletedUsed.letter2;
		tempFile.FAT = tempWordLast.letter1;
		AddFile(tempFile);
	}
	
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

//convert word to number
//source: https://stackoverflow.com/questions/15035208/how-does-one-access-a-single-byte-of-an-integer
//code modified
__int16 FAT::convert_word_to_int16(Drivers::Word word)
{//TODO: Verify inputs
	__int16 number;
	unsigned char bytes[] = { word.letter2, word.letter1 };
	number = *(int*)(bytes + 0);
	return number;
}

FAT::~FAT()
{
}
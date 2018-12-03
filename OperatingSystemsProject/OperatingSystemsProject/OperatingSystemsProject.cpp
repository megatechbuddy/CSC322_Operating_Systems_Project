// Author: Sean Benson, Pho
#include "stdafx.h"
#include "OperatingSystemsProject.h"

OperatingSystemsProject::OperatingSystemsProject()
{
	Menu();
	system("pause");
}

void OperatingSystemsProject::Menu()
{
	memoryStructureManager.getFAT();
	DisplayInstructions();
	DisplayFiles();
	GiveOptions();
}

void OperatingSystemsProject::DisplayInstructions()
{
	std::cout << "Do Stuff." << "\n";
}

void OperatingSystemsProject::DisplayFiles()
{
	fat = memoryStructureManager.getFAT();

	//writing the file works
	//fwrite, ftell
	std::vector<Drivers::Word> writeWords;
	for (unsigned int i=0; i < 100; i++) {
		Drivers::Word tempWord;
		tempWord.letter1 = 64;
		tempWord.letter2 = 64;
		writeWords.push_back(tempWord);
	}
	memoryStructureManager.CSC322_fwrite(writeWords, fat.getCSC322FILE(0));

	//reading the file works
	int success = memoryStructureManager.CSC322_fseek(fat.getCSC322FILE(0).TotalBlocks,fat.getCSC322FILE(0).StartBlock);
	std::vector<Drivers::Word> words = memoryStructureManager.CSC322_fopen(fat.getCSC322FILE(0));
	memoryStructureManager.CSC322_fread(words, 0);



	//check removing file

	//int success2 = memoryStructureManager.cs
	if (success) {
		//TODO: loop through all files
		std::cout << fat.getCSC322FILE(0).name << "\n";
	}
	else {
		std::cout << "Failed to find files." << "\n";
	}
	
	//TODO
	std::cout << "Find files." << "\n";
}

void OperatingSystemsProject::GiveOptions()
{
	std::cout << "Select File to View" << "\n";
	std::cout << "Select File to Remove" << "\n";

}

OperatingSystemsProject::~OperatingSystemsProject()
{
}

int main()
{
	OperatingSystemsProject operatingSystemsProject;
	return 0;
}
// Author: Sean Benson, Tony Le, Jay Tucker, Phong Nguyen, Justin Nguyen
// Please refer to the document attached with this project!
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
	std::cout << "You can add files and change them with this." << "\n" << "\n";
}

void OperatingSystemsProject::DisplayFiles()
{
	std::cout << "Files:" << "\n";
	fat = memoryStructureManager.getFAT();
	for (int i = 0; i < fat->fileList.size(); i++) {
		FAT::CSC322FILE tempFile = fat->fileList[i];
		std::cout << i << ") " << tempFile.name << "\n";
	}

	std::cout << "\n" << "\n";
}

FAT::CSC322FILE OperatingSystemsProject::ChooseAFile(unsigned int input)
{
	fat = memoryStructureManager.getFAT();
	return fat->fileList[input];
}

void OperatingSystemsProject::GiveOptions()
{
	bool done = false;
	while (!done) {
		std::cout << "0) Select File to View" << "\n";
		std::cout << "1) Start Garbage Collection" << "\n";
		std::cout << "2) Exit" << "\n";
		unsigned int valueGetter = -1;
		std::cin >> valueGetter;
		if (valueGetter == 0) {
			std::cout << "\n";
			DisplayFiles();
			std::cout << "\n";
			std::cout << "Choose a file.\n";
			unsigned int valueGetter2 = -1;
			std::cin >> valueGetter2;
			FAT::CSC322FILE tempFile = ChooseAFile(valueGetter2);
			if (tempFile.Deleted == true) {
			}
			else {
				//is it a fat?
				if (tempFile.FAT == true) {
				}
				else {
					//see if it is a file
					//it is usable
					if (tempFile.Used == true) {
						//display it
						//reading the file works
						std::cout << "File Name: " << tempFile.name << "\n";
						std::vector<Drivers::Word> words = memoryStructureManager.CSC322_fopen(tempFile);
						memoryStructureManager.CSC322_fread(words, 0);
					}
				}
			}
		}
		else if (valueGetter == 1) {
			fat = memoryStructureManager.getFAT();
			for (int i = 0; i < fat->fileList.size(); i++) {
				if (fat->fileList[i].Deleted == true) {
					memoryStructureManager.CSC322_remove(fat->fileList[i]);
				}
			}
			std::cout << "Finished removing garbage.\n";
		}
		else if (valueGetter == 2) {
			//do nothing
			done = true;
		}
	}
}

OperatingSystemsProject::~OperatingSystemsProject()
{
}

int main()
{
	OperatingSystemsProject operatingSystemsProject;
	return 0;
}
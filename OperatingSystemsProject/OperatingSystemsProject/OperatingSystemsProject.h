//#include "stdafx.h"
#include "iostream"     
#include "MemoryStructureManager.h"
#include <string>
#pragma once
#ifndef OPERATINGSYSTEMSPROJECT_H
#define OPERATINGSYSTEMSPROJECT_H
class OperatingSystemsProject
{
public:
	OperatingSystemsProject();
	void Menu();
	void DisplayInstructions();
	void DisplayFiles();
	void GiveOptions();
	~OperatingSystemsProject();
	FAT* fat;
	MemoryStructureManager memoryStructureManager;
	FAT::CSC322FILE ChooseAFile(unsigned int input);
};
#endif

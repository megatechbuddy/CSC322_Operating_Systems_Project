// Author: Sean Benson, Pho
#include "stdafx.h"
#include "iostream"     
#include "MemoryStructureManager.h"

int main()
{
	MemoryStructureManager memoryStructureManager(true);
	memoryStructureManager.~MemoryStructureManager();
	system("pause");
	return 0;
}
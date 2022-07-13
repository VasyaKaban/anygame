#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "ObjectParser.h"

void WriteHelp()
{
	std::cout << "Object Parser convert only Vertex/Texture/Normal type of objects!\n"
		"Use 'look' for watch all objects in queue\n"
		"Use 'start' for start parsing\n"
		"Use 'erase' for deleting objects from queue"<< std::endl;
}

int main()
{
	std::vector<std::string> NamesOfObjects;
	std::string Name;
	WriteHelp();
	bool mustStart = false;
	while (mustStart == false)
	{
		std::getline(std::cin, Name);
		if (Name == "start")
		{
			mustStart = true;
		}
		else if (Name == "look")
		{
			system("cls");
			WriteHelp();
			for (int i = 0; i < NamesOfObjects.size(); i++)
			{
				std::cout <<i<<" "<<NamesOfObjects[i] << std::endl;
			}
		}
		else if (Name == "erase")
		{
			int id;
			std::getline(std::cin, Name);
			for (int i = 0; i < NamesOfObjects.size(); i++)
			{
				if (NamesOfObjects[i] == Name)
				{
					id = i;
					break;
				}
			}
			NamesOfObjects.erase(NamesOfObjects.begin() + id);
			std::cout <<Name<<" was deleted!" << std::endl;
		}
		else
		{
			NamesOfObjects.push_back(Name);
			
		}
	}

	for (int i = 0; i < NamesOfObjects.size(); i++)
	{
		system("cls");
		WriteHelp();
		for (int i = 0; i < NamesOfObjects.size(); i++)
		{
			std::cout << i << " " << NamesOfObjects[i] << std::endl;
		}
	}

	for (int i = 0; i < NamesOfObjects.size(); i++)
	{
		ObjectParserCenter(NamesOfObjects[i]);
	}

	char get;
	get = _getch();
	return 0;
}
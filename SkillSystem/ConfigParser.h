#ifndef CONFIGPARSE_H
#define CONFIGPARSE_H


#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <vector>


class ConfigParse
{
public:
	ConfigParse(){}
	~ConfigParse(){}

	ConfigParse::ConfigParse(std::string sz)
	{
		this->szContent = sz;
	}

	std::string szExtracted;
	std::string szContent;

	void Extract(std::string start, std::string end,bool addIndex);

	std::vector<int> getIds(std::string sZString,std::string Index);

	int getInt();
	std::string getString();
};

#endif
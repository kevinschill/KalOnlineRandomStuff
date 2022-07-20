#include "ConfigParser.h"


void ConfigParse::Extract(std::string start, std::string end,bool addIndex)
{
	this->szExtracted.clear();

	std::size_t startIndex = this->szContent.find( start );

     if( startIndex == std::string::npos )
     {
		 this->szExtracted = "-99";
     }

	 if(addIndex)
     startIndex += start.length();

	 std::string::size_type endIndex = this->szContent.find( end, startIndex );
	 if(addIndex)
		this->szExtracted = this->szContent.substr( startIndex+1, endIndex - startIndex -1);
	 else
		 this->szExtracted = this->szContent.substr( startIndex, endIndex - startIndex );
}
int ConfigParse::getInt()
{
	int ret = std::atoi(this->szExtracted.c_str());
	return ret;
}
std::string ConfigParse::getString()
{
	return this->szExtracted;
}

std::vector<int> ConfigParse::getIds(std::string sZString,std::string Index)
{
	std::vector<int> Result;
	std::string szExtractedd;
	while(sZString.find(",") != std::string::npos)
	{
		std::size_t startIndex = sZString.find( Index.c_str() );
		startIndex += Index.length()+1;

		std::string::size_type endIndex = sZString.find( ",", startIndex );

		szExtractedd = sZString.substr( startIndex, endIndex - startIndex);
		sZString.erase(startIndex,1);
		sZString.erase(endIndex-1,1);
		Result.push_back(std::atoi(szExtractedd.c_str()));
	}
	
	return Result;
}
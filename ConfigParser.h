#pragma once
#include <string>
#include <map>
#include <vector>



/*
//------------------------------------------
//----------------- FORMAT -----------------
//------------------------------------------

key0: value0
key1: value1, value2, value3, ...

// double slash '//' means comment till end of line.
// spaces are ignored EVEN LIKE THIS: "NO SPACE HERE". Sorry no spaces yet :/.
// tabs aswell.
// empty lines are ignored.


// The (DELIM) delimeter is for list content. Changeable.
*/

#define DELIM ','

class ConfigParser{
	std::map<std::string, std::string> map_info;
	std::string file_name;

public:
	ConfigParser(const std::string&);
	~ConfigParser();
	void SetNewFile(const std::string&);
	std::string GetStr(const std::string&);
	double GetDouble(const std::string&);
	unsigned int GetUint(const std::string&);
	int GetInt(const std::string&);
	std::vector<std::string> GetStrVec(const std::string&);
	std::vector<int> GetIntVec(const std::string&);
	std::vector<double> GetDoubleVec(const std::string&);
};

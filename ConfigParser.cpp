#include "ConfigParser.h"
#include <fstream>
#include <iostream>

ConfigParser::ConfigParser(const std::string& file_name){
	SetNewFile(file_name);
}

ConfigParser::~ConfigParser(){
	map_info.clear();
}

//str is modified
static inline void ReplaceSubStrings(std::string& str, const std::string replace_this, const std::string replace_with) {
	size_t i = 0;
	auto sub_str_len = replace_this.length();
	if (sub_str_len == 0)
		return;
	while (true) {
		i = str.find(replace_this, i);
		if (i == std::string::npos)
			break;
		str.replace(i, sub_str_len, replace_with);
	}
}

static inline void SplitLineWithChar(std::vector<std::string>& split_line, const std::string& line, char c) {
	std::string item;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (line[i] == c) {
			split_line.push_back(item);
			item.clear();
			continue;
		}
		item += line[i];
	}
	if (item != "")
		split_line.push_back(item);
}

static inline void SplitLineWithCharToInts(std::vector<int>& split_line, const std::string& line, char c) {
	std::string item;
	for (unsigned i = 0; i < line.length(); i++) {
		if (line[i] == c) {
			split_line.push_back(stoi(item));
			item.clear();
			continue;
		}
		item += line[i];
	}
	if (item != "")
		split_line.push_back(stoi(item));
}

static inline void SplitLineWithCharToDouble(std::vector<double>& split_line, const std::string& line, char c){
	std::string item;
	for (unsigned i = 0; i < line.length(); i++) {
		if (line[i] == c) {
			split_line.push_back(stod(item));
			item.clear();
			continue;
		}
		item += line[i];
	}
	if (item != "")
		split_line.push_back(stod(item));
}

void ConfigParser::SetNewFile(const std::string& file_name) {
	this->file_name = file_name;
	map_info.clear();
	std::ifstream map_info_file(file_name);
	if (!map_info_file.is_open()) {
		std::cerr << "Could not open config file: '" << file_name << "'\n";
		exit(1);
	}
	std::string line;
	std::string var;
	std::string value;
	unsigned int line_num = 0;
	while (getline(map_info_file, line)) {
		line_num++;
		auto comment_idx = line.find("//");
		if (comment_idx != std::string::npos) {
			line = line.substr(0, comment_idx);
		}
		ReplaceSubStrings(line, " ", "");
		ReplaceSubStrings(line, "\t", "");
		if(line == "")
			continue;
		auto i = line.find_first_of(':');
		if (i == std::string::npos || i == 0) {
			std::cerr << "Config Parser Warning: config file ['" << file_name << "'] line " << line_num << ": '" << line << "' didn't parse.\n";
			continue;
		}
		var = line.substr(0, i);
		value = line.substr(i + 1);
		map_info.insert(std::pair<std::string, std::string>(var,value));
	}
	map_info_file.close();

}

std::string ConfigParser::GetStr(const std::string& key) {
	auto info = map_info.find(key);
	if (info == map_info.end()) {
		std::cerr << "Config Parser Error: config file ['" << file_name << "'] has no key: '"<< key << "'\n";
		exit(1);
	}
	return info->second;
}

double ConfigParser::GetDouble(const std::string& key) {
	auto info_str = GetStr(key);
	double info_dbl = std::stod(info_str); // throws exeption if cant convert	
	return info_dbl;
}

unsigned int ConfigParser::GetUint(const std::string& key) {
	auto info_str = GetStr(key);
	unsigned int info_uint = std::stoul(info_str); // throws exeption if cant convert	
	return info_uint;
}

int ConfigParser::GetInt(const std::string& key) {
	auto info_str = GetStr(key);
	int info_int = std::stoi(info_str); // throws exeption if cant convert	
	return info_int;
}

std::vector<std::string> ConfigParser::GetStrVec(const std::string& key) {
	auto info_str = GetStr(key);
	std::vector<std::string> values;
	SplitLineWithChar(values, info_str, DELIM);
	return values;
}

std::vector<int> ConfigParser::GetIntVec(const std::string& key) {
	auto info_str = GetStr(key);
	std::vector<int> values;
	SplitLineWithCharToInts(values, info_str, DELIM);
	return values;
}

std::vector<double> ConfigParser::GetDoubleVec(const std::string& key) {
	auto info_str = GetStr(key);
	std::vector<double> values;
	SplitLineWithCharToDouble(values, info_str, DELIM);
	return values;
}

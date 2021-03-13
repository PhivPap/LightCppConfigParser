#include "ConfigParser.h"
#include <iostream>

int main(){
	ConfigParser main_parser("DemoConfig.cfg");

	auto item0 = main_parser.GetStr("key0");
	std::cout << item0 << std::endl;

	auto items = main_parser.GetDoubleVec("key1");
	for(auto item : items)
		std::cout << item << std::endl;

	auto items_str = main_parser.GetStrVec("list");
	for(auto item_str : items_str)
		std::cout << item_str << std::endl;

}

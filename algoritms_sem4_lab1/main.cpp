#include <iostream>
#include "TreeMap.h"

int main() {
	TreeMap<std::string, int> map = TreeMap<std::string, int>();
	map.insert("width", 10);
	map.insert("height", 25);
	map.insert("border", 80);
	map.insert("padding", 8);
	map.insert("margin", 4);
	map.getKeys()->print();
	std::cout << std::endl;
	map.getValues()->print();
	std::cout << std::endl;
	map.print();
}
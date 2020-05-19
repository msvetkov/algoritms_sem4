#include <iostream>
#include <fstream>
#include "FloydMatrix.h"

int main() {
    std::fstream file;
    file.open("prices.txt", std::ios::in);

    auto* list = new LinkedList<std::string>();

	char c;
	std::string buffer = "";
	while (!file.eof()) {
		c = file.get();
		while (c != '\n' && !file.eof()) {
			buffer += c;
			c = file.get();
		}

		list->insert(buffer);
		buffer = "";
	}
	auto* floydMatrix = new FloydMatrix(list);

	std::cout << "Cities and prices:\n";
	for (size_t i = 0; i < list->length(); i++) {
		std::cout << list->at(i) << std::endl;
	}

	std::string firstCity;
	std::string secondCity;
	std::cout << "Enter first city: ";
	std::cin >> firstCity;
	std::cout << "Enter second city: ";
	std::cin >> secondCity;

	try {
		std::string path = floydMatrix->getPath(firstCity, secondCity);
		std::cout << path;
	} catch (std::invalid_argument e) {
		std::cout << e.what();
	}
}

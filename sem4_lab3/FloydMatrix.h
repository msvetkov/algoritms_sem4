#pragma once

#include <climits>
#include<cstdlib>
#include <sstream>
#include "../algoritms_sem4_lab1/TreeMap.h"
#include "../algoritms_sem4_lab1/LinkedList.h"

class FloydMatrix {
private:
	double** matrix;
	TreeMap<std::string, int>* indexByName;
	TreeMap<int, std::string>* nameByIndex;
	void getPathStr(int indexStart, int indexEnd, int** pre, std::string& path);
	size_t _size;
public:
	FloydMatrix(LinkedList<std::string>* list);

	std::string getPath(std::string& firstCity, std::string& secondCity);

	~FloydMatrix() = default;
};


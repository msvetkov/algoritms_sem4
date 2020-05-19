#include "FloydMatrix.h"

FloydMatrix::FloydMatrix(LinkedList<std::string>* list) {
	this->indexByName = new TreeMap<std::string, int>();
	this->nameByIndex = new TreeMap<int, std::string>();
	size_t cityIndex = 0;
	size_t listLength = list->length();

	for (size_t i = 0; i < listLength; i++) {
		std::string str = list->at(i);

		size_t firstIndex = str.find('-');
		size_t secondIndex = str.find(';', firstIndex + 1); // start search from next position

		std::string firstCity = str.substr(0, firstIndex - 1);
		std::string secondCity = str.substr(firstIndex + 2, secondIndex - firstIndex - 2);

		if (!indexByName->containsKey(firstCity)) {
			indexByName->insert(firstCity, cityIndex);
			nameByIndex->insert(cityIndex, firstCity);
			cityIndex = cityIndex + 1;
		}

		if (!indexByName->containsKey(secondCity)) {
			indexByName->insert(secondCity, cityIndex);
			nameByIndex->insert(cityIndex, secondCity);
			cityIndex = cityIndex + 1;
		}
	}

	this->_size = cityIndex;
	matrix = new double* [cityIndex];

	for (size_t i = 0; i < cityIndex; i++) {
		matrix[i] = new double[cityIndex];
	}

	for (size_t i = 0; i < cityIndex; i++) {
		for (size_t j = 0; j < cityIndex; j++) {
			matrix[i][j] = INT_MAX;
		}
	}

	for (size_t i = 0; i < listLength; i++) {
		int priceFirstToSecond = INT_MAX;
		int priceSecondToFirst = INT_MAX;
		std::string str = list->at(i);

		size_t* indexes = new size_t[4];
		indexes[0] = str.find('-');
		indexes[1] = str.find(';', indexes[0] + 1);
		indexes[2] = str.find(';', indexes[1] + 1);
		indexes[3] = str.length();

		std::string firstCity = str.substr(0, indexes[0] - 1);
		std::string secondCity = str.substr(indexes[0] + 2, indexes[1] - indexes[0] - 2);

		if (str.substr(indexes[1] + 2, indexes[2] - 2 - indexes[1]) != "none") {
			priceFirstToSecond = std::atoi(str.substr(indexes[1] + 2, indexes[2] - 2 - indexes[1]).c_str());
		}

		if (str.substr(indexes[2] + 2, indexes[3] - 1) != "none") {
			priceFirstToSecond = std::atoi(str.substr(indexes[2] + 2, indexes[3] - 2 - indexes[2]).c_str());
		}

		matrix[indexByName->find(firstCity)][indexByName->find(secondCity)] = priceFirstToSecond;
		matrix[indexByName->find(secondCity)][indexByName->find(firstCity)] = priceSecondToFirst;
	}
}

std::string FloydMatrix::getPath(std::string& firstCity, std::string& secondCity) {
	if (!this->indexByName->containsKey(firstCity)) {
		throw std::invalid_argument("First city is not found: " + firstCity);
	}

	if (!this->indexByName->containsKey(secondCity)) {
		throw std::invalid_argument("Second city is not found: " + secondCity);
	}

	int indexStart = this->indexByName->find(firstCity);
	int indexEnd = this->indexByName->find(secondCity);

	int** pre = new int* [this->_size];

	for (size_t i = 0; i < this->_size; i++) {
		pre[i] = new int[this->_size];
		for (size_t j = 0; j < this->_size; j++) {
			pre[i][j] = i;
		}
	}

	for (size_t i = 0; i < this->_size; i++) {
		for (size_t j = 0; j < this->_size; j++) {
			for (size_t g = 0; g < this->_size; g++) {
				if (this->matrix[j][i] + this->matrix[i][g] < this->matrix[j][g]) {
					this->matrix[j][g] = this->matrix[j][i] + this->matrix[i][g];
					pre[j][g] = pre[i][g];
				}
			}
		}
	}

	std::string result;
	if (this->matrix[this->indexByName->find(firstCity)][this->indexByName->find(secondCity)] != INT_MAX) {
		std::ostringstream os;
		os << this->matrix[indexByName->find(firstCity)][indexByName->find(secondCity)];
		std::string coastStr = os.str();
		result = "Coast: " + coastStr + "\nRoute: ";
		getPathStr(indexStart, indexEnd, pre, result);
		result = result.substr(0, result.size() - 4);
	} else {
		result = "Wrong route";
	}
	return result;
}

void FloydMatrix::getPathStr(int indexStart, int indexEnd, int** pre, std::string& path) {
	if (indexStart != indexEnd) {
		this->getPathStr(indexStart, pre[indexStart][indexEnd], pre, path);
	}

	path.append(this->nameByIndex->find(indexEnd) + " => ");
};
#include "PushRelabelMethod.h"

PushRelabelMethod::PushRelabelMethod(std::string path) {
	std::fstream file;
	file.open(path, std::ios::in);

	TreeMap<char, int>* topsIndexes = new TreeMap<char, int>();
	this->topCount = 0;
	while (!file.eof()) {
		std::string str;
		char c;
		c = file.get();
		while (c != '\n' && !file.eof()) {
			str += c;
			c = file.get();
		}

		if (str.length() >= 5) {
			if (
				!((str[0] >= 'A' && str[0] <= 'Z') && (str[1] == ' '))
				|| !((str[2] >= 'A' && str[2] <= 'Z') && (str[3] == ' '))
			) {
				throw std::invalid_argument("Wrong data format");
			}

			if (!topsIndexes->containsKey(str[0])) {
				topsIndexes->insert(str[0], this->topCount);
				this->topCount++;
			}

			if (!topsIndexes->containsKey(str[2])) {
				topsIndexes->insert(str[2], this->topCount);
				this->topCount++;
			}
		} else {
			throw std::invalid_argument("Wrong data format");
		}
	}

	if (topsIndexes->containsKey('S')) {
		this->sourceTop = topsIndexes->find('S');
	} else {
		throw std::exception("Source is missing");
	}

	if (topsIndexes->containsKey('T')) {
		this->targetTop = topsIndexes->find('T');
	} else {
		throw std::exception("Target is missing");
	}


	this->flowArray = new int[this->topCount];
	this->height = new int[this->topCount];
	this->capacity = new int* [this->topCount];

	for (int i = 0; i < this->topCount; i++) {
		this->flowArray[i] = 0;
		this->height[i] = 0;
	}

	for (int i = 0; i < this->topCount; i++) {
		this->capacity[i] = new int[topCount];
		for (int j = 0; j < this->topCount; j++) {
			capacity[i][j] = 0;
		}
	}


	file.close();
	file.open(path, std::ios::in);

	while (!file.eof()) {
		std::string str;
		char c;
		c = file.get();
		while (c != '\n' && !file.eof()) {
			str += c;
			c = file.get();
		}

		int firstTop = topsIndexes->find(str[0]);
		int secondTop = topsIndexes->find(str[2]);

		if (firstTop == secondTop) {
			throw std::runtime_error("Graph is in loop");
		}
		this->capacity[firstTop][secondTop] = std::atoi(str.substr(4).c_str());
	}

	file.close();
}

int PushRelabelMethod::getMaxFlow() {
	if (this->topCount < 3) {
		return this->capacity[0][1];
	}

	for (int i = 0; i < this->topCount; i++) {
		if (i != this->sourceTop) {
			this->flowArray[i] = this->capacity[sourceTop][i];
			this->capacity[i][sourceTop] += this->capacity[sourceTop][i];
		}
	}

	this->height[sourceTop] = this->topCount;

	LinkedList<int>* list = new LinkedList<int>();
		
	for (int i = 0; i < this->topCount; i++) {
		if (i != this->sourceTop && i != this->targetTop) {
			list->insertFront(i);
		}
	}
	size_t currentIndex = 0;
	int current = list->at(0);
	while (currentIndex < list->length()) {
		int oldHeight = this->height[current];
		this->discharge(current);
		if (this->height[current] != oldHeight) {
			list->insertFront(current);
			list->remove(currentIndex + 1);
			currentIndex = 0;
			current = list->at(0);
		}
		currentIndex++;
		if (currentIndex < list->length()) {
			current = list->at(currentIndex);
		}
	}
	return this->flowArray[targetTop];
}

void PushRelabelMethod::lift(int edge) {
	int min = 2 * this->topCount + 1;

	for (int i = 0; i < this->topCount; i++) {
		if (this->capacity[edge][i] && (this->height[i] < min)) {
			min = this->height[i];
		}
	}

	this->height[edge] = min + 1;
}

void PushRelabelMethod::push(int edge, int top) {
	int inserting = (this->flowArray[edge] > this->capacity[edge][top])
		? this->capacity[edge][top]
		: this->flowArray[edge];
	this->capacity[edge][top] -= inserting;
	this->capacity[top][edge] += inserting;
	this->flowArray[edge] -= inserting;
	this->flowArray[top] += inserting;
}

void PushRelabelMethod::discharge(int edge) {
	int top = 0;
	while (this->flowArray[edge] > 0) {
		if (
			this->capacity[edge][top]
			&& this->height[edge] == this->height[top] + 1
		) {
			this->push(edge, top);
			top = 0;
		} else {
			top++;
			if (top == this->topCount) {
				this->lift(edge);
				top = 0;
			}
		}
	}
}

PushRelabelMethod::~PushRelabelMethod() {
	for (int i = 0; i < this->topCount; i++) {
		delete[] this->capacity[i];
	}
	delete[] this->capacity;
	delete[] this->height;
	delete[] this->flowArray;
}

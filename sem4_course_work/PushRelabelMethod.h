#include "../algoritms_sem4_lab1/TreeMap.h"
#include <fstream>

class PushRelabelMethod {
private:
	int* flowArray;
	int** capacity;
	int* height;
	int topCount;
	int sourceTop;
	int targetTop;

	void lift(int edge);
	void push(int edge, int top);
	void discharge(int edge);
public:
	PushRelabelMethod(std::string path);

	int getMaxFlow();

	~PushRelabelMethod();
};


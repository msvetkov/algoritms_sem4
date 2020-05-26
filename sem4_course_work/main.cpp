#include <iostream>
#include "PushRelabelMethod.h"

int main() {
    PushRelabelMethod* method = new PushRelabelMethod("input.txt");
    int maxFlow = method->getMaxFlow();
    std::cout << "Max flow: " << maxFlow << std::endl;
}

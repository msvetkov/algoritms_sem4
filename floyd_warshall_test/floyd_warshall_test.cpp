#include "pch.h"
#include "CppUnitTest.h"

#include "../sem4_lab3/FloydMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace floydwarshalltest {
	TEST_CLASS(floydwarshalltest) {
		LinkedList<std::string>* testList;
	public:
		TEST_METHOD_INITIALIZE(init) {
			testList->insert("London - Berlin; 25; 50");
			testList->insert("Berlin - Rome; 11; none");
			testList->insert("Berlin - Paris; 34; 30");
			testList->insert("Rome - Moscow; none; 15");
			testList->insert("Moscow - Paris; 40; none");
		}
		
		TEST_METHOD(getRoute) {
			FloydMatrix* matrix = new FloydMatrix(testList);
			std::string firstCity = "London";
			std::string secondCity = "Moscow";

			std::string result = matrix->getPath(firstCity, secondCity);
			std::string excepted = "Coast: 76\nRoute: London = > Berlin = > Rome = > Moscow";
			Assert::AreEqual(result, excepted);

			firstCity = "Rome";
			secondCity = "Berlin";
			result = matrix->getPath(firstCity, secondCity);
			excepted = "Wrong route";
			Assert::AreEqual(result, excepted);

			firstCity = "Tokyo";
			try {
				result = matrix->getPath(firstCity, secondCity);
			} catch (std::invalid_argument e) {
				Assert::AreEqual(e.what(), "First city is not found: Tokyo");
			}
		}
	};
}

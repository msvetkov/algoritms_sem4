#include "pch.h"
#include "CppUnitTest.h"
#include "../algoritms_sem4_lab1/TreeMap.h"
//#include "../algoritms_sem4_lab1/TreeMap.cpp"
//#include "../algoritms_sem4_lab1/LinkedList.cpp"
//#include "../algoritms_sem4_lab1/MapNode.cpp"
//#include "../algoritms_sem4_lab1/ListNode.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace maptest {
	TEST_CLASS(maptest) {
		TreeMap<std::string, int> map;

	public:
		TEST_METHOD_INITIALIZE(init) {
			map.insert("width", 10);
			map.insert("height", 25);
			map.insert("border", 80);
			map.insert("padding", 8);
			map.insert("margin", 4);
		}
		
		TEST_METHOD(insert) {
			try {
				map.find("z-index");
			} catch (std::invalid_argument error) {
				Assert::AreEqual(error.what(), "This key doesn't exist");
			}
			map.insert("z-index", 10);
			Assert::AreEqual(map.find("z-index"), 10);
		}

		TEST_METHOD(remove) {
			Assert::AreEqual(map.find("margin"), 4);
			map.remove("margin");
			try {
				map.find("margin");
			} catch (std::invalid_argument error) {
				Assert::AreEqual(error.what(), "This key doesn't exist");
			}
		}

		TEST_METHOD(find) {
			Assert::AreEqual(map.find("margin"), 4);
			try {
				map.find("margin-left");
			} catch (std::invalid_argument error) {
				Assert::AreEqual(error.what(), "This key doesn't exist");
			}
		}

		TEST_METHOD(clear) {
			auto* list = new LinkedList<std::string>();
			/*list->insert("border");
			list->insert("height");
			list->insert("margin");
			list->insert("padding");
			list->insert("width");*/
			Assert::IsFalse(map.getKeys()->equals(list));
			map.clear();
			Assert::IsTrue(map.getKeys()->equals(list));
		}

		TEST_METHOD(getKeys) {
			auto* list = new LinkedList<std::string>();
			Assert::IsFalse(map.getKeys()->equals(list));
			list->insert("border");
			list->insert("height");
			list->insert("margin");
			list->insert("padding");
			list->insert("width");
			Assert::IsTrue(map.getKeys()->equals(list));
		}

		TEST_METHOD(getValues) {
			auto* list = new LinkedList<int>();
			Assert::IsFalse(map.getValues()->equals(list));
			list->insert(80);
			list->insert(25);
			list->insert(4);
			list->insert(8);
			list->insert(10);
			Assert::IsTrue(map.getValues()->equals(list));
		}
	};
}

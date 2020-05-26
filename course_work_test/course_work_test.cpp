#include "pch.h"
#include "CppUnitTest.h"
#include "../sem4_course_work/PushRelabelMethod.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	TEST_CLASS(PushRelabel) {
	public:
		TEST_METHOD(correct_data) {
			PushRelabelMethod* method = new PushRelabelMethod("correct_data.txt");
			int maxFlow = method->getMaxFlow();
			Assert::AreEqual(maxFlow, 12);
		}

		TEST_METHOD(loop_graph) {
			try {
				PushRelabelMethod* method = new PushRelabelMethod("loop_graph.txt");
			} catch (std::runtime_error& e) {
				Assert::AreEqual(e.what(), "Graph is in loop");
			}
		}

		TEST_METHOD(two_tops) {
			PushRelabelMethod* method = new PushRelabelMethod("two_tops.txt");
			int maxFlow = method->getMaxFlow();
			Assert::AreEqual(maxFlow, 5);
		}

		TEST_METHOD(missing_letter) {
			try {
				PushRelabelMethod* method = new PushRelabelMethod("missing_letter.txt.txt");
			}
			catch (std::invalid_argument& e) {
				Assert::AreEqual(e.what(), "Wrong data format");
			}
		}
	};
}

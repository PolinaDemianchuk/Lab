#include "pch.h"
#include "CppUnitTest.h"
#include "../Koll_Demianchuk_Polina_variant1/Funcs.h"
#include "../Koll_Demianchuk_Polina_variant1/Funcs.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestFact)
		{
			int n = 5;
			Assert::AreEqual((int)fact(n), 120);
		}

		TEST_METHOD(Testduplicates)
		{
			std::vector<int> arr = { 1, 2, 2, 3, 4, 3 };

			std::vector<int> afterDuplicate = duplicate(arr,6);

			std::vector<int> expected = { 1, 2, 3, 4 };

			for (size_t i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(afterDuplicate[i], expected[i]);
			}
		}

		TEST_METHOD(TestReverse)
		{
			std::vector<int> arr = { 1, 2, 2, 3, 4, 3 };

			std::vector<int> afterDuplicate = duplicate(arr, 6);

			std::vector<int> expected = { 1, 2, 3, 4 };

			for (size_t i = 0; i < expected.size(); i++)
			{
				Assert::AreEqual(afterDuplicate[i], expected[i]);
			}
		}
	};
}

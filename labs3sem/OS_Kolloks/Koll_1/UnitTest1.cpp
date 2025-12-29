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
			Node* Testnode1 = new Node(7);
			Node* Testnode2 = new Node(1);
			Node* Testnode3 = new Node(8);

			Testnode1->next = Testnode2;
			Testnode2->next = Testnode3;

			Node* Testhead = Testnode1;
			Reverse(Testhead);

			Assert::AreEqual(8, Testhead->data);
			Assert::AreEqual(1, Testhead->next->data);
			Assert::AreEqual(7, Testhead->next->next->data);
		}
	};
}

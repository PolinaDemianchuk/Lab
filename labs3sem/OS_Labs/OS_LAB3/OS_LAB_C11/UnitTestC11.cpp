#include "CppUnitTest.h"
#include "../OS_LAB3_C11/Elements.h"
#include "../OS_LAB3_C11/funcs.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestOSLAB3
{
	TEST_CLASS(UnitTestOSLAB3)
	{
	public:
		TEST_METHOD(ChangeToZeros)
		{
			int arr[5] = { 1, 2, 3, 3, 5 };
			makeElementsZeros(arr, 5, 3);
			int modifiedArr[5] = { 1,2,0,0,5 };
			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(arr[i], modifiedArr[i]);
			}
		}

		TEST_METHOD(Markability)
		{
			int arr[5] = { 1, 0, 0, 2, 0 };

			Assert::IsFalse(IsMarkable(arr, 0));
			Assert::IsTrue(IsMarkable(arr, 1));
			Assert::IsTrue(IsMarkable(arr, 2));
			Assert::IsFalse(IsMarkable(arr, 3));
			Assert::IsTrue(IsMarkable(arr, 4));
		}

	};
}

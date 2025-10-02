#include "pch.h"
#include "CppUnitTest.h"
#include "../OS_LAB2/ArrInfo.h"
#include "../OS_LAB2/functions.h"
#include "../OS_LAB2/functions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestOs2
{
	TEST_CLASS(UnitTestOs2)
	{
	public:	
        TEST_METHOD(TestMinMaxNegative)
        {
            int MinMaxArr[]={11,-2,8,0,9,-3};
            arrInfo info;
            info.size = 6;
            info.arr = MinMaxArr;
            int min = info.min;
            int max = info.max;
            DWORD res = min_max(&info);
            Assert::AreEqual(0, min);
            Assert::AreEqual(11, max);
        }
        TEST_METHOD(TestAverage)
        {
            int AverageArr[]={11,-2,8,0,9,-2};
            arrInfo info;
            info.size = 6;
            info.arr = AverageArr;
            double averagetest = info.average;
            DWORD res = average(&info);
            Assert::AreEqual(4.0, averagetest);
        }
        TEST_METHOD(TestMinMaxPositive)
        {
            int MinMaxArr[] = {11,-2,8,0,9,-3 };
            arrInfo info;
            info.size = 6;
            info.arr = MinMaxArr;
            DWORD res = min_max(&info);
            int min = info.min;
            int max = info.max;
            Assert::AreEqual(-3, min);
            Assert::AreEqual(11, max);
        }

        TEST_METHOD(TestChanging)
        {
            int MinMaxArr[] = {11,-2,8,0,9,-2};
            int size = 6;
            ChangeMinMaxToAverage(MinMaxArr, size, -2, 11, 4.0);
            int New[] = {4,4,8,0,9,4};
              for (int i = 0; i < size; i++)
              {
                 Assert::AreEqual(New[i], MinMaxArr[i]);
              }
        }
        TEST_METHOD(TestChangingNegative)
        {
            int MinMaxArr[] = {11,-2,8,0,9,-2};
            int size = 6;
            ChangeMinMaxToAverage(MinMaxArr, size, -2, 11, 4.0);
            int New[] = {7,4,8,0,9,9};
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], MinMaxArr[i]);
            }
        }
        TEST_METHOD(TestChangingSingle)
        {
            int MinMaxArr[] = {11};
            int size = 1;
            ChangeMinMaxToAverage(MinMaxArr, size, 11, 11, 5.0);
            int New[] = {5};
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], MinMaxArr[i]);
            }
        }

        TEST_METHOD(TestChangingAllSame)
        {
            int MinMaxArr[] = {2,2,2};
            int size = 1;
            ChangeMinMaxToAverage(MinMaxArr, size, 2, 2, 2.0);
            int New[] = {2,2,2};
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], MinMaxArr[i]);
            }
        }
        TEST_METHOD(TestChangingAverageHasNumbAfterPoint)
        {
            int MinMaxArr[] = {2,0,25};
            int size = 1;
            ChangeMinMaxToAverage(MinMaxArr, size, 0, 25, 3.8);
            int New[] = {2,3,3};
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], MinMaxArr[i]);
            }
        }
        TEST_METHOD(TestPrintNegative)
        {
            int Arr[] = {11,-2,8,0,9,-2};
            int size = 6;
            PrintArr(Arr, size);
            int New[] = {11,-2,8,0,7,-2};
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], Arr[i]);
            }
        }
        TEST_METHOD(TestPrintPositive)
        {
            int Arr[] = { 11,-2,8,0,9,-2 };
            int size = 6;
            PrintArr(Arr, size);
            int New[] = { 11,-2,8,0,9,-2 };
            for (int i = 0; i < size; i++)
            {
                Assert::AreEqual(New[i], Arr[i]);
            }
        }
	};
}

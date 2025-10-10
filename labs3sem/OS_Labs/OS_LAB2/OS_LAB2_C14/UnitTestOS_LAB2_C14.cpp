#include "pch.h"
#include "CppUnitTest.h"
#include "../OS_LAB2_C11/ArrInfo.h"
#include "../OS_LAB2_C11/functions.h"
#include "../OS_LAB2_C11/functions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestOs2
{
    TEST_CLASS(UnitTestOs2)
    {
    public:
        TEST_METHOD(TestAverage)
        {
            int AverageArr[] = { 11,-2,8,0,9,-2 };
            arrInfo info;
            info.size = 6;
            info.arr = AverageArr;
            average(&info);
            double averagetest = info.average;
            Assert::AreEqual(4.0, averagetest);
        }
        TEST_METHOD(TestMinMax)
        {
            int MinMaxArr[] = { 11,-2,8,0,9,-3 };
            arrInfo info;
            info.size = 6;
            info.arr = MinMaxArr;
            min_max(&info);
            int min = info.min;
            int max = info.max;
            Assert::AreEqual(-3, min);
            Assert::AreEqual(11, max);
        }

        TEST_METHOD(TestChanging)
        {
            std::unique_ptr<int[]> ChArr = std::make_unique<int[]>(3);
            ChArr[0] = 11;
            ChArr[1] = 3;
            ChArr[2] = 1;
            ChangeMinMaxToAverage(ChArr, 3, 1, 11, 5.0);
            Assert::AreEqual(5, ChArr[0]);
            Assert::AreEqual(3, ChArr[1]);
            Assert::AreEqual(5, ChArr[2]);
        }
        TEST_METHOD(TestPrint)
        {
            std::unique_ptr<int[]> PrArr = std::make_unique<int[]>(3);
            PrArr[0] = 11;
            PrArr[1] = 3;
            PrArr[2] = 1;
            PrintArr(PrArr, 3);
            Assert::AreEqual(11, PrArr[0]);
            Assert::AreEqual(3, PrArr[1]);
            Assert::AreEqual(1, PrArr[2]);
        }
    };
}

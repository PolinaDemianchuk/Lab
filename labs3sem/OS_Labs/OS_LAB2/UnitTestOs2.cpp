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
        TEST_METHOD(TestMinMax)
        {
            int MinMaxArr[]={11,-2,8,0,9,-3};
            arrInfo info;
            info.size = 6;
            info.arr = MinMaxArr;
            DWORD res = min_max(&info);
            Assert::AreEqual(0, info.min);
            Assert::AreEqual(11, info.max);
        }
        TEST_METHOD(TestAverage)
        {
            int AverageArr[]={11,-2,8,0,9,-2};
            arrInfo info;
            info.size = 6;
            info.arr = AverageArr;
            DWORD res = average(&info);
            Assert::AreEqual(4.0, info.average);
        }
	};
}

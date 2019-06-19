#include "pch.h"
#include "CppUnitTest.h"

#include "../ray-tracing/def.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto test = V(0.0, 0.0, 0.0);
			test.x += 1;
			Assert::AreEqual(test.x, 1,0);
		}
	};
}

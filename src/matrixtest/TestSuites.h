#pragma once

#include "testcommon/utilfns.h"
#include "UnaryOperationTestCases.h"

namespace unaryoperation
{

void TestSuite()
{
	REGISTERTESTCASE(transpose)
	REGISTERTESTCASE(transposeAssignment)

}

}
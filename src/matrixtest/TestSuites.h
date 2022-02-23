#pragma once

#include "testcommon/testmacros.h"
#include "TestCasesUnaryOperation.h"
#include "TestCasesBinaryOperation.h"

namespace unaryoperation
{

void TestSuite()
{
	REGISTERTESTCASE(transpose)
	REGISTERTESTCASE(transposeAssignment)
	REGISTERTESTCASE(minusAndDquared)
	REGISTERTESTCASE(manipfunction)
}

}

namespace binaryoperation
{

void TestSuite()
{
	REGISTERTESTCASE(elementwiseaddition)
	REGISTERTESTCASE(elementwisesubtraction)
	REGISTERTESTCASE(matrixmultiplication)
	REGISTERTESTCASE(compllicatedcalculation)
}

}


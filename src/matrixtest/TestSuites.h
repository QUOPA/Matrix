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
}

}

namespace binaryoperation
{

void TestSuite()
{
	//REGISTERTESTCASE(elementwiseaddition)
	//REGISTERTESTCASE(elementwisesubtraction)
	//REGISTERTESTCASE(matrixmultiplication)
	//REGISTERTESTCASE(compllicatedcalculation)
}

}


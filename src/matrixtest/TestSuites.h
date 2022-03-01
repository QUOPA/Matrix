#pragma once

#include "testcommon/testmacros.h"
#include "TestCasesUnaryOperation.h"
#include "TestCasesBinaryOperation.h"
#include "TestCasesMaskUnaryOperations.h"
#include "TestCasesMaskBinaryOperations.h"
#include "TestCasesScalarOperation.h"

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
	REGISTERTESTCASE(matrixcustommanipulation)

}

}


namespace maskunaryoperations
{

void TestSuite()
{
	REGISTERTESTCASE(createmask)
}


}

namespace maskbinaryoperations
{
	void TestSuite()
	{
		REGISTERTESTCASE(createmaskbybinary)
		REGISTERTESTCASE(matrixmaskboolean)
		REGISTERTESTCASE(booleanandcomparison)
	}
}



namespace scalaroperation
{
	void TestSuite()
	{
		REGISTERTESTCASE(scalararithmetic)
	}

}

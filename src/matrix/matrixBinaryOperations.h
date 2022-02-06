#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixBase.h"

template <typename T, typename Derived>
class myMatrixBase;

template <typename T, typename LhsMatBase, typename RhsMatBase ,int CalcType>
class myMatrixBinary;

template <typename T, typename LhsMatBase, typename RhsMatBase>
class myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>
{
public:
	explicit myMatrixBinary(LhsMatBase* pLhsMat, RhsMatBase* pRhsMat) 
		: m_pLhsMat(pLhsMat), m_pRhsMat(pRhsMat) {}

protected:
	LhsMatBase* m_pLhsMat;
	RhsMatBase* m_pRhsMat;
};

template <typename T, typename LhsMatBase, typename RhsMatBase>
class myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_ADD>
	: public myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>
	, public myMatrixBase<T, myMatrixUnary<T, LhsMatBase, RhsMatBase, BINARY_ADD> >

{

};




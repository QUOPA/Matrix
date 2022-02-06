#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixBase.h"

template <typename T, typename Derived>
class myMatrixBase;

template <typename T, typename InMatBase, int CalcType>
class myMatrixUnary;

template <typename T, typename InMatBase>
class myMatrixUnary<T, InMatBase, UNARY_BASE>
{
public:
	explicit myMatrixUnary(InMatBase* pIn) : m_pInMat(pIn) {}

protected:
	InMatBase* m_pInMat;
};

template <typename T, typename InMatBase>
class myMatrixUnary<T, InMatBase, UNARY_TRANSPOSE> 
	: public myMatrixUnary<T, InMatBase, UNARY_BASE>
	, public myMatrixBase<T, myMatrixUnary<T, InMatBase, UNARY_TRANSPOSE> >
{
public:
	explicit myMatrixUnary(InMatBase* pIn) : myMatrixUnary<T, InMatBase, UNARY_BASE>(pIn) {}

	// read
	inline IdxType getSize() const { return this->m_pInMat->getSize();}
	inline IdxType getRows() const { return this->m_pInMat->getCols(); }
	inline IdxType getCols() const { return this->m_pInMat->getRows(); }

	// write only
	template<typename OtherMat>
	void operator=(const myMatrixBase<T, OtherMat>& rhs)
	{
		if (this->m_pInMat->getRows() != rhs.getCols())
			throw matrix_rangeerror("error in transpose assignment: the number of rows lhs should be the same with the number of columns of rhs");

		if (this->m_pInMat->getCols() != rhs.getRows())
			throw matrix_rangeerror("error in transpose assignment: the number of columns lhs should be the same with the number of rows of rhs");

		for (IdxType c = 0; c < this->m_pInMat->getRows(); ++c)
		{
			for (IdxType r = 0; r < this->m_pInMat->getCols(); ++r)
			{
				*this->m_pInMat->_v(c, r) = *rhs._v(r, c);
			}
		}
	}

protected:
	inline const T* _v(IdxType r, IdxType c) const { return this->m_pInMat->_v(c, r); }
	inline T* _v(IdxType r, IdxType c) { return this->m_pInMat->_v(c, r); }

	template <typename T2, typename Derived2>
	friend class myMatrixBase;

};


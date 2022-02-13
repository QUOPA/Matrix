#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixBase.h"

template <typename T, typename Derived>
class myMatrixBase;

template <typename T, typename InMatDerieved, int CalcType>
class myMatrixUnary;

template <typename T, typename InMatDerieved>
class myMatrixUnary<T, InMatDerieved, UNARY_BASE>
{
public:
	explicit myMatrixUnary(const InMatDerieved & InMat) : m_InMat(InMat) {}
	myMatrixUnary(const myMatrixUnary& InMat) : m_InMat(InMat) {}

protected:
	InMatDerieved m_InMat;
};

template <typename T, typename InMatDerieved>
class myMatrixUnary<T, InMatDerieved, UNARY_TRANSPOSE>
	: public myMatrixUnary<T, InMatDerieved, UNARY_BASE>
	, public myMatrixBase<T, myMatrixUnary<T, InMatDerieved, UNARY_TRANSPOSE> >
{
public:
	explicit myMatrixUnary(const InMatDerieved & InMat) : myMatrixUnary<T, InMatDerieved, UNARY_BASE>(InMat) {}
	myMatrixUnary(const myMatrixUnary& InMat) : myMatrixUnary<T, InMatDerieved, UNARY_BASE> (InMat) {}

	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getCols(); }
	inline IdxType getCols() const { return this->m_InMat.getRows(); }

	// write only
	template<typename OtherMat>
	void operator=(const myMatrixBase<T, OtherMat>& rhs)
	{
		if (this->m_InMat.getRows() != rhs.getCols())
			throw matrix_rangeerror("error in transpose assignment: the number of rows lhs should be the same with the number of columns of rhs");

		if (this->m_InMat.getCols() != rhs.getRows())
			throw matrix_rangeerror("error in transpose assignment: the number of columns lhs should be the same with the number of rows of rhs");

		for (IdxType c = 0; c < this->m_InMat.getRows(); ++c)
		{
			for (IdxType r = 0; r < this->m_InMat.getCols(); ++r)
			{
				this->m_InMat._v(c, r) = rhs._v(r, c);
			}
		}
	}

protected:

	inline const T _v(IdxType r, IdxType c) const { return this->m_InMat._v(c, r); }
	inline T & _v(IdxType r, IdxType c) { return this->m_InMat._v(c, r); }

	template <typename T2, typename Derived2>
	friend class myMatrixBase;

};


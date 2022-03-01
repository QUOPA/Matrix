#pragma once

#include <cmath>
#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixBase.h"

#define MATRIX_UNARY_OPERATION_CLASS_HAT(CalcType)\
template <typename T, typename InMatDerieved>\
class myMatrixUnary<T, InMatDerieved, CalcType>\
	: public myMatrixUnary<T, InMatDerieved, UNARY_BASE>\
	, public myMatrixBase<T, myMatrixUnary<T, InMatDerieved, CalcType> >\
{\
public:\
	explicit myMatrixUnary(InMatDerieved&& InMat)\
		: myMatrixUnary<T, InMatDerieved, UNARY_BASE>(InMat) {}


#define MATRIX_UNARY_OPERATION_CLASS_SHOE \
protected:\
	template <typename T2, typename Derived2>\
	friend class myMatrixBase;\
	template <typename T2, typename InMatDerieved2, int CalcType2>\
	friend class myMatrixUnary;\
	template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>\
	friend class myMatrixBinary;\
};

template <typename T, typename Derived>
class myMatrixBase;

template <typename T, typename InMatDerieved, int CalcType>
class myMatrixUnary;

template <typename T, typename InMatDerieved>
class myMatrixUnary<T, InMatDerieved, UNARY_BASE>
{
public:
	explicit myMatrixUnary(const InMatDerieved & InMat) : m_InMat(InMat) {}
	//explicit myMatrixUnary(const InMatDerieved& InMat) : m_InMat(InMat) {}
	//myMatrixUnary(const myMatrixUnary& InMat) : m_InMat(InMat) {}

protected:
	InMatDerieved m_InMat;
};


// 1. Transpose
MATRIX_UNARY_OPERATION_CLASS_HAT(UNARY_TRANSPOSE)

public:
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
	
MATRIX_UNARY_OPERATION_CLASS_SHOE

// 2. minus
MATRIX_UNARY_OPERATION_CLASS_HAT(UNARY_MINUS)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const { return - this->m_InMat._v(r, c); }

MATRIX_UNARY_OPERATION_CLASS_SHOE



// 3. Squared
MATRIX_UNARY_OPERATION_CLASS_HAT(UNARY_SQUARED)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const 
	{ 
		T tmpVal = this->m_InMat._v(r, c); 
		return tmpVal * tmpVal;
	}

MATRIX_UNARY_OPERATION_CLASS_SHOE

template <typename T, typename InMatDerieved, typename ManipFn>
class myMatrixUnaryManipulate
	: public myMatrixUnary<T, InMatDerieved, UNARY_BASE>
	, public myMatrixBase<T, myMatrixUnaryManipulate<T, InMatDerieved, ManipFn> >
{
public:
	explicit myMatrixUnaryManipulate(InMatDerieved&& InMat, ManipFn Func)
		: myMatrixUnary<T, InMatDerieved, UNARY_BASE>(InMat), m_Func(Func) {}


public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const { return m_Func(this->m_InMat._v(r, c)); }

	ManipFn m_Func;

	template <typename T2, typename Derived2>
	friend class myMatrixBase;
	template <typename T2, typename InMatDerieved2, int CalcType2>
	friend class myMatrixUnary;
	template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>
	friend class myMatrixBinary;
};

template <typename T, typename InMatDerieved, typename InMatrixMask>
class myMatrixUnarySelected
	: public myMatrixUnary<T, InMatDerieved, UNARY_BASE>
	, public myMatrixBase<T, myMatrixUnarySelected<T, InMatDerieved, InMatrixMask> >
{
public:
	explicit myMatrixUnarySelected(InMatDerieved&& InMat, InMatrixMask && InMask)
		: myMatrixUnary<T, InMatDerieved, UNARY_BASE>(InMat), m_InMask(InMask), m_FilteredOut(0) {}

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

	template<typename OtherMat>
	void operator=(const myMatrixBase<T, OtherMat>& rhs)
	{
		if (this->m_InMat.getRows() != rhs.getRows())
			throw matrix_sizematcherror_rows();

		if (this->m_InMat.getCols() != rhs.getCols())
			throw matrix_sizematcherror_cols();

		for (IdxType r = 0; r < this->m_InMat.getRows(); ++r)
		{
			for (IdxType c = 0; c < this->m_InMat.getCols(); ++c)
			{
				if (this->m_InMask._v(r, c) == true)
					this->_v(r, c) = rhs._v(r, c);
			}
		}
	}

protected:
	inline const T _v(IdxType r, IdxType c) const { return this->m_InMask._v(r, c) == true ? this->m_InMat._v(r, c) : 0; }
	inline T& _v(IdxType r, IdxType c) { m_FilteredOut = 0; return this->m_InMask._v(r, c) == true ? this->m_InMat._v(r, c) : m_FilteredOut; }

	InMatrixMask m_InMask;
	T m_FilteredOut;

	template <typename T2, typename Derived2>
	friend class myMatrixBase;
	template <typename T2, typename InMatDerieved2, int CalcType2>
	friend class myMatrixUnary;
	template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>
	friend class myMatrixBinary;
	template <typename T2>
	friend class myMatrix;

};

template <typename T, int OpType, typename InMatDerived>
inline decltype(auto) createUnaryOperation(InMatDerived&& InMat)
{
	return myMatrixUnary<T, InMatDerived, OpType>(std::forward<InMatDerived>(InMat));
}

template <typename T, typename InMatDerived, typename InMatrixMask>
inline decltype(auto) createUnarySelecteOperation(InMatDerived&& InMat, InMatrixMask && InMask)
{
	return myMatrixUnarySelected<T, InMatDerived, InMatrixMask>(std::forward<InMatDerived>(InMat), std::forward<InMatrixMask>(InMask));
}

template <typename T, typename InMatDerived, typename ManipFn>
inline decltype(auto) createUnaryManipulateOperation(InMatDerived&& InMat, ManipFn Func)
{
	return myMatrixUnaryManipulate<T, InMatDerived, ManipFn>(std::forward<InMatDerived>(InMat), Func);
}


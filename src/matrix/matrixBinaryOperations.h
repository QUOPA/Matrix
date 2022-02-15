#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixBase.h"


#define MATRIX_BINARY_OPERATION_CLASS_HAT(CalcType)					\
template <typename T, typename LhsMatBase, typename RhsMatBase>		\
class myMatrixBinary<T, LhsMatBase, RhsMatBase, CalcType>			\
	: public myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>	\
	, public myMatrixBase<T, myMatrixBinary<T, LhsMatBase, RhsMatBase, CalcType> >\
{\
public:\
	explicit myMatrixBinary(LhsMatBase && LhsMat, RhsMatBase && RhsMat) \
		: myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>(LhsMat, RhsMat) { checkException();}

// Write Something Here

#define MATRIX_BINARY_OPERATION_CLASS_SHOE \
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

template <typename T, typename LhsMatBase, typename RhsMatBase ,int CalcType>
class myMatrixBinary;

template <typename T, typename LhsMatBase, typename RhsMatBase>
class myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>
{
public:
	explicit myMatrixBinary(const LhsMatBase & LhsMat, const RhsMatBase & RhsMat) 
		: m_LhsMat(LhsMat), m_RhsMat(RhsMat) {}

protected:
	LhsMatBase m_LhsMat;
	RhsMatBase m_RhsMat;
};


//MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_ADD)

// template <typename T, typename LhsMatBase, typename RhsMatBase>
// class myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_ADD>
// 	: public myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>
// 	, public myMatrixBase<T, myMatrixUnary<T, LhsMatBase, RhsMatBase, BINARY_ADD> >
// {
// public:
// 	explicit myMatrixBinary(LhsMatBase* LhsMat, RhsMatBase* RhsMat)
// 		:myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>(LhsMat, RhsMat) { checkException() }
// 
// public:
// 	// read
// 	inline IdxType getSize() const { this->m_LhsMat.getSize(); }
// 	inline IdxType getRows() const { this->m_LhsMat.getRows(); }
// 	inline IdxType getCols() const { this->m_LhsMat.getCols(); }
// 
// 
// private:
// 	void checkException() 
// 	{
// 		throwIfColsDifferent(m_LhsMat, m_RhsMat);
// 		throwIfRowsDifferent(m_LhsMat, m_RhsMat);
// 	}
// 
// protected:
// 	inline const T* _v(IdxType r, IdxType c) const 
// 	{
// 		return *this->m_LhsMat._v(r, c) + *this->m_RhsMat._v(r, c);  
// 	}
// 
// protected:
// 	template <typename T2, typename Derived2>
// 	friend class myMatrixBase;
//};

// 1. BINARY_ADD
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_ADD)

public:
	// read
	inline IdxType getSize() const { return this->m_RhsMat.getSize(); }
	inline IdxType getRows() const { return this->m_RhsMat.getRows(); }
	inline IdxType getCols() const { return this->m_RhsMat.getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_LhsMat, this->m_RhsMat);
		throwIfRowsDifferent(this->m_LhsMat, this->m_RhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c) + this->m_RhsMat._v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 2. BINARY_SUB
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_SUB)

public:
	// read
	inline IdxType getSize() const { return this->m_RhsMat.getSize(); }
	inline IdxType getRows() const { return this->m_RhsMat.getRows(); }
	inline IdxType getCols() const { return this->m_RhsMat.getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_LhsMat, this->m_RhsMat);
		throwIfRowsDifferent(this->m_LhsMat, this->m_RhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c) - this->m_RhsMat._v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 3. BINARY_MATMUL
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_MATMUL)

public:
	// read
	inline IdxType getSize() const { return this->m_LhsMat.getRows()* this->m_RhsMat.getCols(); }
	inline IdxType getRows() const { return this->m_LhsMat.getRows(); }
	inline IdxType getCols() const { return this->m_RhsMat.getCols(); }

private:
	void checkException()
	{
		throwIfInnerDifferent(this->m_LhsMat, this->m_RhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		T retVal = 0;
		for (IdxType lcrr = 0; lcrr < this->m_LhsMat.getCols(); ++lcrr)
		{
			retVal += this->m_LhsMat._v(r, lcrr) * this->m_RhsMat._v(lcrr, c);
		}
		return retVal; 
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE


// 5. BINARY_EMUL
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_EMUL)

public:
	// read
	inline IdxType getSize() const { return this->m_RhsMat.getSize(); }
	inline IdxType getRows() const { return this->m_RhsMat.getRows(); }
	inline IdxType getCols() const { return this->m_RhsMat.getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_LhsMat, this->m_RhsMat);
		throwIfRowsDifferent(this->m_LhsMat, this->m_RhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c) * this->m_RhsMat._v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 6. BINARY_EDIV
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_EDIV)

public:
	// read
	inline IdxType getSize() const { return this->m_RhsMat.getSize(); }
	inline IdxType getRows() const { return this->m_RhsMat.getRows(); }
	inline IdxType getCols() const { return this->m_RhsMat.getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_LhsMat, this->m_RhsMat);
		throwIfRowsDifferent(this->m_LhsMat, this->m_RhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c)  / this->m_RhsMat._v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

template <typename T, int OpType, typename LhsMatDerived, typename RhsMatDerived>
inline decltype(auto) createBinaryOperation(LhsMatDerived && LhsMat, RhsMatDerived && RhsMat)
{
	return myMatrixBinary<T, LhsMatDerived, RhsMatDerived, OpType>( std::forward<LhsMatDerived>(LhsMat) , std::forward<RhsMatDerived>(RhsMat));
}

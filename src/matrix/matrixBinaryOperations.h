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
	explicit myMatrixBinary(LhsMatBase* pLhsMat, RhsMatBase* pRhsMat)\
		:myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>(pLhsMat, pRhsMat) { checkException();}

// Write Something Here

#define MATRIX_BINARY_OPERATION_CLASS_SHOE \
protected:\
	template <typename T2, typename Derived2>\
	friend class myMatrixBase;\
};



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


//MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_ADD)

// template <typename T, typename LhsMatBase, typename RhsMatBase>
// class myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_ADD>
// 	: public myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>
// 	, public myMatrixBase<T, myMatrixUnary<T, LhsMatBase, RhsMatBase, BINARY_ADD> >
// {
// public:
// 	explicit myMatrixBinary(LhsMatBase* pLhsMat, RhsMatBase* pRhsMat)
// 		:myMatrixBinary<T, LhsMatBase, RhsMatBase, BINARY_BASE>(pLhsMat, pRhsMat) { checkException() }
// 
// public:
// 	// read
// 	inline IdxType getSize() const { this->m_pLhsMat->getSize(); }
// 	inline IdxType getRows() const { this->m_pLhsMat->getRows(); }
// 	inline IdxType getCols() const { this->m_pLhsMat->getCols(); }
// 
// 
// private:
// 	void checkException() 
// 	{
// 		throwIfColsDifferent(m_pLhsMat, m_pRhsMat);
// 		throwIfRowsDifferent(m_pLhsMat, m_pRhsMat);
// 	}
// 
// protected:
// 	inline const T* _v(IdxType r, IdxType c) const 
// 	{
// 		return *this->m_pLhsMat->_v(r, c) + *this->m_pRhsMat->_v(r, c);  
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
	inline IdxType getSize() const { return this->m_pRhsMat->getSize(); }
	inline IdxType getRows() const { return this->m_pRhsMat->getRows(); }
	inline IdxType getCols() const { return this->m_pRhsMat->getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_pLhsMat, this->m_pRhsMat);
		throwIfRowsDifferent(this->m_pLhsMat, this->m_pRhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_pLhsMat->_v(r, c) + this->m_pRhsMat->_v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 2. BINARY_SUB
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_SUB)

public:
	// read
	inline IdxType getSize() const { return this->m_pRhsMat->getSize(); }
	inline IdxType getRows() const { return this->m_pRhsMat->getRows(); }
	inline IdxType getCols() const { return this->m_pRhsMat->getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_pLhsMat, this->m_pRhsMat);
		throwIfRowsDifferent(this->m_pLhsMat, this->m_pRhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_pLhsMat->_v(r, c) - this->m_pRhsMat->_v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 3. BINARY_MATMUL
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_MATMUL)

public:
	// read
	inline IdxType getSize() const { return this->m_pLhsMat->getRows()* this->m_pRhsMat->getCols(); }
	inline IdxType getRows() const { return this->m_pLhsMat->getRows(); }
	inline IdxType getCols() const { return this->m_pRhsMat->getCols(); }

private:
	void checkException()
	{
		throwIfInnerDifferent(this->m_pLhsMat, this->m_pRhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		T retVal = 0;
		for (IdxType lcrr = 0; lcrr < this->m_pLhsMat->getCols(); ++lcrr)
		{
			retVal += this->m_pLhsMat->_v(r, lcrr) * this->m_pRhsMat->_v(lcrr, c);
		}
		return retVal; 
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE


// 5. BINARY_EMUL
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_EMUL)

public:
	// read
	inline IdxType getSize() const { return this->m_pRhsMat->getSize(); }
	inline IdxType getRows() const { return this->m_pRhsMat->getRows(); }
	inline IdxType getCols() const { return this->m_pRhsMat->getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_pLhsMat, this->m_pRhsMat);
		throwIfRowsDifferent(this->m_pLhsMat, this->m_pRhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_pLhsMat->_v(r, c) * this->m_pRhsMat->_v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE

// 6. BINARY_EDIV
MATRIX_BINARY_OPERATION_CLASS_HAT(BINARY_EDIV)

public:
	// read
	inline IdxType getSize() const { return this->m_pRhsMat->getSize(); }
	inline IdxType getRows() const { return this->m_pRhsMat->getRows(); }
	inline IdxType getCols() const { return this->m_pRhsMat->getCols(); }


private:
	void checkException()
	{
		throwIfColsDifferent(this->m_pLhsMat, this->m_pRhsMat);
		throwIfRowsDifferent(this->m_pLhsMat, this->m_pRhsMat);
	}

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_pLhsMat->_v(r, c)  / this->m_pRhsMat->_v(r, c);
	}

MATRIX_BINARY_OPERATION_CLASS_SHOE
#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixBase.h"

template <typename T2, typename Derived2>
class myMatrixBase; 
template <typename T2, typename InMatDerieved2, int CalcType2>
class myMatrixUnary; 
template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>
class myMatrixBinary; 

#define MATRIX_ONESCALAR_OPERATION_CLASS_HAT(CalcType)	\
template <typename T, typename InMatDerived>\
class MatrixOneScalarOperation<T, InMatDerived, CalcType> \
	: public MatrixOneScalarOperation<T, InMatDerived, ONE_SCALAR_BASE>	\
	, public myMatrixBase<T, MatrixOneScalarOperation<T, InMatDerived, CalcType> >\
{\
public:\
	explicit MatrixOneScalarOperation(InMatDerived && InMat, T InScalar) \
		: MatrixOneScalarOperation<T, InMatDerived, ONE_SCALAR_BASE>(InMat, InScalar) { }

// Write Something Here

#define MATRIX_ONESCALAR_OPERATION_CLASS_SHOE \
protected:\
	template <typename T2, typename Derived2>\
	friend class myMatrixBase;\
	template <typename T2, typename InMatDerieved2, int CalcType2>\
	friend class myMatrixUnary;\
	template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>\
	friend class myMatrixBinary;\
};

template <typename T, typename InMatDerived, int CalcType>
class MatrixOneScalarOperation;

template <typename T, typename InMatDerived>
class MatrixOneScalarOperation<T, InMatDerived, BINARY_BASE>
{
public:
	explicit MatrixOneScalarOperation(const InMatDerived& InMat, T inScalar)
		: m_InMat(InMat), m_InScalar(inScalar) {}

protected:
	InMatDerived m_InMat;
	T m_InScalar;
};

// 1. ONE_SCALAR_ADD
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_ADD)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InMat._v(r, c) + this->m_InScalar;
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE

// 2. ONE_SCALAR_SUB_MLEFT
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_SUB_MLEFT)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InMat._v(r, c) - this->m_InScalar;
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE

// 3. ONE_SCALAR_SUB_MRIGHT
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_SUB_MRIGHT)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InScalar - this->m_InMat._v(r, c);
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE

// 4. ONE_SCALAR_MUL
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_MUL)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InMat._v(r, c)* this->m_InScalar;
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE

// 5. ONE_SCALAR_DIV_MLEFT
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_DIV_MLEFT)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InMat._v(r, c) / this->m_InScalar;
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE

// 6. ONE_SCALAR_MUL
MATRIX_ONESCALAR_OPERATION_CLASS_HAT(ONE_SCALAR_DIV_MRIGHT)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getRows(); }
	inline IdxType getCols() const { return this->m_InMat.getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const
	{
		return this->m_InScalar/ this->m_InMat._v(r, c);
	}

MATRIX_ONESCALAR_OPERATION_CLASS_SHOE


#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixMaskBase.h"

template <typename Derived2>
class MatrixMaskBase;

template <typename InMatDerieved2, int CalcType2>
class MatrixMaskUnary;

template <typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>
class MatrixMaskBinary;

#define MATRIX_MASK_ONESCALAR_OPERATION_CLASS_HAT(CalcType)	\
template <typename InMatDerived, typename Scalar>\
class MatrixMaskOneScalarOperation<InMatDerived, Scalar, CalcType> \
	: public MatrixMaskOneScalarOperation<InMatDerived, Scalar, MASK_ONE_SCALAR_BASE>	\
	, public MatrixMaskBase<MatrixMaskOneScalarOperation<InMatDerived, Scalar, CalcType> >\
{\
public:\
	explicit MatrixMaskOneScalarOperation(InMatDerived && InMat, Scalar InScalar) \
		: MatrixMaskOneScalarOperation<InMatDerived, Scalar, MASK_ONE_SCALAR_BASE>(InMat, InScalar) { }

// Write Something Here

#define MATRIX_MASK_ONESCALAR_OPERATION_CLASS_SHOE \
protected:\
	template <typename Derived2>\
	friend class MatrixMaskBase;\
	template <typename InMatDerieved2, int CalcType2>\
	friend class MatrixMaskUnary;\
	template <typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>\
	friend class MatrixMaskBinary;\
};

#define MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(CalcType, Oper)\
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_HAT(CalcType)\
public:\
inline IdxType getSize() const { return this->m_InMat.getSize(); }\
inline IdxType getRows() const { return this->m_InMat.getRows(); }\
inline IdxType getCols() const { return this->m_InMat.getCols(); }\
protected:\
	inline const bool _v(IdxType r, IdxType c) const {\
		return this->m_InMat._v(r, c) Oper this->m_InScalar; }\
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_SHOE

#define MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MRIGHT(CalcType, Oper)\
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_HAT(CalcType)\
public:\
inline IdxType getSize() const { return this->m_InMat.getSize(); }\
inline IdxType getRows() const { return this->m_InMat.getRows(); }\
inline IdxType getCols() const { return this->m_InMat.getCols(); }\
protected:\
	inline const bool _v(IdxType r, IdxType c) const {\
		return this->m_InScalar Oper this->m_InMat._v(r, c); }\
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_SHOE


template <typename InMatDerived, typename Scalar, int CalcType>
class MatrixMaskOneScalarOperation;

template <typename InMatDerived, typename Scalar>
class MatrixMaskOneScalarOperation<InMatDerived, Scalar, BINARY_BASE>
{
public:
	explicit MatrixMaskOneScalarOperation(const InMatDerived& InMat, Scalar inScalar)
		: m_InMat(InMat), m_InScalar(inScalar) {}

protected:
	InMatDerived m_InMat;
	Scalar m_InScalar;
};

// 1. MASK_ONE_SCALAR_LESS_MLEFT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_LESS_MLEFT, <)

// 2. MASK_ONE_SCALAR_LESS_MRIGHT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MRIGHT(MASK_ONE_SCALAR_LESS_MRIGHT, < )

// 3. MASK_ONE_SCALAR_LEQ_MLEFT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_LEQ_MLEFT, <= )

// 4. MASK_ONE_SCALAR_LEQ_MRIGHT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MRIGHT(MASK_ONE_SCALAR_LEQ_MRIGHT, <= )

// 5. MASK_ONE_SCALAR_GREATER_MLEFT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_GREATER_MLEFT, > )

// 6. MASK_ONE_SCALAR_GREATER_MRIGHT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MRIGHT(MASK_ONE_SCALAR_GREATER_MRIGHT, > )

// 7. MASK_ONE_SCALAR_GEQ_MLEFT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_GEQ_MLEFT, >= )

// 8. MASK_ONE_SCALAR_GEQ_MRIGHT
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MRIGHT(MASK_ONE_SCALAR_GEQ_MRIGHT, >= )

// 9. MASK_ONE_SCALAR_EQUAL
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_EQUAL, == )

// 10. MASK_ONE_SCALAR_NEQ
MATRIX_MASK_ONESCALAR_OPERATION_CLASS_GENERATOR_MLEFT(MASK_ONE_SCALAR_NEQ, != )


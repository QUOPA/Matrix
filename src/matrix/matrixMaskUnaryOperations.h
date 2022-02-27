#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixExceptions.h"
#include "matrix/matrixMaskBase.h"
#include "matrix/matrixUnaryOperations.h"

#define MATRIX_MASK_UNARY_OPERATION_CLASS_HAT(CalcType)\
template <typename InMaskDerieved>\
class MatrixMaskUnary<InMaskDerieved, CalcType>\
	: public MatrixMaskUnary<InMaskDerieved, UNARY_BASE>\
	, public MatrixMaskBase<MatrixMaskUnary<InMaskDerieved, CalcType> >\
{\
public:\
	explicit MatrixMaskUnary(InMaskDerieved&& InMat)\
		: MatrixMaskUnary<InMaskDerieved, UNARY_BASE>(InMat) {}


#define MATRIX_MASK_UNARY_OPERATION_CLASS_SHOE \
protected:\
	template <typename Derived2>\
	friend class MatrixMaskBase;\
	template <typename InMaskDerieved2, int CalcType2>\
	friend class MatrixMaskUnary;\
};

template <typename Derived>
class MatrixMaskBase;

template <typename InMaskDerieved, int CalcType>
class MatrixMaskUnary;

template <typename InMaskDerieved>
class MatrixMaskUnary<InMaskDerieved, MASK_UNARY_BASE>
{
public:
	explicit MatrixMaskUnary(const InMaskDerieved& InMask) : m_InMask(InMask) {}

protected:
	InMaskDerieved m_InMask;
};


// 1. transpose
MATRIX_MASK_UNARY_OPERATION_CLASS_HAT(MASK_UNARY_TRANSPOSE)

public:
	// read
	inline IdxType getSize() const { return this->m_InMat.getSize(); }
	inline IdxType getRows() const { return this->m_InMat.getCols(); }
	inline IdxType getCols() const { return this->m_InMat.getRows(); }

	// write only
	template<typename OtherMat>
	void operator=(const MatrixMaskBase<OtherMat>& rhs)
	{
		if (this->m_InMat.getRows() != rhs.getCols())
			throw matrix_rangeerror("error in transpose assignment: the number of rows lhs should be the same with the number of columns of rhs");

		if (this->m_InMat.getCols() != rhs.getRows())
			throw matrix_rangeerror("error in transpose assignment: the number of columns lhs should be the same with the number of rows of rhs");

		for (IdxType c = 0; c < this->m_InMask.getRows(); ++c)
		{
			for (IdxType r = 0; r < this->m_InMask.getCols(); ++r)
			{
				this->m_InMask._v(c, r) = rhs._v(r, c);
			}
		}
	}

protected:
	inline decltype(auto) _v(IdxType r, IdxType c) const { return this->m_InMat._v(c, r); }
	inline decltype(auto) _v(IdxType r, IdxType c) { return this->m_InMat._v(c, r); }

MATRIX_MASK_UNARY_OPERATION_CLASS_SHOE

// 2. Not
MATRIX_MASK_UNARY_OPERATION_CLASS_HAT(MASK_UNARY_NOT)

public:
	// read
	inline IdxType getSize() const { return this->m_InMask.getSize(); }
	inline IdxType getRows() const { return this->m_InMask.getRows(); }
	inline IdxType getCols() const { return this->m_InMask.getCols(); }

protected:
	inline decltype(auto)  _v(IdxType r, IdxType c) const { return !this->m_InMask._v(r, c); }

MATRIX_MASK_UNARY_OPERATION_CLASS_SHOE

template <int OpType, typename InMaskDerived>
inline decltype(auto) createMaskUnaryOperation(InMaskDerived&& InMask)
{
	return MatrixMaskUnary<InMaskDerived, OpType>(std::forward<InMaskDerived>(InMask));
}



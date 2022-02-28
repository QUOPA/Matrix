#pragma once
#include "matrix/myTypes.h"

#define MATRIX_MASK_BINARY_OPERATION_CLASS_HAT(CalcType)\
template <typename LhsMatDerived, typename RhsMatDerived>		\
class MatrixMaskBinary<LhsMatDerived, RhsMatDerived, CalcType>			\
	: public MatrixMaskBinary<LhsMatDerived, RhsMatDerived, MASK_BINARY_BASE>	\
	, public MatrixMaskBase<MatrixMaskBinary<LhsMatDerived, RhsMatDerived, CalcType> >\
{\
public:\
	explicit MatrixMaskBinary(LhsMatDerived && LhsMat, RhsMatDerived && RhsMat) \
		: MatrixMaskBinary<LhsMatDerived, RhsMatDerived, MASK_BINARY_BASE>(LhsMat, RhsMat) { checkException();}

// Write Something Here

#define MATRIX_MASK_BINARY_OPERATION_CLASS_SHOE \
protected:\
	template <typename T2, typename Derived2>\
	friend class myMatrixBase;\
	template <typename T2, typename InMatDerieved2, int CalcType2>\
	friend class myMatrixUnary;\
	template <typename T2, typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>\
	friend class myMatrixBinary;\
	template <typename Derived2>\
	friend class MatrixMaskBase;\
	template <typename InMatDerieved2, int CalcType2>\
	friend class MatrixMaskUnary;\
	template <typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>\
	friend class MatrixMaskBinary;\
	template <typename T, typename InMatDerieved2, typename InMatrixMask2>\
	friend class myMatrixUnarySelected;\
};

template <typename Derived>
class MatrixMaskBase;

template <typename LhsMatDerived, typename RhsMatDerived, int CalcType>
class MatrixMaskBinary;

template <typename LhsMatDerived, typename RhsMatDerived>
class MatrixMaskBinary<LhsMatDerived, RhsMatDerived, MASK_BINARY_BASE>
{
public:
	explicit MatrixMaskBinary(const LhsMatDerived& LhsMat, const RhsMatDerived& RhsMat)
		: m_LhsMat(LhsMat), m_RhsMat(RhsMat) {}

protected:
	LhsMatDerived m_LhsMat;
	RhsMatDerived m_RhsMat;
};


// 7. BINARY_CMP_LESS
MATRIX_MASK_BINARY_OPERATION_CLASS_HAT(MASK_BINARY_CMP_LESS)

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
	inline const bool _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c) < this->m_RhsMat._v(r, c);
	}

	MATRIX_MASK_BINARY_OPERATION_CLASS_SHOE


// 8. BINARY_CMP_LEQ
MATRIX_MASK_BINARY_OPERATION_CLASS_HAT(MASK_BINARY_CMP_LEQ)

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
	inline const bool _v(IdxType r, IdxType c) const
	{
		return this->m_LhsMat._v(r, c) <= this->m_RhsMat._v(r, c);
	}

MATRIX_MASK_BINARY_OPERATION_CLASS_SHOE

template <int OpType, typename LhsMatDerived, typename RhsMatDerived>
inline decltype(auto) createBinaryMaskOperation(LhsMatDerived&& LhsMat, RhsMatDerived&& RhsMat)
{
	return MatrixMaskBinary<LhsMatDerived, RhsMatDerived, OpType>
		(std::forward<LhsMatDerived>(LhsMat), std::forward<RhsMatDerived>(RhsMat));
}


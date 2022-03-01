#pragma once

#include "matrix/matrixMask.h"
#include "matrix/matrixBase.h"
#include "matrix/matrixMaskBase.h"
#include "matrix/matrixMaskScalarOperations.h"

template <typename Scalar, int OpType, typename InMat>
inline decltype(auto) createMatrixMaskScalarOperation(InMat&& LhsMat, Scalar RhsScalar)
{
	return MatrixMaskOneScalarOperation<InMat, Scalar, OpType>(std::forward<InMat>(LhsMat), RhsScalar);
}

// 1. MASK_ONE_SCALAR_LESS_MLEFT
template<typename T, typename Derived>
const auto operator<(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_LESS_MLEFT>(lhsMat.ref(), rhsScl);
}

// 2 MASK_ONE_SCALAR_LESS_MRIGHT
template<typename T, typename Derived>
const auto operator<(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_LESS_MRIGHT>(lhsMat.ref(), rhsScl);
}

// 3. MASK_ONE_SCALAR_LEQ_MLEFT
template<typename T, typename Derived>
const auto operator<=(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_LEQ_MLEFT>(lhsMat.ref(), rhsScl);
}

// 4 MASK_ONE_SCALAR_LEQ_MRIGHT
template<typename T, typename Derived>
const auto operator<=(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_LEQ_MRIGHT>(lhsMat.ref(), rhsScl);
}

// 5. MASK_ONE_SCALAR_GREATER_MLEFT
template<typename T, typename Derived>
const auto operator>(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_GREATER_MLEFT>(lhsMat.ref(), rhsScl);
}

// 6 MASK_ONE_SCALAR_GREATER_MRIGHT
template<typename T, typename Derived>
const auto operator>(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T , MASK_ONE_SCALAR_GREATER_MRIGHT>(lhsMat.ref(), rhsScl);
}

// 7. MASK_ONE_SCALAR_GEQ_MLEFT
template<typename T, typename Derived>
const auto operator>=(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_GEQ_MLEFT>(lhsMat.ref(), rhsScl);
}

// 8. MASK_ONE_SCALAR_GEQ_MRIGHT
template<typename T, typename Derived>
const auto operator>=(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T , MASK_ONE_SCALAR_GEQ_MRIGHT>(lhsMat.ref(), rhsScl);
}

// 9. MASK_ONE_SCALAR_EQUAL
template<typename T, typename Derived>
const auto operator==(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_EQUAL>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator==(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_EQUAL>(lhsMat.ref(), rhsScl);
}

// 10. MASK_ONE_SCALAR_NEQ
template<typename T, typename Derived>
const auto operator!=(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_NEQ>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator!=(T rhsScl, const myMatrixBase<T, Derived>& lhsMat) {
	return createMatrixMaskScalarOperation<T, MASK_ONE_SCALAR_NEQ>(lhsMat.ref(), rhsScl);
}


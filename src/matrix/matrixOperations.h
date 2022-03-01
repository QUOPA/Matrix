#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixBase.h"
#include "matrix/matrixMaskBase.h"
#include "matrix/matrixScalarOperations.h"

template <typename T, int OpType, typename InMat>
inline decltype(auto) createMatrixScalarOperation(InMat&& LhsMat, T RhsScalar)
{
	return MatrixOneScalarOperation<T, InMat, OpType> (std::forward<InMat>(LhsMat), RhsScalar);
}

// 1. Mat-Scalar add
template<typename T, typename Derived>
const auto operator+(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixScalarOperation<T,ONE_SCALAR_ADD>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator+(T lhsScl, const myMatrixBase<T, Derived>& rhsMat) {
	return createMatrixScalarOperation<T, ONE_SCALAR_ADD>(rhsMat.ref(), lhsScl);
}

// 2-3. Mat - Scalar subtraction
template<typename T, typename Derived>
const auto operator-(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixScalarOperation<T, ONE_SCALAR_SUB_MLEFT>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator-(T lhsScl, const myMatrixBase<T, Derived>& rhsMat) {
	return createMatrixScalarOperation<T, ONE_SCALAR_SUB_MRIGHT>(rhsMat.ref(), lhsScl);
}

// 4. Mat-Scalar Multiplication
template<typename T, typename Derived>
const auto operator*(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixScalarOperation<T, ONE_SCALAR_MUL>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator*(T lhsScl, const myMatrixBase<T, Derived>& rhsMat) {
	return createMatrixScalarOperation<T, ONE_SCALAR_MUL>(rhsMat.ref(), lhsScl);
}

// 5-6. Mat-Scalar Division
template<typename T, typename Derived>
const auto operator/(const myMatrixBase<T, Derived>& lhsMat, T rhsScl) {
	return createMatrixScalarOperation<T, ONE_SCALAR_DIV_MLEFT>(lhsMat.ref(), rhsScl);
}

template<typename T, typename Derived>
const auto operator/(T lhsScl, const myMatrixBase<T, Derived>& rhsMat) {
	return createMatrixScalarOperation<T, ONE_SCALAR_DIV_MRIGHT>(rhsMat.ref(), lhsScl);
}

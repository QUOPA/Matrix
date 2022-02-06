#pragma once

#include <iostream>
#include "matrix/mytypes.h"
#include "matrix/matrixUnaryOperations.h"

template <typename T, typename InMatBase, int CalcType>
class myMatrixUnary;

template <typename T, typename Derived>
class myMatrixBase
{
public:
	// read
	inline IdxType getSize() const { return derived()->getSize(); }
	inline IdxType getRows() const { return derived()->getRows(); }
	inline IdxType getCols() const { return derived()->getCols(); }

	// Operations (read / write)
	inline const auto t() const { return myMatrixUnary<T, const myMatrixBase, UNARY_TRANSPOSE>(this); }
	inline auto t() { return myMatrixUnary<T, myMatrixBase, UNARY_TRANSPOSE>(this); }

	// assingment (non const only)
	template<typename T, typename OtherMat>
	inline void operator=(const myMatrixBase<T, OtherMat>& rhs) { derived()->operator=(*rhs.derived()); }

	inline const T* _v(IdxType r, IdxType c) const { return derived()->_v(r,c); }
	inline T* _v(IdxType r, IdxType c) { return derived()->_v(r, c); }

private:
	inline const Derived* derived() const { return static_cast<const Derived*>(this); }
	inline Derived* derived() { return static_cast<Derived*>(this); }

	template <typename T2, typename Derived2>
	friend std::ostream& operator<<(std::ostream& o, const myMatrixBase<T2, Derived2>& MatIn);

};


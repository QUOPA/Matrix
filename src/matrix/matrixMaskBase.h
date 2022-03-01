#pragma once

#include "matrix/myTypes.h"
#include "matrix/matrixMaskUnaryOperations.h"
#include "matrix/matrixMaskBinaryOperations.h"

template <typename Derived>
class MatrixMaskBase
{
public:
	typedef Derived derivedType;

	/* read only */
	inline IdxType getSize() const { return derived()->getSize(); }
	inline IdxType getRows() const { return derived()->getRows(); }
	inline IdxType getCols() const { return derived()->getCols(); }

	/* Unary Operations */
	
	// 2. bitwise-not
	inline const auto operator!() const { return createMaskUnaryOperation<MASK_UNARY_NOT>(this->ref()); }

	/* Binary Operations  */
	// 1. Elementwise And
	template<typename OtherDerived> inline
		const auto operator&(const MatrixMaskBase<OtherDerived> & rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_AND>(this->ref(), rhs.ref());
	}

	// 2. Elementwise OR
	template<typename OtherDerived> inline
		const auto operator|(const MatrixMaskBase<OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_OR>(this->ref(), rhs.ref());
	}

	// 4. Elementwise XOR
	template<typename OtherDerived> inline
		const auto operator^(const MatrixMaskBase<OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_XOR>(this->ref(), rhs.ref());
	}

	// 5. Elementwise Exclude
	template<typename OtherDerived> inline
		const auto operator-(const MatrixMaskBase<OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_EXCLUDE>(this->ref(), rhs.ref());
	}



	// assingment (non const only)
	template<typename OtherMat>
	inline void operator=(const MatrixMaskBase<OtherMat>& rhs) { derived()->operator=(*rhs.derived()); }

	inline decltype(auto) _v(IdxType r, IdxType c) const { return derived()->_v(r, c); }
	inline decltype(auto) _v(IdxType r, IdxType c) { return derived()->_v(r, c); }

	inline decltype(auto) ref() const { return derived()->_ref(); }
	inline decltype(auto) ref() { return derived()->_ref(); }

	inline const auto _ref() const { return *derived(); }
	inline auto _ref() { return *derived(); }

private:
	inline const Derived* derived() const { return static_cast<const Derived*>(this); }
	inline Derived* derived() { return static_cast<Derived*>(this); }


	template <typename LhsMatDerieved2, typename RhsMatDerieved2, int CalcType2>
	friend class MatrixMaskBinary; 



};


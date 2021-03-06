#pragma once

#include <iostream>
#include "matrix/mytypes.h"
#include "matrix/matrixUnaryOperations.h"
#include "matrix/matrixBinaryOperations.h"
#include "matrix/matrixMaskBase.h"
#include "matrix/matrixMaskBinaryOperations.h"

template <typename T>
class myMatrix;

template <typename T, typename InMatBase, int CalcType>
class myMatrixUnary;

template <typename T, typename LhsMatBase, typename RhsMatBase, int CalcType>
class myMatrixBinary;

template <typename T, typename Derived>
class myMatrixBase
{
public:
	inline myMatrix<T> concrete() const { return *(this->derived()); }
	
	/* read only */
	inline IdxType getSize() const { return derived()->getSize(); }
	inline IdxType getRows() const { return derived()->getRows(); }
	inline IdxType getCols() const { return derived()->getCols(); }

	/* Unary Operations */

	// 1. Transpose
	inline const auto t() const { return createUnaryOperation<T, UNARY_TRANSPOSE> ( this->ref());}
	inline auto t() { return createUnaryOperation<T, UNARY_TRANSPOSE>( this->ref()); }

	// 2. Minus
	inline const auto operator-() { return createUnaryOperation<T, UNARY_MINUS>(this->ref()); }

	// 3. Squared
	inline const auto Squared() { return createUnaryOperation<T, UNARY_SQUARED>(this->ref()); }

	// Select From Masking
	template <typename MaskDerived> inline
	const auto select(MaskDerived && InMatDerived) const
	{	return createUnarySelecteOperation<T>(this->ref(), std::forward<MaskDerived>(InMatDerived));}

	template <typename MaskDerived> inline
	auto select(MaskDerived&& InMatDerived)
	{	return createUnarySelecteOperation<T>(this->ref(), std::forward<MaskDerived>(InMatDerived));}

	// Elementwise Unary Manipulate
	template<typename Fn> inline 
		const auto EManip(Fn Func) const { return createUnaryManipulateOperation<T>(this->ref(), Func); }

	const auto EManip(T (*Func) (T) ) const { return createUnaryManipulateOperation<T>(this->ref(), Func); }

	/* Binary Operations */
	
	// 1. Elementwise Addition
	template<typename OtherDerived> inline
		const auto operator+ (const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryOperation<T, BINARY_ADD>(this->ref(), rhs.ref());
	}

	// 2. Elementwise Subtraction
	template<typename OtherDerived> inline
		const auto operator- (const myMatrixBase<T, OtherDerived> & rhs) const { 
		return  createBinaryOperation<T, BINARY_SUB>(this->ref(), rhs.ref());
	}

	// 3. MatrixMultiplication
	template<typename OtherDerived> inline
		const auto operator* (const myMatrixBase<T, OtherDerived>& rhs) const {
		return  createBinaryOperation<T, BINARY_MATMUL>(this->ref(), rhs.ref());
	}

	// 5. Elementwise Multiplication
	template<typename OtherDerived> inline
		const auto EMul (const myMatrixBase<T, OtherDerived>& rhs) const {
		return  createBinaryOperation<T, BINARY_EMUL>(this->ref(), rhs.ref());
	}
	
	// 6. Elementwise Division
	template<typename OtherDerived> inline
		const auto EDiv(const myMatrixBase<T, OtherDerived>& rhs) const {
		return  createBinaryOperation<T, BINARY_EDIV>(this->ref(), rhs.ref());
	}

	// Elementwise Binary Manipulate
	template<typename OtherDerived, typename Fn> inline
		const auto EManip(const myMatrixBase<T, OtherDerived>& rhs, Fn Func) const { return createBinaryManipulateOperation<T>(this->ref(), rhs.ref(), Func); }

	template<typename OtherDerived> inline
		const auto EManip(const myMatrixBase<T, OtherDerived>& rhs, T(*Func) (T, T)) const { return createBinaryManipulateOperation<T>(this->ref(), rhs.ref(), Func); }

	/* binary operations return value is mask */
	
	// 6. Elementwise less than
	template<typename OtherDerived> inline
		const auto operator<(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_LESS>(this->ref(), rhs.ref());
	}

	// 7. Elementwise less than or equal to
	template<typename OtherDerived> inline
		const auto operator<=(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_LEQ>(this->ref(), rhs.ref());
	}

	// 8. Elementwise greater than
	template<typename OtherDerived> inline
		const auto operator>(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_GREATER>(this->ref(), rhs.ref());
	}

	// 9. Elementwise greater than or equal to
	template<typename OtherDerived> inline
		const auto operator>=(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_GEQ>(this->ref(), rhs.ref());
	}

	// 10. Elementwise equal to
	template<typename OtherDerived> inline
		const auto operator==(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_EQUAL>(this->ref(), rhs.ref());
	}

	// 11. Elementwise less than or equal to
	template<typename OtherDerived> inline
		const auto operator!=(const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryMaskOperation<MASK_BINARY_CMP_NEQ>(this->ref(), rhs.ref());
	}

	// assingment (non const only)
	template<typename OtherDerived>
	inline void operator=(const myMatrixBase<T, OtherDerived>& rhs) { derived()->operator=(*rhs.derived()); }

	inline void operator=(T rhs) { derived()->operator=(rhs); }

	// for internal use element pick (later to be put to protected )
	inline const T _v(IdxType r, IdxType c) const { return derived()->_v(r,c); }
	inline T& _v(IdxType r, IdxType c) { return derived()->_v(r, c); }

	inline decltype(auto) ref() const { return derived()->_ref(); }
	inline decltype(auto) ref() { return derived()->_ref(); }

	inline const auto _ref() const { return *derived(); }
	inline auto _ref() { return *derived(); }

private:
	inline const Derived* derived() const { return static_cast<const Derived*>(this); }
	inline Derived* derived() { return static_cast<Derived*>(this); }

	template <typename T2, typename Derived2>
	friend std::ostream& operator<<(std::ostream& o, const myMatrixBase<T2, Derived2>& MatIn);

};


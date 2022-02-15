#pragma once

#include <iostream>
#include "matrix/mytypes.h"
#include "matrix/matrixUnaryOperations.h"
#include "matrix/matrixBinaryOperations.h"

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
	
	// read
	inline IdxType getSize() const { return derived()->getSize(); }
	inline IdxType getRows() const { return derived()->getRows(); }
	inline IdxType getCols() const { return derived()->getCols(); }

	// Unary Operations
	inline const auto t() const { return createUnaryOperation<T, UNARY_TRANSPOSE> ( this->ref()); }
	inline auto t() { return createUnaryOperation<T, UNARY_TRANSPOSE>( this->ref()); }

	// Binary Operations 
	template<typename OtherDerived> inline
		const auto operator+ (const myMatrixBase<T, OtherDerived>& rhs) const {
		return createBinaryOperation<T, BINARY_ADD>(this->ref(), rhs.ref());
	}

	template<typename OtherDerived> inline
		const auto operator- (const myMatrixBase<T, OtherDerived> & rhs) const { 
		return  createBinaryOperation<T, BINARY_SUB>(this->ref(), rhs.ref());
	}

	template<typename OtherDerived> inline
		const auto operator* (const myMatrixBase<T, OtherDerived>& rhs) const {
		return  createBinaryOperation<T, BINARY_MATMUL>(this->ref(), rhs.ref());
	}



	

	// assingment (non const only)
	template<typename T, typename OtherMat>
	inline void operator=(const myMatrixBase<T, OtherMat>& rhs) { derived()->operator=(*rhs.derived()); }

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


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
	inline const auto t() const { return myMatrixUnary<T, const Derived, UNARY_TRANSPOSE>( this->ref()); }
	inline auto t() { return myMatrixUnary<T, Derived, UNARY_TRANSPOSE>( this->ref()); }

	// Binary Operations 

	template<typename OtherDerived> inline
		const auto operator+ (const myMatrixBase<T, OtherDerived>& rhs) const {
		return  myMatrixBinary<T, const myMatrixBase, const myMatrixBase<T, OtherDerived>, BINARY_ADD>(this, &rhs); }

	template<typename OtherDerived> inline
		const auto operator- (const myMatrixBase<T, OtherDerived> & rhs) const { 
		return  myMatrixBinary<T, const myMatrixBase, const myMatrixBase<T, OtherDerived>, BINARY_SUB> (this, &rhs); }

	template<typename OtherDerived> inline
		const auto operator* (const myMatrixBase<T, OtherDerived>& rhs) const {
		return  myMatrixBinary<T, const myMatrixBase, const myMatrixBase<T, OtherDerived>, BINARY_MATMUL>(this, &rhs); }



	

	// assingment (non const only)
	template<typename T, typename OtherMat>
	inline void operator=(const myMatrixBase<T, OtherMat>& rhs) { derived()->operator=(*rhs.derived()); }

	// for internal use element pick (later to be put to protected )
	inline const T _v(IdxType r, IdxType c) const { return derived()->_v(r,c); }
	inline T& _v(IdxType r, IdxType c) { return derived()->_v(r, c); }

	inline const auto ref() const { return derived()->_ref(); }
	inline auto ref() { return derived()->_ref(); }

	inline const auto _ref() const { return *derived(); }
	inline auto _ref() { return *derived(); }


private:
	inline const Derived* derived() const { return static_cast<const Derived*>(this); }
	inline Derived* derived() { return static_cast<Derived*>(this); }


	template <typename T2, typename Derived2>
	friend std::ostream& operator<<(std::ostream& o, const myMatrixBase<T2, Derived2>& MatIn);

};


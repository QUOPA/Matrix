#pragma once

#include "matrix/matrixBase.h"
#include "matrix/matrix.h"

template <typename T, typename OtherDerived>
class matrixReference : public myMatrixBase<T, matrixReference<T, OtherDerived> >
{
public:
	explicit matrixReference(OtherDerived *  matin)
		: m_pInMat(matin){}

	inline IdxType getSize() const { return m_pInMat->getSize(); }
	inline IdxType getRows() const { return m_pInMat->getRows(); }
	inline IdxType getCols() const { return m_pInMat->getCols(); }

protected:
	inline const T _v(IdxType r, IdxType c) const { return m_pInMat->_v(r, c); }
	inline T& _v(IdxType r, IdxType c) { return m_pInMat->_v(r, c); }

	template <typename T2, typename Derived2>
	friend class myMatrixBase;

private:
	OtherDerived * m_pInMat;



};
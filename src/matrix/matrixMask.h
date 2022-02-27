#pragma once

#include "matrix/matrixMaskBase.h"
#include "matrix/matrixexceptions.h"
#include <vector>

template<typename Derived>
class MatrixMaskBase;

class MatrixMask : public MatrixMaskBase<MatrixMask>
{
public:
	MatrixMask() : m_nRows(0), m_nCols(0) { }
	MatrixMask(const std::vector<bool>& maskin, IdxType nRows, IdxType nCols)
		:m_nRows(0), m_nCols(0)
	{
		if (nRows <= 0 || nCols <= 0)
			throw matrix_rangeerror("bad row size or column size input");

		if (nRows * nCols != maskin.size())
			throw matrix_sizematcherror("Size do not match : nRows * nCols != datain.size()");

		m_Mask = maskin;

		m_nRows = nRows;
		m_nCols = nCols;
	}

	template<typename OtherMat>
	MatrixMask(const MatrixMaskBase<OtherMat>& rhs)
		:m_nRows(0), m_nCols(0)
	{ this->operator=(rhs); }

	MatrixMask(const MatrixMask& rhs)
		:m_nRows(0), m_nCols(0)
	{ this->operator=(rhs); }


	void operator=(const MatrixMask& rhs)
	{
		m_Mask = rhs.m_Mask;
		m_nRows = rhs.getRows();
		m_nCols = rhs.getCols();
	}

	void operator=(MatrixMask&& rhs)
	{
		std::swap(m_Mask, rhs.m_Mask);
		m_nRows = rhs.getRows();
		m_nCols = rhs.getCols();
	}

	template<typename OtherMat>
	void operator=(const MatrixMaskBase<OtherMat>& rhs)
	{
		m_Mask.resize(rhs.getSize());
		m_nRows = rhs.getRows();
		m_nCols = rhs.getCols();

		for (IdxType r = 0; r < m_nRows; ++r)
			for (IdxType c = 0; c < m_nCols; ++c)
				_v(r, c) = rhs._v(r, c);
	}

	inline IdxType getSize() const { return m_nRows * m_nCols; }
	inline IdxType getRows() const { return m_nRows; }
	inline IdxType getCols() const { return m_nCols; }


	inline const auto& _ref() const {
		return *this;
	}

	inline auto& _ref() {
		return *this;
	}

	inline decltype(auto) _v(IdxType r, IdxType c) const { return m_Mask[r * m_nCols + c]; }
	inline decltype(auto) _v(IdxType r, IdxType c) { return m_Mask[r * m_nCols + c]; }

private:
	IdxType m_nRows;
	IdxType m_nCols;

	std::vector<bool> m_Mask;

	template<typename Derived>
	friend class MatrixMaskBase;

};

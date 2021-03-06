#pragma once

#include "matrix/matrixbase.h"
#include "matrix/matrixexceptions.h"
#include "matrix/matrixReference.h"
#include <vector>

template <typename T>
class myMatrix : public myMatrixBase<T, myMatrix<T>>
{
public:
	myMatrix()
		:m_pData(nullptr), m_nRows(0), m_nCols(0)
	{}

	myMatrix(const T * datain, IdxType nRows, IdxType nCols);
	//myMatrix(T* && datain, IdxType nRows, IdxType nCols);

	myMatrix(const std::vector<T> & datain, IdxType nRows, IdxType nCols);	

	template<typename OtherMat>
	myMatrix(const myMatrixBase<T, OtherMat>& rhs) 
		:m_pData(nullptr), m_nRows(0), m_nCols(0) 
	{ this->operator=(rhs); }

	myMatrix(const myMatrix& rhs) 
		:m_pData(nullptr), m_nRows(0), m_nCols(0)
	{ this->operator=(rhs); }

	inline IdxType getSize() const { return m_nRows * m_nCols; }
	inline IdxType getRows() const { return m_nRows; }
	inline IdxType getCols() const { return m_nCols; }

	void operator=(const myMatrix& rhs) 
	{
		if (!renewDataMemory(rhs.getSize()))
			throw matrix_rangeerror("Failed to renew data memory of size :" + std::to_string(rhs.getSize()));

		m_nRows = rhs.getRows();
		m_nCols = rhs.getCols();

		std::size_t nSize = rhs.getSize() * sizeof(T);
		memcpy(m_pData, rhs.m_pData, nSize);
	}

	void operator=(myMatrix && rhs) 
	{  
		std::swap(m_pData, rhs.m_pData);
		std::swap(m_nRows, rhs.m_nRows);
		std::swap(m_nCols, rhs.m_nCols);
	}

	template<typename OtherMat>
	void operator=(const myMatrixBase<T, OtherMat>& rhs)
	{ 
		if (getSize() != rhs.getSize())
		{
			T* tmpData = new T[rhs.getSize()];
			if (tmpData == nullptr)
				throw matrix_memoryerror("Failed to create temporary data storage");

			m_nRows = rhs.getRows();
			m_nCols = rhs.getCols();

			for (IdxType r = 0; r < m_nRows; ++r)
				for (IdxType c = 0; c < m_nCols; ++c)
					tmpData[r * m_nCols + c] = rhs._v(r, c);

			if (m_pData != nullptr)
				delete[] m_pData;

			m_pData = tmpData;
		}
		else
		{
			if (m_pData == nullptr)
				m_pData = new T[getSize()];

			if (m_pData == nullptr)
				throw matrix_memoryerror("Failed to create temporary data storage");

			m_nRows = rhs.getRows();
			m_nCols = rhs.getCols();

			for (IdxType r = 0; r < m_nRows; ++r)
				for (IdxType c = 0; c < m_nCols; ++c)
					m_pData[r * m_nCols + c] = rhs._v(r, c);

		}
	}

	inline void operator=(T rhs)
	{
		for (int idx = 0; idx < getSize(); ++idx)
			m_pData[idx] = rhs;
	}


	inline const auto & _ref() const {
		return *this;
	}

	inline auto & _ref() {
		return *this;
	}

	inline const T _v(IdxType r, IdxType c) const { return m_pData[r * m_nCols + c]; }
	inline T& _v(IdxType r, IdxType c) { return m_pData[r * m_nCols + c]; }

private:
	bool renewDataMemory(IdxType nSize)
	{
		if (m_pData != nullptr)
			delete[] m_pData;
		m_pData = new T[nSize];
		return m_pData != nullptr;
	}

	T* m_pData;
	IdxType m_nRows;
	IdxType m_nCols;

	template <typename T2, typename Derived2>
	friend class myMatrixBase;

	template <typename T2, typename Derived2>
	friend class matrixReference;
	
	template <typename T2, typename InMatDerieved, int CalcType>
	friend class myMatrixUnary;

	template <typename T2, typename InMatDerieved, typename InMatrixMask>
	friend class myMatrixUnarySelected;
};

template<typename T>
myMatrix<T>::myMatrix(const T* datain, IdxType nRows, IdxType nCols)
	:m_pData(nullptr), m_nRows(0), m_nCols(0)
{
	if (nRows <= 0 || nCols <= 0)
		throw matrix_rangeerror("bad row size or column size input");

	m_pData = new T[nRows * nCols];

	m_nRows = nRows;
	m_nCols = nCols;

	for (IdxType r = 0; r < m_nRows; ++r)
		for (IdxType c = 0; c < m_nCols; ++c)
			m_pData[r * m_nCols + c] = datain[r * m_nCols + c];
}


template<typename T>
myMatrix<T>::myMatrix(const std::vector<T>& datain, IdxType nRows, IdxType nCols)
	:m_pData(nullptr), m_nRows(0), m_nCols(0)
{
	if (nRows <= 0 || nCols <= 0)
		throw matrix_rangeerror("bad row size or column size input");

	if (nRows * nCols != datain.size())
		throw matrix_sizematcherror("Size do not match : nRows * nCols != datain.size()");

	m_pData = new T[nRows * nCols];

	m_nRows = nRows;
	m_nCols = nCols;

	std::size_t nSize = datain.size() * sizeof(T);
	memcpy(m_pData, datain.data(), nSize);

	//for (IdxType r = 0; r < m_nRows; ++r)
	//	for (IdxType c = 0; c < m_nCols; ++c)
	//		m_pData[r * m_nCols + c] = datain[r * m_nCols + c];
}

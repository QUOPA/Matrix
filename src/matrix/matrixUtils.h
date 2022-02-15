#pragma once

#include <iostream>

#define showFormatedMatrix(mtxname) \
showMatrixNameAndInfo(mtxname)<< mtxname << std::endl;

#define showMatrixNameAndInfo(mtxname) \
std::cout << "<" << #mtxname << ">" << std::endl; \
showMatrixInfo(mtxname)

template <typename LhsType, typename RhsType>
inline void throwIfRowsDifferent(const LhsType & LhsMat, const RhsType & RhsMat)
{
	if (LhsMat.getRows() != RhsMat.getRows())
		throw matrix_sizematcherror_rows();
}

template <typename LhsType, typename RhsType>
inline void throwIfColsDifferent(const LhsType & LhsMat, const RhsType & RhsMat)
{
	if (LhsMat.getCols() != RhsMat.getCols())
		throw matrix_sizematcherror_cols();
}

template <typename LhsType, typename RhsType>
inline void throwIfInnerDifferent(const LhsType& LhsMat, const RhsType& RhsMat)
{
	if (LhsMat.getCols() != RhsMat.getRows())
		throw matrix_sizematcherror_inners();
}



template <typename T, typename Derived>
class myMatrixBase;

template <typename T, typename Derived>
std::ostream& operator<<(std::ostream& o, const myMatrixBase<T, Derived>& MatIn);

template <typename T, typename Derived>
std::ostream& showMatrixInfo(const myMatrixBase<T, Derived>& MatIn);

template <typename T, typename Derived>
std::ostream& operator<<(std::ostream& o, const myMatrixBase<T, Derived>& MatIn)
{
	o << "[";
	for (IdxType r = 0; r < MatIn.getRows(); ++r)
	{
		if (r != 0)
			o << std::endl;

		for (IdxType c = 0; c < MatIn.getCols(); ++c)
		{
			if (c == 0)
				o << MatIn._v(r, c);
			else
				o << ", " << MatIn._v(r, c);
		}
	}
	o << "]";
	return o;
}

template<typename T, typename Derived>
std::ostream& showMatrixInfo(const myMatrixBase<T, Derived>& MatIn)
{
	std::cout << MatIn.getRows() << " Rows, " << MatIn.getCols() << " Cols" << std::endl;
	return std::cout;
}



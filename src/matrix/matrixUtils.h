#pragma once

#include <iostream>

#define showMatrixNameAndInfo(mtxname) \
std::cout << "<" << #mtxname << ">" << std::endl; \
showMatrixInfo(mtxname)


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
				o << *MatIn._v(r, c);
			else
				o << ", " << *MatIn._v(r, c);
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



#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixMask.h"
#include "matrix/matrixUtils.h"

namespace maskbinaryoperations
{
	void createmaskbybinary()
	{
		std::vector<bool> vecTempBoolean{ true, true, false, false };
		MatrixMask matMask(vecTempBoolean, 2, 2);

		std::vector<double> vecDouble{ 3, 6, 9, 12 };
		myMatrix<double> Mat1(vecDouble, 2, 2);

		std::vector<double> vecDouble2{ 6, 6, 6, 6};
		myMatrix<double> Mat2(vecDouble2, 2, 2);

		myMatrix<double> Mat3({100,100,100,100}, 2, 2);

		auto tmpMask = Mat1 < Mat2;
		showFormatedMatrix(tmpMask);

		auto tmpMask2 = Mat1 <= Mat2;
		showFormatedMatrix(tmpMask2);

		Mat1.select( Mat1 <= Mat2 ) = Mat3;
		showFormatedMatrix(Mat1);

	}

	void matrixmaskboolean()
	{
		std::vector<bool> vecTempBoolean{ true, true, false, false };
		MatrixMask matMask(vecTempBoolean, 2, 2);

		std::vector<bool> vecTempBoolean2{ true, false, true, false };
		MatrixMask matMask2(vecTempBoolean2, 2, 2);

		auto MaskAND = matMask & matMask2;
		auto MaskOR = matMask | matMask2;
		auto MaskXOR = matMask ^ matMask2;
		auto MaskExclude = matMask - matMask2;
		auto MaskNAND = !(matMask & matMask2);
		
		showFormatedMatrix(MaskAND);
		showFormatedMatrix(MaskOR);
		showFormatedMatrix(MaskXOR);
		showFormatedMatrix(MaskExclude);
		showFormatedMatrix(MaskNAND);
	}

	void booleanandcomparison()
	{
		std::vector<bool> vecTempBoolean{ true, true, false, false };
		MatrixMask matMask(vecTempBoolean, 2, 2);

		std::vector<double> vecDouble{ 3, 6, 9, 12 };
		myMatrix<double> Mat1(vecDouble, 2, 2);

		std::vector<double> vecDouble2{ 6, 6, 6, 6 };
		myMatrix<double> Mat2(vecDouble2, 2, 2);

		myMatrix<double> Mat3({ 100,100,100,100 }, 2, 2);
		
		auto ComplexSelect1 = Mat1 >= Mat2 & matMask;
		showFormatedMatrix(ComplexSelect1);
		Mat3.select(ComplexSelect1) = Mat2;
		showFormatedMatrix(Mat3)
	}

}
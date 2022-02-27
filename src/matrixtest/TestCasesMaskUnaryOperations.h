#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixMask.h"
#include "matrix/matrixUtils.h"

namespace maskunaryoperations
{
	void createmask()
	{
		std::vector<bool> vecTempBoolean{true, true, false, false};
		MatrixMask matMask(vecTempBoolean, 2, 2);
		
		std::vector<double> vecDouble{ 3, 6, 9, 12 };
		myMatrix<double> Mat1(vecDouble, 2, 2);

		auto RetMat = Mat1.select(matMask);
		showFormatedMatrix(RetMat);
		showFormatedMatrix(RetMat.concrete());

		MatrixMask matMask2 = !matMask;
		showFormatedMatrix(matMask2);

		myMatrix<double> newMat = Mat1.select(matMask) - Mat1.select(matMask2);
		showFormatedMatrix(newMat);
		showFormatedMatrix(Mat1);
		
		Mat1.select(MatrixMask({ true, false, false, false }, 2, 2)) = -Mat1;
		showFormatedMatrix(Mat1);
	}
}
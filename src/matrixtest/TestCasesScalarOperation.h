#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixMask.h"
#include "matrix/matrixUtils.h"
#include "matrix/matrixOperations.h"


namespace scalaroperation
{
	
	void scalararithmetic ()
	{
		std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		myMatrix<int> mat(vecInts, 2, 5);
		showFormatedMatrix(mat);

		auto matAdded = mat + 5;
		showFormatedMatrix(matAdded);

		auto matSubtract_MLeft = mat - 1;
		showFormatedMatrix(matSubtract_MLeft);
		
		auto matSubtract_MRight = 10 - mat;
		showFormatedMatrix(matSubtract_MRight);
		
		auto matMultiplication = 10 * mat ;
		showFormatedMatrix(matMultiplication);
		
		auto matDivision_MLeft = mat/2;
		showFormatedMatrix(matDivision_MLeft);

		auto matDivision_MRight = 100 / mat;
		showFormatedMatrix(matDivision_MRight);
	}

	void scalarassignment()
	{
		std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		myMatrix<int> mat(vecInts, 2, 5);
		showFormatedMatrix(mat);

		mat = mat + 5;
		showFormatedMatrix(mat);

		mat = 5;
		showFormatedMatrix(mat);		
	}

}
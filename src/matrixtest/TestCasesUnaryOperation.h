#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixUtils.h"
//#include "algomatrix/matrixUnaryOperations.h"

namespace unaryoperation
{

void transpose()
{
	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	myMatrix<int> mat(vecInts, 2, 5);
	showFormatedMatrix(mat);
	
	showFormatedMatrix(mat.t());
	
	myMatrix<int> mat_Tran_Concrete = mat.t();
	showFormatedMatrix(mat_Tran_Concrete);
	
	const myMatrix<int> constMat(vecInts, 2, 5);
	showFormatedMatrix(constMat);
	
	showFormatedMatrix(constMat.t());
	
	myMatrix<int> constMat_Trans_Concrete = constMat.t();
	showFormatedMatrix(constMat_Trans_Concrete);
}

void transposeAssignment()
{
	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vecInts2 = { -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
	
	myMatrix<int> mat(vecInts, 2, 5);
	showFormatedMatrix(mat);
	
	myMatrix<int> mat2(vecInts2, 5, 2);
	showFormatedMatrix(mat2);
	
	mat.t().t().t() = mat2;

	std::cout << "after mat.t() = mat2 ... " << std::endl;
	showFormatedMatrix(mat);

	//below not allowed
	//const myMatrix<int> constMat(vecInts, 2, 5);
	//constMat.t() = mat2; 
}

}

#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixUtils.h"
//#include "algomatrix/matrixUnaryOperations.h"

namespace unaryoperation
{

void transpose()
{
	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7,8, 9, 10 };

	myMatrix<int> mat(vecInts, 2, 5);
	showMatrixNameAndInfo(mat) << mat << std::endl;
	
	auto mat_Tran_Express = mat.t();
	showMatrixNameAndInfo(mat_Tran_Express) << mat_Tran_Express << std::endl;

	myMatrix<int> mat_Tran_Concrete = mat_Tran_Express;
	showMatrixNameAndInfo(mat_Tran_Concrete) << mat_Tran_Concrete << std::endl;

	const myMatrix<int> constMat(vecInts, 2, 5);
	showMatrixNameAndInfo(constMat) << constMat << std::endl;
	
	auto constMat_Trans_Express = constMat.t();
	showMatrixNameAndInfo(constMat_Trans_Express) << constMat_Trans_Express << std::endl;

	myMatrix<int> constMat_Trans_Concrete = constMat_Trans_Express;
	showMatrixNameAndInfo(constMat_Trans_Concrete) << constMat_Trans_Concrete << std::endl;
}

void transposeAssignment()
{
	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vecInts2 = { -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };

	myMatrix<int> mat(vecInts, 2, 5);
	showMatrixNameAndInfo(mat) << mat << std::endl;

	myMatrix<int> mat2(vecInts2, 5, 2);
	showMatrixNameAndInfo(mat2) << mat2 << std::endl;

	mat.t() = mat2;
	std::cout << "after mat.t() = mat2 ... " << std::endl;
	showMatrixNameAndInfo(mat) << mat << std::endl;

	// below not allowed
	// const myMatrix<int> constMat(vecInts, 2, 5);
	// constMat.t() = mat2; 
}

}

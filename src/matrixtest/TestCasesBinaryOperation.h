#pragma once

#include "matrix/matrix.h"
#include "matrix/matrixUtils.h"

namespace binaryoperation
{

 void elementwiseaddition()
 {
 	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 
 	myMatrix<int> mat(vecInts, 2, 5);
 	showFormatedMatrix(mat);
 
 	myMatrix<int> mat2(vecInts, 2, 5);
 	showFormatedMatrix(mat2);
 
    showFormatedMatrix(mat2 + mat + mat);

 	myMatrix<int> mat4 = mat2 + mat + mat;
 	showFormatedMatrix(mat4);
 
 	std::vector<double> vecdouble = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

 	const myMatrix<double> cmat1(vecdouble, 2, 5);
 	showFormatedMatrix(cmat1);
 
 	const myMatrix<double> cmat2(vecdouble, 2, 5);
 	showFormatedMatrix(cmat2);
 
 	auto cmat3 = cmat1 + cmat2; //+cmat2 + cmat1 + cmat1;
 	const myMatrix<double> cmat4 = cmat3;
 
 	showFormatedMatrix(cmat3.concrete());
 
 }
 
 void elementwisesubtraction()
 {
 	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 
 	myMatrix<int> mat(vecInts, 2, 5);
 	showFormatedMatrix(mat);
 
 	myMatrix<int> mat2(vecInts, 2, 5);
 	showFormatedMatrix(mat2);
 
 	auto mat3 = mat2 - mat - mat - mat - mat;
 
 	myMatrix<int> mat4 = mat3;
 	showFormatedMatrix(mat4);
 
 	std::vector<double> vecdouble = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 	const myMatrix<double> cmat1(vecdouble, 2, 5);
 	showFormatedMatrix(cmat1);
 
 	const myMatrix<double> cmat2(vecdouble, 2, 5);
 	showFormatedMatrix(cmat2);
 
 	auto cmat3 = cmat1 - cmat2 - cmat2 - cmat1 - cmat1;
 	const myMatrix<double> cmat4 = cmat3;
 
 	showFormatedMatrix(cmat3.concrete());
 
 }	
 
 void matrixmultiplication()
 {
 	std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 
 	myMatrix<int> mat(vecInts, 2, 5);
 	showFormatedMatrix(mat);
 
 	myMatrix<int> mat2(vecInts, 5, 2);
 	auto mat3 = mat * mat2;
 	
 	myMatrix<int> mat4 = mat3;
 	showFormatedMatrix(mat4);
 
 	std::vector<double> vecdouble = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
 	const myMatrix<double> cmat1(vecdouble, 2, 5);
 	showFormatedMatrix(cmat1);
 	
 	auto cmat3 = cmat1.t() * cmat1;
 	//const myMatrix<double> cmat4 = cmat3;
 	
 	showFormatedMatrix(cmat3.concrete());
 
 }
 
 void compllicatedcalculation()
 {
 	std::vector<double> vecdouble = { 1, 2, 3, 4 };
 	const myMatrix<double> cmat1(std::move(vecdouble.data()), 2, 2);
 	
 	showFormatedMatrix(cmat1);
 	auto cmat3 = cmat1.t() * cmat1 * cmat1 + cmat1 + cmat1 - cmat1 - cmat1 + cmat1 - cmat1 * cmat1 + cmat1;
 
 	showFormatedMatrix(cmat3.concrete());

 }



}
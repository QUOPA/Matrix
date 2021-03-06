# Matrix
An easy-to-use header-only C++ library for matrix representation and calcualtion.
This matrix library support lazy evaluation, element-wise evaluation and so on, exploiting compile-time generic coding approach. 
The CRTP based class/expression backbone was deeply influenced by the famous matrix library 'Eigen'. 
# Features
## Lazy Evaluation
This matrix library employs expression template patterns, which is enabling detatch creation of expression from real evaluation as follows.
```c++
std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
myMatrix<int> mat(vecInts, 2, 5);
auto matExpr = mat + mat; // a proxy matrix indicating mat(lhs) and mat(rhs) to be added.
myMatrix<int> mat2 = matExpr; // evaluation of the matExpr by initialization.
auto mat3 = matExpr.concrete() // evaluation of matExpr by function.
```
## For loop fusion
The lazy evaluation enables multiple element-wise matrix calculation using one 'for' loop as follows.
```c++
std::vector<int> vecInts = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
myMatrix<int> mat(vecInts, 2, 5);
myMatrix<int> mat2(vecInts, 2, 5);
auto matExpr = mat2 - mat - mat - mat - mat; // five calculation
auto mat3 = matExpr.concrete(); // evaluation in one 'for' loop
```
[more examples](https://github.com/QUOPA/Matrix/blob/main/src/matrixtest/TestCasesBinaryOperation.h)

## Element-wise evaluation / Partial evaluation
It is possible to calculate one element 
```c++
... continued to the above code
auto matExpr2 = (mat2 + mat1) * mat1.t() ) // formulating expression, not evaluated
std::cout << matExpr2._v(1,0) << std::endl; // evaluate 1,0 th element then show (the other elements are not evaluated)
```
## Masking
1. Can use mask (or filter) to select data from matrix seen.
```c++
// working as data retrive
myMatrix<int> mat1 ({1,2,3,4}, 2, 2);
myMatrix<int> mat2 = mat1.select(mat1 >= 2) - mat1.select(mat1 < 2); // mat2 --> {-1,-2;3,4}
```
[more examples.](https://github.com/QUOPA/Matrix/blob/main/src/matrixtest/TestCasesScalarOperation.h)

2. Mask for filtering element position to be updated
```c++
// working as data retrive
myMatrix<int> mat1 ({1,2,3,4}, 2, 2);
mat1.select(mat1 < 2) = - mat1; // mat1 --> {-1,2;3,4}
```
[more examples.](https://github.com/QUOPA/Matrix/blob/main/src/matrixtest/TestCasesMaskUnaryOperations.h)

3. Mask arithematic
```c++
// working as data retrive
myMatrix<int> mat1 ({1,2,3,4}, 2, 2);
mat1.select(mat1 < 2 | mat1 == 4 ) = - mat1; // mat1 --> {-1,2;3,-4}
```
[more examples.](https://github.com/QUOPA/Matrix/blob/main/src/matrixtest/TestCasesMaskBinaryOperations.h)

# Upcomming Features...
## Getting sub-matrix or sub-vector 
```c++
myMatrix<int> mat1 ({1,2,3,4}, 2, 2);
mat1.row(1) = 10; // now data --> {1,2,10,10}
```
## Arithmetic and Assign
```c++
myMatrix<int> mat1 ({1,2,3,4}, 2, 2);
mat1 += 10; // now data --> {11,12,13,14}
```

# Performance
to be tested.

# Further Works
* Determine Class name ... not "myMatrix" ... 
* Calculation optimization. 
* Numerical algorithm such as pseudo-inverse, faster matrix multiplication algorithm ....
* Study on hardware acceleration.
* More test codes for showing functions and performances.
* Better interface
* Hiding non interface functions and relate friendship
* arithmetic + assignment such as +=, -=
* Detailed To Do list ...

# Limit
The original work was for practicing programming skills, so some codes could not be the optimal for numerical calculations.

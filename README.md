# Matrix
An easy-to-use header-only C++ library for matrix representation and calcualtion.
This matrix library support lazy evaluation, element-wise evaluation and so on, exploiting compile-time generic coding methods and patterns. 
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
The lazy evaluation enables 
## Element-wise evaluation / Partial evaluation

# To Do (not implemented yet)

# Performance
to be tested.

# Further Works
* Calculation optimization. 
* Numerical algorithm such as pseudo-inverse, faster matrix multiplication algorithm ....
* Study on hardware acceleration.

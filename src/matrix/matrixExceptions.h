#pragma once
#include <stdexcept>
#include <string>

class matrixexcept : public std::exception 
{
public:
	matrixexcept(const std::string& strmsg) : std::exception(strmsg.data()) {}
	inline std::string getErrorKind() { return "matrix exception"; }
};

class matrix_rangeerror : public matrixexcept
{
public:
	matrix_rangeerror(const std::string& strmsg) : matrixexcept(strmsg) {}
	inline std::string getErrorKind() { return "matrix range error"; }
};

class matrix_operationerror : public matrixexcept
{
public:
	matrix_operationerror(const std::string& strmsg) : matrixexcept(strmsg) {}
	inline std::string getErrorKind() { return "matrix operation error"; }
};

class matrix_sizematcherror : public matrixexcept
{
public:
	matrix_sizematcherror(const std::string& strmsg) : matrixexcept(strmsg) {}
	inline std::string getErrorKind() { return "matrix size miss match error"; }
};

class matrix_sizematcherror_rows : public matrix_sizematcherror
{
public:
	matrix_sizematcherror_rows() : matrix_sizematcherror("Row Size Different btw LHS and RHS") {}
	inline std::string getErrorKind() { return "matrix row size mismatch error"; }
};

class matrix_sizematcherror_cols : public matrix_sizematcherror
{
public:
	matrix_sizematcherror_cols() : matrix_sizematcherror("Col Size Different btw LHS and RHS") {}
	inline std::string getErrorKind() { return "matrix col size mismatch error"; }
};

class matrix_sizematcherror_inners : public matrix_sizematcherror
{
public:
	matrix_sizematcherror_inners() : matrix_sizematcherror("Inner Size Different btw LHS and RHS") {}
	inline std::string getErrorKind() { return "matrix col size mismatch error"; }
};



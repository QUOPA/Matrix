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
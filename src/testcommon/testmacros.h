#pragma once

#include <chrono>
#include <exception>
#include <tuple>
#include <stdarg.h>
#include <string>
#include <iostream>

#define REGISTERTESTCASE(FN, ...)\
std::cout << std::endl << "< TEST CASE : " << #FN << " >" << std::endl; \
{auto _tickbegin = std::chrono::steady_clock::now();\
try { FN(##__VA_ARGS__);  } \
catch (std::exception & e) { std::cout << "Exception : " << e.what() <<std::endl; } \
catch (...) { std::cout << "Exception : Unexpected" << std::endl; }\
auto _tockend = std::chrono::steady_clock::now();\
std::cout << ">> Elepsed Time: " << getTimeDiffStr(_tickbegin,_tockend) << std::endl;}

#define REGISTERTESTSUITE(NS, ...)\
std::cout << std::endl <<  "======== TEST SUITE : " << #NS << " ========" << std::endl; \
__PARAMETEREXPANDER(##__VA_ARGS__);\
NS::TestSuite(##__VA_ARGS__);

#define REGISTERTESTSUITE(NS)\
std::cout << std::endl <<  "======== TEST SUITE : " << #NS << " ========" << std::endl; \
NS::TestSuite();

template<typename Head, typename... Args>
void __PARAMETEREXPANDER_IMPL(std::size_t N, const Head& head, const Args&... args);

template<typename Head>
void __PARAMETEREXPANDER_IMPL(std::size_t N, const Head& head);

template<typename... Args>
void __PARAMETEREXPANDER(const Args&... args)
{
	const std::size_t N = sizeof...(args);
	__PARAMETEREXPANDER_IMPL(N, args...);
}

template<typename Head>
void __PARAMETEREXPANDER_IMPL(std::size_t N, const Head& head)
{
	std::cout << "Param " << N << ": " << head << std::endl;
}

template<typename Head, typename... Args>
void __PARAMETEREXPANDER_IMPL(std::size_t N, const Head& head, const Args&... args)
{
	const std::size_t M = sizeof...(args);
	std::cout << "Param " << N - M << ": " << head << std::endl;
	__PARAMETEREXPANDER_IMPL(N, args...);
}

std::string getTimeDiffStr(const std::chrono::steady_clock::time_point& tickbegin
	, const std::chrono::steady_clock::time_point& tockend, int decimal = 0)
{
	std::string strDuration;
	std::string strUnit;
	long long timeduration = std::chrono::duration_cast<std::chrono::nanoseconds>(tockend - tickbegin).count();
	if (timeduration > 1E10)
		return std::to_string(timeduration / static_cast < long long>(1E9)) + " [s]";
	else if (timeduration > 1E7)
		return std::to_string(timeduration / static_cast < long long>(1E6)) + " [ms]";
	else if (timeduration > 1E4)
		return std::to_string(timeduration / static_cast<long long>(1E3)) +" [us]";
	else
		return std::to_string(timeduration) + " [ns]";
}


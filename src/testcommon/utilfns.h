#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <type_traits>

#include <exception>

#define REGISTERTESTCASE(FN) std::cout << "< TEST CASE : " << #FN << " >" << std::endl; \
try { FN(); } \
catch (std::exception & e) { std::cout << "Exception : " << e.what() <<std::endl; } \
catch (...) { std::cout << "Exception : Unexpected" << std::endl; }

#define REGISTERTESTSUITE(NS) std::cout << std::endl <<  "======== TEST SUITE : " << #NS << " ========" << std::endl; NS::TestSuite();

namespace testutil{

enum genvecopt // masking 
{
	OPT_NOOPTION = 0,
	OPT_SORTED = 1,
	OPT_UNIQUE = 2,
};

template<typename T>
void showvector(const std::vector<T>& vectoshow);

template<typename T>
std::vector<T> genvector(int minlen, int maxlen, const T & minval, const T & maxval, int optionMask = OPT_NOOPTION);

template<class T>
using uniform_distribution =
typename std::conditional<
	std::is_floating_point<T>::value,
	std::uniform_real_distribution<T>,
	typename std::conditional<
	std::is_integral<T>::value,
	std::uniform_int_distribution<T>,
	void
	>::type
>::type;


template<typename T>
inline void showvector(const std::vector<T>& vectoshow)
{
	for (size_t idx = 0; idx < vectoshow.size(); ++idx)
		std::cout << vectoshow[idx] << ", ";
	std::cout << std::endl;
}

 template<typename T>
 std::vector<T> genvector(int minlen, int maxlen, const T & minval, const T & maxval, int optionMask)
 {
 	std::random_device rd;
 	std::mt19937 rng(rd());
 	
 	std::uniform_int_distribution<> lendist(minlen, maxlen);
    uniform_distribution<T> valdist(minval, maxval);

 	int nlen = lendist(rng);

 	std::vector<T> retvec(nlen);
 	if (optionMask & OPT_UNIQUE)
 	{
        if ( std::is_integral<T>::value && (maxval - minval + 1) <= minlen )
            throw std::exception("vector generation failure : cannot generate unique list");

 		std::unordered_set<T> tmpset;
 		tmpset.reserve(nlen);
 		for (int idx = 0; idx < nlen;)
 		{
			tmpset.insert(valdist(rng));
 			idx = tmpset.size();
 		}
 		int idx = 0;
 		for (auto itr = tmpset.begin(); itr != tmpset.end(); ++itr) 
 		{
 			retvec[idx++] = *itr;
 		}
 	}
 	else
 	{
 		for (int idx = 0; idx < nlen; idx++)
 		{
 			retvec[idx] = valdist(rng);
 		}
 	}
 	
 	if (optionMask & OPT_SORTED)
 	{
 		std::sort(retvec.begin(), retvec.end());
 	}
 	
 	return retvec;
 	return std::vector<T>();
 }

}
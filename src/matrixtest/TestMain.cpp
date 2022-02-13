
#include "testcommon/testmacros.h"
#include "TestSuites.h"

int main()
{
	REGISTERTESTSUITE(unaryoperation)
	REGISTERTESTSUITE(binaryoperation)

	char buff[256];
	std::cin.getline(buff, 256);

	return 0;
}
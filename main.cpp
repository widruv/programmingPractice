#include <iostream>

#include "WebNavigation.h"

int main()
{
	WebNavigation aWebNavigation;
	while(true)
	{
		std::string inputString;
		std::string currentPage;
		std::getline( std::cin, inputString );
		if ( aWebNavigation.excute( inputString, currentPage ) == 0 )
		{
			break;
		}
		std::cout << currentPage << std::endl;
	}

	return 0;
}

#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iostream>
#include <list>
#include <zconf.h>

int main()
{
	std::list<std::string> listOfStrs = { "First", "Sec", "Third", "Fourth", "Fifth", "Sixth" };

	std::list<std::string>::iterator it = listOfStrs.begin();
	std::advance(it, 2);
    *it = "43";
    std::cout << "3rd element = " << *it << std::endl;


    /**** Finding nth element using std::next() ******/

	// Find 3rd element from list

	// It returns a new iterator pointing to n position after the
	// base iterator given as first argument
	auto it1 = std::next(listOfStrs.begin(), 2);

	std::cout << "3rd element = " << *it1 << std::endl;

	return 0;
}
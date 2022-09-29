#include "MutantStack.hpp"
#include <list>
#include <iterator>

int main()
{
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "Top Mutantstack: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "Size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);

	std::cout << "\n....................................\n" << std::endl;

	std::list<int> list;
	list.push_back(5);
	list.push_back(17);
	std::cout << "Top Mutantstack: " << list.back() << std::endl;
	list.pop_back();
	std::cout << "Size: " << list.size() << std::endl;
	list.push_back(3);
	list.push_back(5);
	list.push_back(737);
	list.push_back(0);
	std::list<int>::iterator it2 = list.begin();
	std::list<int>::iterator ite2 = list.end();
	++it2;
	--it2;
	while (it2 != ite2)
	{
		std::cout << *it2 << std::endl;
		++it2;
	}
	
	mstack.push(88);
	mstack.push(77);
	mstack.push(555);

	std::cout << "\n.........const_iterator........\n" << std::endl;
	MutantStack<int>::const_iterator constStart = mstack.cbegin();
	MutantStack<int>::const_iterator constEnd = mstack.cend();
	//*constStart = 0000;
	while (constStart != constEnd)
	{
		std::cout << *constStart << std::endl;
		++constStart;
	}
	std::cout << "\n.........reverse_iterator........\n" << std::endl;
	MutantStack<int>::reverse_iterator revStart = mstack.rbegin();
	MutantStack<int>::reverse_iterator revEnd = mstack.rend();
	*revStart = 5555;
	while (revStart != revEnd)
	{
		std::cout << *revStart << std::endl;
		++revStart;
	}
	return 0;
}

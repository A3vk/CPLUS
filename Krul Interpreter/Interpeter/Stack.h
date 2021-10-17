#pragma once
#include <vector>

template<class T>
class Stack : public std::vector<T>
{
public:
	T pop_back()
	{
		const T value = this->back();
		std::vector<T>::pop_back();
		return value;
	}
};


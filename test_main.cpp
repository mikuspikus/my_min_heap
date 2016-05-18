// test_main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "heap_queue.h"

int main()
{
	my_min_heap::heap_queue<std::string> one;

	one.insert(10, "Highest priority. Must be the last.");
	one.insert(5, "Average priority. Must be in the middle.");
	one.insert(0, "Lowest priority. Must be the first.");
	one.insert(5, "Still average priority. Must be after first average.");

	std::cout << one.extractMin() << "\n";
	std::cout << one.extractMin() << "\n";
	std::cout << one.extractMin() << "\n";
	std::cout << one.extractMin() << "\n";

    return 0;
}


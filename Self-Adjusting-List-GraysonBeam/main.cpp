#include <iostream>
#include <string>

#include "array_list.h"
#include "linked_list.h"

int main()
{
	nwacc::array_list<int> list;
	/**
	* Summary
	* Populate the array list with random values between one and one hundred.
	* And run the shift_right() method to shift all values in the array to the
	* right by one value.
	*/
	for (auto counter = 0; counter <= 19; counter++)
	{
		list.push_back(rand() % 100);
		list.shift_right();
	}
	int search_value;
	/**
	 * Summary
	 * Run the search algorithm that will find the value at the position of 4 in the array
	 * and move the value to position 0 of the array.
	 */
	list.search_algorithm(search_value);

	/**
	 * Summary
	 * Prints the value of counter, list.size(), and list.get_capacity() to the console.
	 */
	for (auto counter = 0; counter <= 19; counter++)
	{
		std::cout << counter << " | " << list.size() << " | " << list.get_capacity() << std::endl;
	}

	/**
	 * Summary
	 * Populates the linked_list with random values between one and one hundred.
	 */
	the_boot::linked_list<int> int_linked_list;
	for (auto counter = 0; counter <= 19; counter++)
	{
		int_linked_list.push_back(rand() % 100);
		
	}

	/**
	 * Summary
	 * Prints the value of the counter to the console.
	 */
	for (auto counter = 0; counter <= int_linked_list.size(); counter++)
	{
		std::cout << counter << std::endl;
	}
	return 0;
}
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s232ali@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    - jpalathu
 *    - malajeel
 * 
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -  crsockab
 * 
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;

		int *NEW_stack_array;
		int *NEW_minimum_array;
		int *NEW_maximum_array;


	public:
		Dynamic_range_stack( int = 10 );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {

	delete[] maximum_array;
	delete[] minimum_array;
	delete[] stack_array;

}

int Dynamic_range_stack::top() const {
	if (!empty()) 
	{
		return stack_array[entry_count - 1];
	}
	else
	{
		throw underflow();
	}
}

int Dynamic_range_stack::maximum() const {
	if (!empty()) 
	{
		return maximum_array[max_count - 1];
	}
	else
	{
		throw underflow();
	}
}

int Dynamic_range_stack::minimum() const {
	if (!empty()) 
	{
		return minimum_array[min_count - 1];
	}
	else
	{
		throw underflow();
	}
}

int Dynamic_range_stack::size() const {
	return entry_count;
}

bool Dynamic_range_stack::empty() const {

	return entry_count == 0;
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
	if (entry_count == current_capacity)
	{
		int *NEW_maximum_array = new int[current_capacity * 2];
		int *NEW_minimum_array = new int[current_capacity * 2];
		int *NEW_stack_array = new int[current_capacity * 2];

		current_capacity *= 2;

		std::copy(minimum_array, minimum_array + min_count, NEW_minimum_array);
		std::copy(maximum_array, maximum_array + max_count, NEW_minimum_array);
		std::copy(stack_array, stack_array + entry_count, NEW_stack_array);

		delete[] maximum_array;
		delete[] minimum_array;
		delete[] stack_array;

		maximum_array = NEW_maximum_array;
		minimum_array = NEW_minimum_array;
		stack_array = NEW_stack_array;
	}
		if (empty()) 
		{

			minimum_array[0] = obj;
			maximum_array[0] = obj;
			min_count = 1;
			max_count = 1;
				
		}
		// checking if new object is the less than previous min, if so, storing it as the new minimum
		else if (obj < minimum_array[min_count -1])
		{

			minimum_array[min_count] = obj;
			min_count ++;

		}
		// checking if the new object is greater than previous mac and if so, storing it as the new max
		else if (obj > maximum_array[max_count -1])
		{

			maximum_array[max_count] = obj;
			max_count ++;

		}

		stack_array[entry_count] = obj;
	

		entry_count ++;


}
	


int Dynamic_range_stack::pop() {

	if (!empty())
	{
	
		int lastEntry = stack_array[entry_count - 1];

		if (top() == minimum_array[max_count - 1])
		{
			int *NEW_minimum_array = new int[current_capacity];
			std::copy(minimum_array, minimum_array + min_count - 1, NEW_minimum_array);
			delete[] minimum_array;
			minimum_array = NEW_minimum_array;
			min_count --;
		}
		if (top() == maximum_array[max_count - 1])
		{
			int *NEW_maximum_array = new int[current_capacity];
			std::copy(maximum_array, maximum_array + max_count -1, NEW_maximum_array);
			delete[] maximum_array;
			maximum_array = NEW_maximum_array;
			max_count --;
		}
	int *NEW_stack_array = new int[current_capacity];
	std::copy(stack_array, stack_array + (entry_count - 1), NEW_stack_array);
	delete[] stack_array;
	stack_array = NEW_stack_array;
	entry_count --;

	return lastEntry;
	}
	else 
	{
		throw underflow();		
	}
	
}

void Dynamic_range_stack::clear() 
{

	delete[] maximum_array;
	delete[] minimum_array;
	delete[] stack_array;

	int *NEW_maximum_array = new int[initial_capacity];
	int *NEW_minimum_array = new int[initial_capacity];
	int *NEW_stack_array = new int[initial_capacity];

	max_count = 0;
	min_count = 0;
	current_capacity = initial_capacity;
	entry_count = 0;

	maximum_array = NEW_maximum_array;
	minimum_array = NEW_minimum_array;
	stack_array = NEW_stack_array;

}	



std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {

	return out;
}



#endif

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  s232ali
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	/*delete both the arrays*/
		delete[] array;					
		delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
		/*return the number of elements stored in the hash table*/
	return count;						
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	/*return the array_size for the capacity of the hash table */
	return array_size;					
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	/*if the hash table is empty*/
   return (count == 0) ?  true :  false; 
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	/*change the type of obj into an int*/
	int object = static_cast <int> (obj);
	int probe = object%array_size;
	/*if the probe is less than zero, add the array size to the probe*/
	if (probe < 0 ){
		probe = probe+array_size;
	}
	return probe;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	/*change the type of obj into an int*/
	int object = static_cast <int> (obj);
	int offset = (object/array_size)%array_size;

	/*if the offset is even, add one to make it odd*/
	if (offset%2 == 0 ){
		offset++;
	}
	/*if the probe is less than zero, add the array size to the probe*/
	if (offset < 0 ){
		offset = offset+array_size;
	}

	return offset;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {

	int collisionCount = 0; /*to keep track of the amount of collisions the obj runs into*/

	int probe = h1(obj);
	int offset = h2(obj); 


	if (array[probe] == obj && array_state[probe] == OCCUPIED) {
		return true;    /*if the object is in the first probe return true*/
	}

		int initial = probe;  /*set the first probe to varibale intial*/

	while (array_state[probe] != EMPTY){
		/*if there is a collision at the intial probe, loop through all the other probes
		 and check if the object is located at the new probe*/
		collisionCount++;

		probe = (collisionCount*h2(obj) +  h1(obj)) % array_size;

		if (array[probe] == obj && array_state[probe] == OCCUPIED) {
			return true; 
		}

		else if (probe == initial){
			return false; 
		}

	}
	/* use while loop- check if the array state is not empty*/
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {     

	return T(array[n]);
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {

	/*if there is a collision at the intial probe, find new probe using offset, 
	check if that is occupied, if it is not insert the obj*/

	int collisionCount = 0; 

	if (count == array_size){
		throw overflow();
	}

	else {

		 int probe = h1(obj);
		 int offset = h2(obj); 

		while (array_state[probe] == OCCUPIED){

			collisionCount++;
			probe = (collisionCount*h2(obj) +  h1(obj)) % array_size;
	
		}

		count++;
		array[probe] = obj;
		array_state[probe] = OCCUPIED;

	}

	 return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {

	int probe = h1(obj);
	int offset = h2(obj); 
	int collisionCount = 0; 
	int initial = probe; 

	if (array[probe] == obj && array_state[probe] == OCCUPIED){
			array_state[probe] = DELETED; 
			count--; 
			return true;
	}

	while (array_state[probe] != EMPTY){

		collisionCount++;

		probe = (collisionCount*h2(obj) +  h1(obj)) % array_size;

		if (array[probe] == obj && array_state[probe] == OCCUPIED) {
			array_state[probe] = DELETED; 
			count--; 
			return true;
		}

		else if (probe == initial){
			return false; 
		}

	}

	
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	count = 0;  
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
	 return ; 
}

//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
    //   // enter your implemetation here 
	//   for (int i = 0; i < array_size ; i++){
	// 	  std:: cout << array[i] << std:: endl;
	//   }	
	//   std:: cout << "STATE" << std:: endl;
	//     for (int i = 0; i < array_size ; i++){
	// 	  std:: cout << array_state[i] << std:: endl;
	//   }	
	// return;
}

#endif

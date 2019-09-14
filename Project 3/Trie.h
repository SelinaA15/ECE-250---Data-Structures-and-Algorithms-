/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s232ali @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -jpalathu
 *	  -
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -jpalathu
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;
		

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if (size()){
		return false;
	}
	else {
		return true;
	}
}

Trie_node *Trie::root() const {
	return root_node;

}

bool Trie::member( std::string const &str ) const {

	/*check to see if all the characters are letters*/
int i = 0;
	while (i < str.length()){
			if (!isalpha(str[i])){
			throw illegal_argument();
		}
		i++;
	}

	/*if the tree is not empty, call the trie_node member*/
	if (!empty()){
		if (root_node->member(str,0)){
			return true;
		}
	}
	else {
		return false;
	}
	
}

bool Trie::insert( std::string const &str ) {

	/*check to see if all the characters are letters*/	
int i = 0;
	while (i < str.length()){
			if (!isalpha(str[i])){
			throw illegal_argument();
		}
		i++;
	}

	/*if string is already in the tree return false*/
	
	if (root_node == nullptr){ 			
		root_node = new Trie_node;
	}

	 if (member(str) == true ){
	  	return false; 					
	 }

	/*inserting the first word into the tree*/
	
 	root_node-> insert(str, 0);
	trie_size = trie_size+1;
	return true;	

//	return false;
}

bool Trie::erase( std::string const &str ) {

int i = 0;
	while (i < str.length()){
			if (!isalpha(str[i])){
			throw illegal_argument();
		}
		i++;
	}


	if (!member(str)){
		return false;
	}

	if (empty()){
		return false;
	}

	/*if root node is the only thing that is there*/
	else if (size()==1){
		root_node->clear();
	  	delete root_node;
	 	root_node = nullptr;
		 trie_size = trie_size-1;
	}

	else{
		root_node->erase(str, 0, root_node);
    	trie_size = trie_size -1; 
	}
	    
 
return true;

}

void Trie::clear() {
	if (trie_size!=0) {
        
        root_node->clear();
    
        delete root_node;
        root_node = nullptr;
        trie_size = 0;
    }
}



std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}


#endif

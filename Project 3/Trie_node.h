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
 *	  -attien
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -jpalathu -debugging
 *****************************************/

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children; //a pointer to a pointer
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
	 	return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	/*make the characters all lowercase*/
	int index = str[depth];
	int letter = tolower(index) - 'a';
	
	/* if you've reached the end of the word, set to is terminal*/
		if (str.length()== depth){
			return is_terminal;
		}

	/*the next letter will be at depth+1*/
		int nextletter = depth+1;

	/*if there is no children array, then the word isnt in the tree*/
		if (children == nullptr){
			return false; 
		}

	/*if the child is pointing to something, call the function again to check what the child is pointing to*/
		if (children[letter] != nullptr){
			return children[letter]->member(str,nextletter);
		}
	return false;
}

bool Trie_node::insert( std::string const &str, int depth ) {
	/*if this is the last letter in the word, is_terminal = true*/
	if (str.length()== depth){
		is_terminal = true; 
		return true; 
	}

	/*make the characters all lowercase*/
	int index = str[depth];
	int letter = tolower(index) - 'a';

	/*Find the index in the array based on the letter*/

		/*if the node does not point to anything, make it point to a new array of 26 pointers */
		if (children == nullptr){
			children = new Trie_node*[CHARACTERS];

			/*make all pointers in the array point to null*/
			int i = 0;
			while(i<CHARACTERS){
				children[i] = nullptr;
				i++;
			}
		
			/*insert the next letter into this array*/
			children[letter] = new Trie_node; 

			/*if that specific index isnt pointing to anything make it point to a node*/
			if (children[letter]== nullptr){
				children[letter] = new Trie_node; 
			}
		}

		/*if the array of 26 pointers exsits but that specific index isnt pointing to anything make it point to a node*/
		else if (children[letter]== nullptr){
			children[letter] = new Trie_node; 
		}
	
	int nextletter = depth+1; 
	return children[letter]->insert(str,nextletter);
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	 
	int index = str[depth];
	int letter = tolower(index) - 'a';

 	 /*recurse into the tree to find the last node*/ 
	 if (str.length() == depth){
		 /*if you've found the last node, check if it is pointing to anything, if not then the node and it's pointer can be deleted*/
	 		is_terminal = false;
			if (children == nullptr){
				delete this; 
				ptr_to_this = nullptr; 
	 		}
 		return true; 
	 }

	int nextletter = depth+1;	
	 return children[letter]->erase(str,nextletter, children[letter]);
}

void Trie_node::clear() {

/*for every single index check it is pointing to something, if it is then call clear again with that node, if not keep going through the array*/
	if (children != nullptr){
		for (int i = 0; i < CHARACTERS; i++){
			if (children[i] != nullptr){
				children[i]->clear();
				delete children[i];
				children[i] = nullptr;
			}				
		}
	}
delete[] children;
children = nullptr;	
    
}

#endif

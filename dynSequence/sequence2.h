// FILE: sequence2.h
// CLASS PROVIDED: write your code inline with the class definition, IN THIS HEADER FILE,
// just as you would if you were writing Java code.
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   static const int DEFAULT_CAPACITY = _____
//     sequence::DEFAULT_CAPACITY is the initial capacity of a sequence that is
//     created by the default constructor.

// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.
//

#ifndef MAIN_SAVITCH_SEQUENCE_H
#define MAIN_SAVITCH_SEQUENCE_H
#include <iostream>
using namespace std;

typedef double value_type;

class sequence
{
private:
	//pointer to array
	value_type* data;

	int used;
	int current_index;

	//default capacity
	int capacity;
public:
	// TYPEDEFS and MEMBER CONSTANTS
	static const int DEFAULT_CAPACITY = 5;
	const int CAPACITY_DOUBLED = 2;

	// CONSTRUCTORS and DESTRUCTOR
	// CONSTRUCTORS for the sequence class:
	//   sequence(int initial_capacity = DEFAULT_CAPACITY)
	//     Postcondition: The sequence has been initialized as an empty sequence.
	//     The insert/attach functions will work efficiently (without allocating
	//     new memory) until this capacity is reached.
	sequence(int initial_capacity = DEFAULT_CAPACITY)
	{
		data = new value_type[initial_capacity];
		capacity = initial_capacity;
		current_index = 0;
		used = 0;
		
	}

	//	sequence(const sequence& source)
	//     Postcondition: the sequence has made a deep copy of the source sequence.
	sequence(const sequence& source)
	{
		//create new sequence
		data = new value_type[source.capacity];

		//copy members
		for (int i = 0; i < source.capacity; i++)
		{
			data[i] = source.data[i];
		}
		//set data
		capacity = source.capacity;
		used = source.used;
		current_index = source.current_index;
	}

	//  DESTRUCTOR:
	//	 ~sequence()
	//	Poscondition: all dynamically allocated memory has been destroyed.
	~sequence()
	{
		//delete array
			delete[] data;	
	}

	// MODIFICATION MEMBER FUNCTIONS
	// MODIFICATION MEMBER FUNCTIONS for the sequence class:
	//   void resize(int new_capacity)
	//     Postcondition: The sequence's current capacity is changed to the 
	//     new_capacity (but not less that the number of items already on the
	//     list). The insert/attach functions will work efficiently (without
	//     allocating new memory) until this new capacity is reached.
	void resize(int new_capacity)
	{
		//check for illegal size
		if (new_capacity < used)
		{
			cout << "Illegal size";
			return;
		}
		//create new sequence
		value_type * temp = new value_type[new_capacity];
		//copy members
		for (int i = 0; i < used; i++)
		{
			temp[i] = data[i];
		}
		//set data and delete unused arrays
		capacity = new_capacity;
		delete[] data;
		data = temp;
		temp = nullptr;
		delete[] temp;
	}

	//   void start( )
	//     Postcondition: The first item on the sequence becomes the current item
	//     (but if the sequence is empty, then there is no current item).
	void start()
	{
		current_index = 0;
	}

	//   void advance( )
	//     Precondition: is_item returns true.
	//     Postcondition: If the current item was already the last item in the
	//     sequence, then there is no longer any current item. Otherwise, the new
	//     current item is the item immediately after the original current item.
	void advance()
	{
		if (is_item())
		{
			current_index += 1;
		}
	}

	//   void insert(const value_type& entry)
	//     Postcondition: A new copy of entry has been inserted in the sequence
	//     before the current item. If there was no current item, then the new entry 
	//     has been inserted at the front of the sequence. In either case, the newly
	//     inserted item is now the current item of the sequence.
	void insert(const value_type& entry)
	{
		value_type temp = entry;
		//check for how full the array is or how empty it is
		if (used == 0)
		{
			//set new value in first location
			data[0] = temp;
			current_index = 0;
			used++;
			return;
		}

		//if array is full, resize.
		if (used == capacity)
		{
			resize(capacity * CAPACITY_DOUBLED);
		}
		//otherwise move the members
		else
		{
			for (int i = used; i >= current_index; i--)
			{
				if (i == current_index)
				{
					data[i] = entry;
					used++;
				}
				else
				{
					data[i] = data[i - 1];
				}
			}
		}
	}

	//   void attach(const value_type& entry)
	//     Postcondition: A new copy of entry has been inserted in the sequence after
	//     the current item. If there was no current item, then the new entry has 
	//     been attached to the end of the sequence. In either case, the newly
	//     inserted item is now the current item of the sequence.
	void attach(const value_type& entry)
	{
		//check if array is full, if so then resize.
		if (used == capacity)
		{
			resize(capacity * CAPACITY_DOUBLED);
		}
		//check if empty array
		if (used == 0)
		{
			data[0] = entry;
			used++;
			current_index = 0;
		}
		//if not then push old items back
		else
		{
			for (int i = used - 1; i >= current_index; i--)
			{
				if (i == current_index)
				{
					data[i + 1] = entry;
					current_index++;
					used++;
				}
				else
				{
					data[i + 1] = data[i];
				}
			}
		}

	}

	//   void remove_current( )
	//     Precondition: is_item returns true.
	//     Postcondition: The current item has been removed from the sequence, and the
	//     item after this (if there is one) is now the new current item.
	//	   else there is no current item.
	void remove_current()
	{
		//if it is an item then move items down
		if (is_item())
		{
			int count = current_index;
			while (count <= used - 1)
			{
				data[count] = data[count + 1];
				count++;
				if (count == used - 1)
				{
					data[used] = 0;
				}
			}
			used--;
		}
	}

	//	OPERATOR:
	//	  sequence operator =(const sequence& source);
	//	  Postondition: a deep copy of the source sequence replaces the current sequence.
	//                  Unused dynamic memory is deallocated.
	//                  Returns a sequence object in order to allow for chained assignments to work.
	sequence operator =(const sequence& source)
	{
		//make sure the two arrays are not the same
		if (this == &source)
		{
			return 0;
		}
		//make a new array
		value_type * temp = new value_type[source.capacity];
		//copy data
		for (int i = 0; i < source.used; i++)
		{
			temp[i] = source.data[i];
		}
		//return new array that was copied and delete temp array
		delete[] data;
		data = temp;
		temp = nullptr;
		delete[] temp;
		return *this;
	}

	// CONSTANT MEMBER FUNCTIONS
	// CONSTANT MEMBER FUNCTIONS for the sequence class:
	//   int size( ) const
	//     Postcondition: The return value is the number of items in the sequence.
	int size() const
	{
		return used;
	}

	//   bool is_item( ) const
	//     Postcondition: A true return value indicates that there is a valid
	//     "current" item that may be retrieved by activating the current
	//     member function (listed below). A false return value indicates that
	//     there is no valid current item.
	bool is_item() const
	{
		//check if there is an item
		if (current_index >= used){
			return false;
		} else {
			return true;
		}
	}

	//   value_type current( ) const
	//     Precondition: is_item( ) returns true.
	//     Postcondition: The item returned is the current item in the sequence.
	value_type current() const
	{
		//if there is an item to return then return it, otherwise return 0.
		if (is_item() == true)
		{
			return data[current_index];
		}
		else
		{
			return 0;
		}
	}
};
#endif


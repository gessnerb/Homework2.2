#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

class miniVector
{
public:
	miniVector(int size = 0);
	// constructor.
	// Postconditions: Allocates array with size number of elements and capacity. If no value is passed 
	//				  to the parameter, default value of 0 as shown is used. If size != 0, then 
	//				   all array elements are initialized to 0. 

	miniVector(const miniVector &obj);
	// copy constructor
	// Postcondition: creates current vector as a copy of obj passed to the function

	~miniVector();
	// destructor
	// Postcondition: the dynamic array is destroyed or returned back to the heap

	miniVector& operator=(const miniVector& rhs);
	// assignment operator.
	// Postcondition: current vector, i.e., the calling vector object holds the same data as rhs

	int& back();
	// return the element at the rear of the vector.
	// Precondition: the vector is not empty. if vector is empty, program is terminated

	int& operator[](int i);
	// provides general access to elements using an index.
	// Precondition: boundary checking is performed when accessing an array element using the subscript 
	// 			operator []; i.e., 0 <= i < vSize. if the index is out of range, program is terminated

	void push_back(const int& item);
	// insert item at the rear of the vector.
	// Postcondition: the vector size is increased by 1

	void pop_back();
	// remove element at the rear of the vector.
	// Precondition: vector is not empty. if the vector is empty, program is terminated

	int size() const;
	// Postcondition: returns current list size

	bool empty() const;
	// Postcondition: returns true if vector is empty and false otherwise

	int capacity() const;
	// Postcondition: returns the current capacity of the vector

private:
	int vCapacity;		// amount of available physical locations of the array
	int vSize;			// number of elements in the array the are currently used
	int *vArr;			// the pointer pointing to a dynamic array

	void reserve(int n, bool copy);
	// called by public functions only if n > vCapacity. 
	// Postcondition: expands the vector capacity to n elements, copies the existing elements to the 
	//  			 new array space if copy == true, and deletes the old dynamic array.
	// 				 terminates the program if memory allocation fails using assert function.
};
// *************************************************************************************************
// set the capacity to n elements
void miniVector::reserve(int n, bool copy)
{
	int *newArr;
	int i;

	// allocate a new dynamic array with n elements
	newArr = new int[n];
	assert(newArr != nullptr);
	// if copy is true, copy elements from the old list to the new list
	if (copy)
		for (i = 0; i < vSize; i++)
			newArr[i] = vArr[i];

	// delete original dynamic array. if vArr is NULL, the vetor was
	// originally empty and there is no memory to delete
	if (vArr != nullptr)
		delete[] vArr;

	// set vArr to the value newArr. update vCapacity
	vArr = newArr;
	vCapacity = n;
}
// *************************************************************************************************
// constructor, initializes vSize and vCapacity
// allocate a dynamic array of vSize integers
// and initialize the array with 0
miniVector::miniVector(int size) : vSize(0), vCapacity(0), vArr(NULL)
{
	int i;
	// if size is 0, vSize/vCapacity are 0 and vArr is NULL.just return
	if (size == 0)
		return;
	// set capacity to size. since we are building the vector,
	// copy is false because of new construction of an object
	reserve(size, false);
	// assign size to vSize
	vSize = size;
	// copy 0 into each vector element
	for (i = 0; i < vSize; i++)
		vArr[i] = 0;
}
// *************************************************************************************************
// copyconstructor, make the current object a copy of obj
// for starters, use initialization list to create an empty vector
miniVector::miniVector(const miniVector &obj) : vSize(0), vCapacity(0), vArr(nullptr)
{
	int i;
	// if size is 0, vSize/vCapacity are 0 and vArr is NULL; just return
	if (obj.vSize == 0)
		return;
	// set capacity to ojb.vSize. since we are building the vector,
	// copy is false because of new construction of an object
	reserve(obj.vSize, false);
	// assign size to obj.vSize
	vSize = obj.vSize;
	// copy items from the obj.vArr to the newlly allocated array
	for (i = 0; i < vSize; i++)
	{
		vArr[i] = obj.vArr[i];
	}
	cout << "Copy constructor called." << endl;
}
// *************************************************************************************************
// destructor;de-allocate the dynamic array
miniVector::~miniVector()
{
	cout << "Destructor called." << endl;
	if (vArr != nullptr)
	{
		// de-allocate memory for the array
		delete[] vArr;
		cout << "Dynamic memory location returned to heap." << endl;
	}
}
// *************************************************************************************************
// replace existing object(left-hand operand) by rhs (right-hand operand)
miniVector& miniVector::operator=(const miniVector& rhs)
{
	int i;
	// check vCapacity to see if a new array must be allocated
	if (vCapacity < rhs.vSize)
		// make capacity of current object the size of rhs
		// don't do a copy, since we will replace the old values
		reserve(rhs.vSize, false);
	// assign current object to have same size as rhs
	vSize = rhs.vSize;
	// copy items from rhs.vArr to vArr
	for (i = 0; i < vSize; i++)
		vArr[i] = rhs.vArr[i];
	return *this;
	cout << "Overloaded assignment operator called." << endl;
}
// *************************************************************************************************
// check vSize if the value is 0; otherwise return the element vArr[vSize - 1]
int& miniVector::back()
{
	if (vSize == 0)
	{
		cout << "The array is empty! The program will now close" << endl;
		exit(1);
	}
	return vArr[vSize - 1];
}
// *************************************************************************************************
// provides general access to array elements
int& miniVector::operator[](int i)
{
	if (i < 0 || i >= vSize)
	{
		cout << "\n Trying to access array element v[" << i << "]." << endl;
		cout << "The program will terminate because the value of the subscript is out of range!" << endl;
		exit(1);
	}
	return vArr[i];
}
// *************************************************************************************************
// ensure the list has sufficient capacity, add the new item to the list
// and increment vSize accordingly
void miniVector::push_back(const int &item)
{
	// if space is full, allocate more capacity
	if (vSize == vCapacity)
	{
		if (vCapacity == 0)
			reserve(1, false);
		else
			reserve(2 * vCapacity, true);
	}
	// add the item to the list and update vSize
	vArr[vSize] = item;
	vSize++;
}
// *************************************************************************************************
// if not empty, increment the size; logical deletion 
// meaning the item is not physically deleted
void miniVector::pop_back()
{
	if (vSize == 0)
	{
		cout << "The array is empty! The program will now close" << endl;
		exit(1);
	}
	vSize--;
}
// *************************************************************************************************
// returns size of the array
int miniVector::size()const
{
	return vSize;
}
// *************************************************************************************************
// returns vSize
bool miniVector::empty() const
{
	return vSize == 0;
}
// *************************************************************************************************
// returns vCapacity
int miniVector::capacity() const
{
	return vCapacity;
}
// *************************************************************************************************
class Time {
	friend ostream & operator <<(ostream &, const Time &);
public:
	Time();								// default constructor
	Time(int, int, int, int, int, int);	// 2nd constructor with 6 int-type parameters
	void setTime(int, int, int);
private:
	int hours;
	int minutes;
	int seconds;
};
// *************************************************************************************************
int main()
{
	miniVector Vec;
	cout << "The capacity of vec = " << Vec.capacity() << endl;
	cout << "The size of Vec = " << Vec.size() << endl;

	for (int i = 0; i < 5; i++)
		Vec.push_back((i + 1) * 10);
	// v[i] = (i + 1) * 10; cannot do this because of the [] function

	cout << "\nAfter inserting " << Vec.size() << " values into the array, the size of v is now = "
		<< Vec.size() << endl;
	cout << "The capacity of Vec = " << Vec.capacity() << endl;

	cout << "\nArray v contains:" << endl;
	for (int i = 0; i < Vec.size(); i++)
		cout << "Vec[" << i << "] = " << Vec[i] << endl;
	cout << Vec[8];
	return 0;
}
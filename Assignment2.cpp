#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
// stack class
template <typename t>
class Stack
{
private: // access modifier
    // introduce class variables
    t *myarray;             // pointer stores address of our array
    int capacity, elements; // variables that contain total capacity of array and total number of elements

    // function decreases capacity
    void shrink()
    {
        elements -= 1;
        t *new_array = new t[elements];
        capacity = elements;
        for (int index = 0; index < elements; index++) // transfer elements to new array
        {
            new_array[index] = myarray[index];
        }
        delete[] myarray;    // delete previous array
        myarray = new_array; // assign new array to the pointer
    }
    // function increases capacity
    void grow()
    {
        // cout << capacity << elements << endl;
        capacity += 1;                                       // as in vectors capacity doubles
        t *new_array = new t[capacity];                      // create new array
        for (int index = 0; index < (capacity - 1); index++) // transfer elements to new array
        {
            new_array[index] = myarray[index];
        }
        delete[] myarray;    // delete previous array
        myarray = new_array; // assign new array to the pointer
    }

public:
    Stack()
    { // default constructor
        myarray = new t[10];
        capacity = 1;
        elements = 0;
    }

    // checks whether stack is empty
    bool isEmpty()
    {
        if (capacity == 0)
        {
            return true;
        }
        return false;
    }

    // insert element at top
    void push(t value)
    {
        if (capacity == elements) // check whether array is full
        {
            grow(); // increase capacity of array
        }
        myarray[elements] = value; // add new data
        elements += 1;
    }

    // pop element at top
    t pop()
    {
        if (!isEmpty())
        {
            t popped = myarray[elements - 1];
            shrink();
            return popped;
        }
        return '0';
    }

    // display the contents of the top element of stack
    t Peak()
    {
        if (!isEmpty())
        {
            return myarray[elements - 1];
        }
        return '0';
    }

    // release the memory allocated by stack
    void clear()
    {
        delete[] myarray;
    }

    // get size of stack
    int getSize()
    {
        return capacity;
    }

    void display()
    {
        for (int i = 0; i < elements; i++)
        {
            cout << myarray[i];
        }
        cout << endl;
    }
};
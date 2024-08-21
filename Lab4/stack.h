#include <iostream>
#include <string>
#include <stdexcept>
using std::overflow_error;
using std::runtime_error;
using std::underflow_error;
using std::out_of_range;

template<class T>
class stack 
{
    private:
        static const int MAX_SIZE = 20;
        T data [MAX_SIZE];
        int size = 0; // effectively top of stack

    public:
        stack() {}; //inialize size as 0, constructor

        void push(const T& val) //push elements onto the stack
        {
            if ((size + 1) > MAX_SIZE) //checks if a push would overflow without incrementing size
            {
                throw overflow_error("Called push on full stack.");
            }
            data[size] = val; //set size position to value being pushed
            size++; //update top of stack
        }

        void pop() //"removes" the element off the top of the stack
        {
            if (empty()) //prevents size from going to -1 and popping nothing
            {
                throw underflow_error("Called pop on empty stack.");
            }
            size--;
        }

        void pop_two() //above but for top two elements of stack
        {
            if (empty()) //prevents size going to -2, can't pop two on an empty stack
            {
                throw out_of_range("Called pop_two on empty stack.");
            }
            else if (size == 1) //prevents size going to -1, can't pop 2 on 1 element 
            {
                throw out_of_range("Called pop_two on a stack of size 1.");
            }
            else
            {
                size -= 2; //reduce size by 2, ignoring the elements we popped off as they aren't included in the subarray that is the stack
            }
        }

        T& top() //returns the top of the stack without modifying it
        {
            if (empty()) //empty stack means no elements to look at
            {
                throw underflow_error("Called top on empty stack.");
            }
            return data[size -1];
        }

        const T& top() const //returns the top of the stack without modifying it, using const to ensure no modification 
        {
            if (empty()) //empty stack means no elements to look at
            {
                throw underflow_error("Called top on empty stack.");
            }
            return data[size -1];
        }

        bool empty() const //checks if stack is empty
        {
            return (size == 0); //return size == 0 bool
        }      
};
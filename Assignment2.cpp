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

// method returns true if the character is operator
bool isOperator(char a)
{
    if (a == '*' || a == '/' || a == '+' || a == '-' || a == '^')
        return true;
    return false;
}

// method returns true if character is a brace
bool isBrace(char a)
{
    if (a == '(' || a == '{' || a == '[' || a == ')' || a == '}' || a == ']')
        return true;
    return false;
}

// method returns precedance of operators
int OperatorsPrecedance(char a)
{
    if (a == '*' || a == '/')
        return 2;
    else if (a == '+' || a == '-')
        return 1;
    if (a == '^')
        return 3;
    return 4;
}

// method returns postfix version of expression
Stack<char> InfixToPostFix(string expression)
{
    Stack<char> operators;
    Stack<char> PostfixExpression;

    // for loop iterates over each character in the expression
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ') // character is a space
        {
            continue; // skip to next
        }

        else if (isdigit(expression[i])) // character is a digit
        {
            PostfixExpression.push(expression[i]);
        }

        else if (isOperator(expression[i])) // character is an operator
        {
            PostfixExpression.push(' ');
            if (OperatorsPrecedance(expression[i]) >= OperatorsPrecedance(operators.Peak())) // compares precendences and pops the preceding operators accordingly
            {
                PostfixExpression.push(operators.pop());
            }
            operators.push(expression[i]);
        }

        else if (isBrace(expression[i])) // character is a brace
        {

            if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']') // for closing brace
            {
                if (operators.isEmpty())
                {
                    cout << "The Expression entered is not correct. Program will terminate";
                    exit(0);
                    ;
                }
                char OpeningBrace = ' ';
                switch (expression[i]) // assign appropriate opening bracket
                {
                case ')':
                    OpeningBrace = '(';
                    break;
                case '}':
                    OpeningBrace = '{';
                    break;
                case ']':
                    OpeningBrace = '[';
                    break;
                }
                while (OpeningBrace != operators.Peak()) // pop until opening bracket is met
                {

                    PostfixExpression.push(' ');
                    char x = operators.pop();
                    PostfixExpression.push(x);
                    if (operators.isEmpty() & x != OpeningBrace)
                    {
                        cout << "The Expression entered is not correct. Program will terminate";
                        exit(0);
                    }
                }
                operators.pop(); // pop the opening base
            }
            else
            { // for opening brace
                operators.push(expression[i]);
            }
        }
    }

    while (!operators.isEmpty()) // pop out remaining operators
    {
        PostfixExpression.push(' ');
        PostfixExpression.push(operators.pop());
    }
    return PostfixExpression;
}

// method for calculating 2 number evaluations
float Evaluate(float a, float b, char o)
{
    switch (o)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return pow(a, b);
}
// method evaluates result of postfix expression
float Result(Stack<char> postfixExpression)
{
    Stack<float> result;
    Stack<char> temp;
    while (!postfixExpression.isEmpty()) // reversing the postfix expression stack for ease
    {
        temp.push(postfixExpression.pop());
    }
    while (!temp.isEmpty()) // iterating over the stack
    {
        if (isdigit(temp.Peak())) // if digit
        {
            string s = "";
            int power = -1;
            while (temp.Peak() != ' ')
            {
                s += temp.pop();
                power++;
            }
            temp.pop();
            float num = 0;
            for (int i = 0; i < s.length(); i++) // convert char digits to equivalent int
            {
                float x = s[i] - '0';
                num += x * pow(10, power);
                power--;
            }
            result.push(num);
        }
        else if (isOperator(temp.Peak())) // if operator
        {
            float a = Evaluate(result.pop(), result.pop(), temp.pop()); // perform specified operation
            result.push(a);                                             // pop back result into the stack
        }
        else
        {
            temp.pop();
        }
    }
    return result.pop(); // pop final result
}

int main()
{
    string expression;
    cout << "Enter Expression: ";
    getline(cin, expression);
    cout << "Postfix Expression: ";
    InfixToPostFix(expression).display();
    printf("Answer: %-10.2f", Result(InfixToPostFix(expression)));
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

class Stack
{
    private:
        int top;
        int capacity;
        char* array;
    
    public:
        Stack(int size) : top(-1), capacity(size) 
        {
            array = (char *)malloc(capacity * sizeof(char));
        }

        ~Stack()
        {
            free(array);
        }

        void push(char a)
        {
            if (top < capacity - 1)
                array[++top] = a;
        }

        void pop()
        {
            if (!isEmpty())
                top--;
        }

        char peek()
        {
            if (isEmpty())
                return 0;
            return array[top];
        }

        bool isEmpty()
        {
            return top == -1;
        }
};

bool isCorrect(string s)
{
    Stack stack(s.length());
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            stack.push('(');
        }
        else if (s[i] == ')')
        {
            stack.pop();
        }
    }

    return stack.isEmpty();
}

int main(void)
{
    string parentheses;
    cin >> parentheses;

    if (isCorrect(parentheses))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
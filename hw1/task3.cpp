/*
Реализовать очередь с динамическим зацикленным буфером.

Обрабатывать команды push back и pop front.

Формат ввода
В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
*/

#include <iostream>
#include <string>

class Queue 
{
    public:
        int* arr = NULL;
        int front = 0;
        int rear = 0;
        int size = -1;
        int capacity = 0;

        Queue(int size);
        ~Queue();

        int popFront();
        void pushBack(int n);
        bool isFull();
        bool isEmpty();
};

Queue::Queue(int new_size) 
{
    capacity = new_size;
    arr = new int[capacity];
    front = 0;
    rear = 0;
    size = 0;
}

Queue::~Queue() 
{
    delete[] arr;
}

bool Queue::isFull() 
{
    return size == capacity;
}

bool Queue::isEmpty() 
{
    return size == 0;
}

int Queue::popFront() 
{
    if (isEmpty()) 
        return -1;

    int element = arr[front];
    front = (front + 1) % capacity;
    size--;
    return element;
}

void Queue::pushBack(int n) 
{
    if (isFull()) 
    {
        // std::cout << "realloc\n" << std::endl;
        // перевыделение памяти
        int* newArr = new int[capacity * 2];
        
        // копирование в новый массив
        for (int i = 0; i < size; i++) 
        {
            newArr[i] = arr[(front + i) % capacity];
        }
        
        delete[] arr;
        arr = newArr;
        front = 0;
        rear = size;
        capacity *= 2;
    }

    arr[rear] = n;
    rear = (rear + 1) % capacity;
    size++;
}

int main() 
{
    int initial_size = 4;
    Queue q(initial_size);

    int n;

    scanf("%d", &n);

    // переменная для ответа
    std::string answer = "YES";

    // чтение входных данных
    for (int i = 0; i < n; i++)
    {
        int action, num;
        action = num = 0;
        scanf("%d %d", &action, &num);
        if (action == 2)
        {
            if (q.popFront() != num)
                answer = "NO";
        }
        else if (action == 3)
            q.pushBack(num);
    
    }

    std::cout << answer << std::endl;

    return 0;
}

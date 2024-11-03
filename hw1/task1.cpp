/*
Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях.
Позиции битов нумеруются с 0.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.

Формат ввода
Входное число лежит в диапазоне 0..2^32-1 и вводится в десятичном виде.

Формат вывода
Целое число - количество бит
*/

#include <iostream>

int count_even_bits(unsigned int number)
{
    int count = 0;

    while(number != 0)
    {
        count += number & 1;
        number >>= 2;
    }

    return count;
}

int main(void)
{
    unsigned int number;
    
    std::cin >> number;
    
    std::cout << count_even_bits(number) << std::endl;

    return 0;
}

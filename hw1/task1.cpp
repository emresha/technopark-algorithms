#include <iostream>

int main()
{
    unsigned int number;
    int count = 0;
    
    std::cin >> number;
    
    while(number != 0)
    {
        count += number & 1;
        number >>= 2;
    }
    
    std::cout << count << std::endl;

    return 0;
}
#include <iostream>
#include <string>
#define RESIZE_PERCENTAGE 0.75
#define DEL "DEL"

class HashMap
{
private:
    long long length;
    long long capacity;
    std::string *arr;
    long long p;

    long long calc_hash(const std::string &s, long long p, long long size)
    {
        long long h = 0;
        for (char c : s)
        {
            h = (h * p + c) % size;
        }
        return h;
    }

    // поиск для вставки
    long long find_index_insert(std::string *array, long long size, const std::string &key)
    {
        long long hash = calc_hash(key, p, size);
        long long i = 0;
        long long probe = hash;

        while (i < size)
        {
            probe = (probe + i) % size;

            if (array[probe].empty() || array[probe] == DEL)
                return probe;

            i++;
        }

        return -1;
    }

    // обычный поиск
    long long find_index(const std::string &key)
    {
        long long hash = calc_hash(key, p, capacity);
        long long i = 0;
        long long probe = hash;

        while (i < capacity)
        {
            probe = (probe + i) % capacity;

            if (arr[probe] == key)
            {
                return probe;
            }

            if (arr[probe].empty())
            {
                return -1;
            }

            if (arr[probe] == DEL)
            {
                i++;
                continue;
            }

            i++;
        }

        return -1;
    }

    void grow(void)
    {
        // создаём массив, который в конце увеличения заменит исходный
        long long new_capacity = capacity * 2;
        std::string *tmp = new std::string[new_capacity];
        for (long long i = 0; i < new_capacity; i++)
            tmp[i] = "";
        // std::cout << "RESIZE" << std::endl;

        // пробегаемся по всему прошлому массиву и копируем непустые значение
        for (long long i = 0; i < capacity; i++)
        {
            if (!arr[i].empty() && arr[i] != DEL)
            {
                tmp[find_index_insert(tmp, new_capacity, arr[i])] = arr[i];
            }
        }

        delete[] arr;

        arr = tmp;

        capacity = new_capacity;
    }

public:
    HashMap(long long new_capacity = 8)
    {
        length = 0;
        capacity = new_capacity;
        arr = new std::string[capacity];
        for (long long i = 0; i < capacity; i++)
            arr[i] = "";
        p = 2337537353;
    }

    ~HashMap(void)
    {
        delete[] arr;
    }

    bool Has(std::string key)
    {
        return find_index(key) != -1;
    }

    int Add(std::string key)
    {
        if (Has(key))
            return -1;

        if ((double)(length + 1) / capacity >= RESIZE_PERCENTAGE)
            grow();

        arr[find_index_insert(arr, capacity, key)] = key;

        length++;

        return 0;
    }

    int Delete(std::string key)
    {
        if (!Has(key))
            return -1;

        arr[find_index(key)] = DEL;
        length--;

        return 0;
    }

    // для служебного использования:)
    // void Print(void)
    // {
    //     std::cout << "LEN: " << length << std::endl;
    //     for (long long i = 0; i < capacity; i++)
    //     {
    //         std::cout << arr[i] << " at " << i << std::endl;
    //     }
    // }
};

int main(void)
{
    char action;
    std::string key;

    HashMap map;

    while (std::cin >> action >> key)
    {
        int res;
        bool res_b;

        switch (action)
        {
        case '?':
            res_b = map.Has(key);
            std::cout << (res_b ? "OK" : "FAIL") << std::endl;
            break;
        case '+':
            res = map.Add(key);
            std::cout << (res ? "FAIL" : "OK") << std::endl;
            break;
        case '-':
            res = map.Delete(key);
            std::cout << (res ? "FAIL" : "OK") << std::endl;
            break;
        // case 'p':
        //     map.Print();
        //     break;
        default:
            break;
        }
    }

    return 0;
}

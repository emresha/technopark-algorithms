#include <iostream>
#include <string>
#define RESIZE_PERCENTAGE 0.75
#define DELETED "<DELETED>"

long long calc_hash(const std::string &s, long long p, long long size)
{
    long long h = 0;
    for (char c : s)
    {
        h = (h * p + c) % size;
    }
    return h;
}

class HashMap
{
private:
    long long capacity;
    long long length;
    std::string *arr;
    long long p;

    long long find_slot(const std::string &str, bool for_insertion)
    {
        long long hash = calc_hash(str, p, capacity);
        long long i = 0;

        while (i < capacity)
        {
            long long index = (hash + i * i) % capacity;

            if (arr[index].empty() || arr[index] == DELETED)
            {
                if (for_insertion)
                    return index;
                if (arr[index].empty())
                    return -1;
            }

            if (arr[index] == str)
                return index;
            i++;
        }

        return -1;
    }

    void resize()
    {
        long long old_capacity = capacity;
        long long new_length = 0;
        capacity *= 2;
        std::string *new_arr = new std::string[capacity];

        for (long long i = 0; i < old_capacity; i++)
        {
            if (!arr[i].empty() && arr[i] != DELETED)
            {
                long long new_index = calc_hash(arr[i], p, capacity);
                long long probe = 0;

                while (!new_arr[(new_index + probe * probe) % capacity].empty())
                {
                    probe++;
                }
                new_arr[(new_index + probe * probe) % capacity] = arr[i];
                new_length++;
            }
        }

        delete[] arr;
        length = new_length;
        arr = new_arr;
    }

public:
    HashMap()
    {
        capacity = 8;
        length = 0;
        arr = new std::string[capacity];
        p = 2337537353;
    }

    ~HashMap()
    {
        delete[] arr;
        arr = nullptr;
    }

    int Add(const std::string &str)
    {
        if (Has(str))
            return 1;

        if ((double)(length + 1) / capacity >= RESIZE_PERCENTAGE)
        {
            // std::cout << "resize" << std::endl;
            resize();
        }

        long long index = find_slot(str, true);
        if (index != -1)
        {
            arr[index] = str;
            length++;
            return 0;
        }
        return 1;
    }

    bool Has(const std::string &str)
    {
        return find_slot(str, false) != -1;
    }

    int Delete(const std::string &str)
    {
        long long index = find_slot(str, false);

        if (index == -1)
            return 1;
        arr[index] = DELETED;
        length--;
        return 0;
    }
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
        default:
            break;
        }
    }

    return 0;
}

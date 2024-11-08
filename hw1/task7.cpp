/*
Дан массив неотрицательных целых 64-битных чисел.
Количество чисел не больше 1000000. 
Отсортировать массив методом поразрядной сортировки LSD по байтам.
*/

#include <iostream>
#include <cstdint>

void counting_sort(uint64_t *arr, int size, int shift)
{
    int base = 256;
    int count[256] = {0};
    uint64_t *out = (uint64_t *)malloc(sizeof(u_int64_t) * size);

    for (int i = 0; i < size; i++)
    {
        int digit = (arr[i] >> shift) & (base - 1);
        count[digit]++;
    }

    for (int i = 1; i < base; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        int digit = (arr[i] >> shift) & (base - 1);
        out[--count[digit]] = arr[i];
    }

    for (int i = 0; i < size; i++)
        arr[i] = out[i];

    free(out);

    return;
}

void LSD_sort(uint64_t *arr, int size)
{
    int max_bits = 64;

    for (int shift = 0; shift < max_bits; shift += 8)
        counting_sort(arr, size, shift);

    return;
}

int main(void)
{
    int n;

    std::cin >> n;
    uint64_t *arr = (uint64_t *)malloc(sizeof(uint64_t) * n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    LSD_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    free(arr);

    return 0;
}
/*
Дано множество целых чисел из [0..10^9] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль
Реализуйте стратегию выбора опорного элемента “случайный элемент”.
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <ctime>

template <typename T>
int partition(T *arr, int left, int right, bool (*cmp)(T, T))
{
    int pivot_index = left + rand() % (right - left + 1);

    T pivot_value = arr[pivot_index];
    std::swap(arr[pivot_index], arr[right]);

    int i = left;
    for (int j = left; j < right; ++j)
    {
        if (cmp(arr[j], pivot_value))
        {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }

    std::swap(arr[i], arr[right]);

    return i;
}

template <typename T>
T quickselect(T *arr, int left, int right, int k, bool (*cmp)(T, T))
{
    while (left <= right)
    {
        int pivot_index = partition(arr, left, right, cmp);
        if (pivot_index == k)
            return arr[pivot_index];
        else if (pivot_index < k)
            left = pivot_index + 1;
        else
            right = pivot_index - 1;
    }
    return arr[left];
}

template <typename T>
void find_statistics(T *arr, int size, bool (*cmp)(T, T), T *ten, T *median, T *ninety)
{
    *ten = quickselect(arr, 0, size - 1, size / 10, cmp);
    *median = quickselect(arr, 0, size - 1, size / 2, cmp);
    *ninety = quickselect(arr, 0, size - 1, 9 * size / 10, cmp);
}

template <typename T>
bool cmpare(T a, T b)
{
    return a < b;
}

int main()
{
    std::srand(std::time(0));

    int n;
    std::cin >> n;

    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int ten_percentile, median, ninety_percentile;

    find_statistics(arr, n, cmpare<int>, &ten_percentile, &median, &ninety_percentile);

    std::cout << ten_percentile << '\n' << median << '\n' << ninety_percentile << std::endl;

    free(arr);

    return 0;
}

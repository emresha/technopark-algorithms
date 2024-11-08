/*
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. 
Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
*/

#include <iostream>

struct Segment
{
    int left;
    int right;
};

static void print_segment_arr(const struct Segment *arr, const int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i].left << " " << arr[i].right << std::endl;
    }

    return;
}

bool cmp(struct Segment first, struct Segment second)
{
    return first.left <= second.left;
}

template <typename T>
void merge(T *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T *L = (T *)malloc(sizeof(T) * n1);
    T *R = (T *)malloc(sizeof(T) * n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (cmp(L[i], R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

template <typename T>
void merge_sort(T *arr, int left, int right, bool (*cmp)(T, T))
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid, cmp);
    merge_sort(arr, mid + 1, right, cmp);
    merge(arr, left, mid, right);
}

int count_paint(struct Segment *arr, int size)
{
    if (size == 0)
        return 0;

    int total_length = arr[0].right - arr[0].left;
    int current_end = arr[0].right;

    for (int i = 1; i < size; i++)
    {
        if (arr[i].left > current_end)
        {
            total_length += arr[i].right - arr[i].left;
            current_end = arr[i].right;
        }
        else if (arr[i].right > current_end)
        {
            total_length += arr[i].right - current_end;
            current_end = arr[i].right;
        }
    }

    return total_length;
}

int main(void)
{
    int n;
    std::cin >> n;

    struct Segment *segments = (struct Segment *)malloc(sizeof(struct Segment) * n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> segments[i].left >> segments[i].right;
    }

    merge_sort(segments, 0, n - 1, cmp);

    // print_segment_arr(segments, n);
    
    std::cout << count_paint(segments, n) << std::endl; 

    free(segments);

    return 0;
}

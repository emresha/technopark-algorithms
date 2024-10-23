#include <iostream>
#include <vector>

static int exponentialSearch(int *a, int n, int current)
{
    int bin_search_begin = 0, bin_search_end = 1;
    if (a[0] >= current)
    {
        return 0;
    }

    while (bin_search_end < n && a[bin_search_end] < current)
    {
        bin_search_begin = bin_search_end;
        bin_search_end *= 2;
    }

    if (bin_search_end >= n)
        bin_search_end = n - 1;

    return bin_search_end;
}

static int binarySearch(int *a, int bin_beg, int bin_end, int current)
{
    int result = bin_end + 1;

    while (bin_beg <= bin_end)
    {
        int mid = (bin_beg + bin_end) / 2;
        if (a[mid] >= current)
        {
            result = mid;
            bin_end = mid - 1;
        }
        else
        {
            bin_beg = mid + 1;
        }
    }

    return result;
}

int main(void)
{
    int n, m;

    scanf("%d %d", &n, &m);

    int *a = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }

    int *b = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; ++i)
    {
        scanf("%d", &b[i]);
    }

    for (int i = 0; i < m; ++i)
    {
        int current = b[i];
        int bin_search_end = exponentialSearch(a, n, current);
        int bin_search_begin = bin_search_end / 2;

        int result = binarySearch(a, bin_search_begin, bin_search_end, current);

        printf("%d ", result);
    }

    printf("\n");

    free(a);
    free(b);

    return 0;
}

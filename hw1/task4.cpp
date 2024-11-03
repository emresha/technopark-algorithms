/*
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт,
и выводит их в порядке возрастания посещаемости.
Количество заходов и идентификаторы пользователей не повторяются.
*/

#include <iostream>
#include <functional>

struct UserFreq
{
    int id;
    int frequency;

    friend std::ostream& operator<<(std::ostream& os, const UserFreq& uf) 
    {
        os << uf.id;
        return os;
    }
};

struct FrequencyComparator {
    bool operator()(const UserFreq& lhs, const UserFreq& rhs) const 
    {
        return lhs.frequency < rhs.frequency;
    }
};

template <typename T, typename Comparator> 
class Heap
{
    public:
        Heap(size_t size)
        {
            max_size = size;
            arr = (T*)malloc(sizeof(T) * size);
        }

        ~Heap()
        {
            free(arr);
        }

        void Print(size_t index)
        {
            while (current_size)
            {
                std::cout << Extract() << ' ';
            }

            std::cout << std::endl;
        }

        void Add(T elem)
        {
            if (current_size == max_size)
            {
                if (cmp(arr[0], elem))
                    arr[0] = elem;

                siftDown(0);
            }
            else
            {
                arr[current_size] = elem;
                // printf("sift up\n");
                siftUp(current_size);
                current_size++;
            }
        }

        T Extract(void)
        {
            T extracted = arr[0];
            std::swap(arr[0], arr[current_size - 1]);
            current_size--;
            siftDown(0);

            return extracted;
        }

    private:
        void siftDown(size_t index)
        {
            while (true)
            {
                int left_child = index * 2 + 1;
                int right_child = index * 2 + 2;

                int smallest = index;

                if (left_child < current_size && cmp(arr[left_child], arr[smallest]))
                    smallest = left_child;

                if (right_child < current_size && cmp(arr[right_child], arr[smallest]))
                    smallest = right_child;

                if (smallest != index)
                {
                    std::swap(arr[index], arr[smallest]);
                    index = smallest;
                }
                else
                    break;
            }
        };

        void siftUp(size_t index)
        {
            while (index > 0)
            {
                int parent = (index - 1) / 2;
                if (!cmp(arr[index], arr[parent]))
                    break;

                std::swap(arr[index], arr[parent]);
                index = parent;
            }
        }

        T *arr;
        Comparator cmp;
        size_t current_size = 0;
        size_t max_size;
};

int int_comparator(int l, int r)
{
    return l - r;
}

int main(void)
{
    size_t n = 0, k = 0;

    std::cin >> n;
    std::cin >> k;

    Heap<UserFreq, FrequencyComparator> heap(k);

    for (size_t i = 0; i < n; i++)
    {
        struct UserFreq user;
        std::cin >> user.id >> user.frequency;

        heap.Add(user);
    }

    heap.Print(0);

    return 0;
}
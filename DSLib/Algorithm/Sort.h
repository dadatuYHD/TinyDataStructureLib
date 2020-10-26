#ifndef SORT_H
#define SORT_H

#include "Object/Object.h"
#include "Array/Array.h"

namespace DSLib {

#define DESCENDING 0
#define ASCENDING  1

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator = (const Sort&);

    template <typename T>
    static void swap(T& a, T& b)
    {
        T c = a;

        a = b;
        b = c;
    }

    template <typename T>
    static void merge(T * src,  T * helpArray, int begin, int mid, int end, bool type = ASCENDING)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while ((i <= mid) && (j <= end))
        {
            if (type ? (src[i] < src[j]) : (src[i] > src[j]))
            {
                helpArray[k++] = src[i++];
            }
            else
            {
                helpArray[k++] = src[j++];
            }
        }

        while (i <= mid)
        {
            helpArray[k++] = src[i++];
        }

        while (j <= end)
        {
            helpArray[k++] = src[j++];
        }

        for (i = begin; i <= end; i++)
        {
            src[i] = helpArray[i];
        }
    }

    template <typename T>
    static void merge(T * src,  T * helpArray, int begin, int end, bool type = ASCENDING)
    {
        if (begin < end)
        {
            int mid = (begin + end) / 2;
            merge(src, helpArray, begin, mid, type);
            merge(src, helpArray, mid + 1, end, type);
            merge(src, helpArray, begin, mid, end, type);
        }
    }

    template <typename T>
    static int partition(T *array,  int begin, int end, bool type)
    {
        T baseValue = array[begin];

        while (begin < end)
        {
            while ((end > begin) && (type ? (array[end] > baseValue) : (array[end] < baseValue)))
            {
                end--;
            }

            swap(array[end], array[begin]);

            while ((begin < end) && (type ? (array[begin] < baseValue) : (array[begin] > baseValue)))
            {
                begin++;
            }

            swap(array[begin], array[end]);
        }

        array[begin] = baseValue;

        return begin;
    }

    template <typename T>
    static void quick(T *array,  int begin, int end, bool type)
    {
        if (begin < end)
        {
            int pivot = partition(array, begin, end, type);

            quick(array, begin, pivot - 1, type);
            quick(array, pivot + 1, end, type);
        }
    }

public:
    template <typename T>
    static void select(T *array, int len, bool type = ASCENDING)  //O(N2)
    {
        for (int i = 0; i < len; i++)
        {
            int min = i;

            for (int j = i + 1; j < len; j++)
            {
                if ((type ? (array[min] > array[j]) : (array[min] < array[j])))
                {
                    min = j;
                }
            }

            if (min != i)
            {
                swap(array[min], array[i]);
            }
        }
    }

    template <typename T>
    static void select(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        select(array.GetArray(), array.length(), type);
    }

#define REVERSE_INSERT 1
    template <typename T>
    static void insert(T *array, int len, bool type = ASCENDING)  //O(N2)
    {
        for (int i = 1; i < len; i++)
        {
            int index = i;
            T temp = array[i];
#if REVERSE_INSERT
            for (int j = i - 1; (j >= 0) && (type ? (temp < array[j]) : (temp > array[j])); j--)
            {
                array[j + 1] = array[j];
                index = j;
            }
#else
            for (int j = 0; j < i; j++)
            {
                if ((type ? (temp < array[j]) : (temp > array[j])))
                {
                    while (index > j)
                    {
                        array[index] = array[index - 1];
                        index--;
                    }
                    index = j;
                    break;
                }
            }
#endif
            if (index != i) array[index] = temp;
        }
    }

    template <typename T>
    static void insert(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        insert(array.GetArray(), array.length(), type);
    }

    template <typename T>
    static void bubble(T *array, int len, bool type = ASCENDING)   //O(N2)
    {
        bool isChange = true;

        for (int i = 0; (i < len) && isChange; i++)
        {
            isChange = false;
            for (int j = len - 1; j > i; j--)
            {
                if (type ? (array[j] < array[j - 1]) : (array[j] > array[j - 1]))
                {
                    swap(array[j], array[j - 1]);
                    isChange = true;
                }
            }
        }
    }

    template <typename T>
    static void bubble(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        bubble(array.GetArray(), array.length(), type);
    }

    template <typename T>
    static void shell(T *array, int len, bool type = ASCENDING)   //O(N1.5)
    {
        int d = len;

        do
        {
            d = d / 3 + 1;

            for (int i = d; i < len; i += d)
            {
                int index = i;
                T temp = array[i];

                for (int j = i - d; (j >= 0) && (type ? (temp < array[j]) : (temp > array[j])); j -= d)
                {
                    array[j + d] = array[j];
                    index = j;
                }

                if (index != i) array[index] = temp;
            }

        }while (d > 1);
    }

    template <typename T>
    static void shell(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        shell(array.GetArray(), array.length(), type);
    }

    template <typename T>
    static void merge(T *array,  int len, bool type = ASCENDING)//O(n*logn)
    {
        T * helpArray = new T[len];

        merge(array, helpArray, 0, len - 1, type);

        delete [] helpArray;
    }

    template <typename T>
    static void merge(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        merge(array.GetArray(), array.length(), type);
    }

    template <typename T>
    static void quick(T *array,  int len, bool type = ASCENDING) //O(n*logn)
    {
        quick(array, 0, len - 1, type);
    }

    template <typename T>
    static void quick(Array<T>& array, bool type = ASCENDING)  //O(N2)
    {
        quick(array.GetArray(), array.length(), type);
    }
};

}

#endif // SORT_H

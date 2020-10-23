#ifndef SORT_H
#define SORT_H

#include "Object/Object.h"

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
};

}

#endif // SORT_H

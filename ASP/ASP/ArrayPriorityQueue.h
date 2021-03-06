#pragma once

#include <iostream>
#include <stdexcept>

#include "Queue.h"
template<class T>
class ArrayPriorityQueue : public Queue<T>
{
    int size;
    int maxSize;
    T* array;

    void ExpandQueue();
    int GetFirstElementPosition() const;
public:
    ArrayPriorityQueue(int maxSize = 20);

    void Add(const T& item);

    T Remove();

    T Peek() const;

    bool IsEmpty() const;

    bool IsFull() const;

    int Size() const;

    ~ArrayPriorityQueue();
};

template<class T>
ArrayPriorityQueue<T>::ArrayPriorityQueue(int maxSize) : size(0), maxSize(maxSize)
{
    array = new T[maxSize];
}

template<class T>
void ArrayPriorityQueue<T>::ExpandQueue()
{
    try
    {
        T* temp = array;
        array = new T[2 * maxSize];

        for (int i = 0; i < maxSize; i++)
            array[i] = temp[i];

        maxSize *= 2;

        delete[] temp;
    }
    catch (std::bad_alloc e)
    {
        std::cout << e.what() << "\n";
    }
}

template<class T>
int ArrayPriorityQueue<T>::GetFirstElementPosition() const
{
    int max = 0;
    for (int i = 1; i < size; i++)
        if (array[i] > array[max])
            max = i;
    return max;
}

template<class T>
void ArrayPriorityQueue<T>::Add(const T& item)
{
    if (IsFull())
    {
        ExpandQueue();
    }

    array[size++] = item;
}

template<class T>
T ArrayPriorityQueue<T>::Remove()
{
    if (IsEmpty()) throw std::exception("The queue is empty");


    int max = GetFirstElementPosition();

    T removedItem = array[max];
    array[max] = array[size - 1];
    size--;

    return removedItem;
}


template<class T>
T ArrayPriorityQueue<T>::Peek() const
{
    if (IsEmpty()) throw std::exception("The queue is empty");

    int max = GetFirstElementPosition();
    return array[max];
}

template<class T>
bool ArrayPriorityQueue<T>::IsEmpty() const
{
    return size == 0;
}

template<class T>
bool ArrayPriorityQueue<T>::IsFull() const
{
    return size == maxSize;
}

template<class T>
int ArrayPriorityQueue<T>::Size() const
{
    return size;
}

template<class T>
ArrayPriorityQueue<T>::~ArrayPriorityQueue()
{
    delete[] array;
    size = 0;
}
#pragma once
#include "ArrayException.h"
#include <iostream>
using namespace std;
const int DEFAULT_CAPACITY = 10;
template <typename T>
class Array
{
    T *ptr;
    int size, capacity;

public:
    T &operator[](int index);
    void insert(const T &element, int index);
    void insert(const T &element);
    void remove(int index);
    explicit Array(int startCapacity = DEFAULT_CAPACITY);
    ~Array();
    Array(const Array<T> &arr);
    Array<T> &operator=(const Array<T> &arr);
    void increaseCapacity(int newCapacity);
    int getSize() const;
    template <typename U>
    friend ostream &operator<<(ostream &out, const Array<U> &arr);
};
template <typename T>
Array<T>::Array(int startCapacity)
{
    if (startCapacity <= 0)
    {
        capacity = DEFAULT_CAPACITY;
    }
    else
    {
        capacity = startCapacity;
    }
    ptr = new T[capacity];
    size = 0;
}

template <typename T>
Array<T>::~Array()
{
    delete[] ptr;
    size = 0;
    capacity = DEFAULT_CAPACITY;
}

template <typename T>
Array<T>::Array(const Array<T> &arr)
{
    ptr = new T[arr.capacity];
    size = arr.size;
    capacity = arr.capacity;
    for (int i = 0; i < arr.size; i++)
    {
        ptr[i] = arr.ptr[i];
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &arr)
{
    if (this == &arr)
    {
        return *this;
    }
    if (capacity != arr.capacity)
    {
        delete[] ptr;
        ptr = new T[arr.capacity];
        capacity = arr.capacity;
    }
    size = arr.size;
    for (int i = 0; i < size; i++)
    {
        ptr[i] = arr.ptr[i];
    }
    return *this;
}

template <typename T>
T &Array<T>::operator[](int index)
{
    if (index >= size || index < 0)
    {
        throw ArrayException();
    }
    else
    {
        return ptr[index];
    }
}

template <typename T>
void Array<T>::insert(const T &element, int index)
{
    if (index < 0 || index > size)
    {
        throw ArrayException();
    }
    if (size == capacity)
    {
        increaseCapacity(capacity * 2);
    }
    for (int j = size - 1; j >= index; j--)
    {
        ptr[j + 1] = ptr[j];
    }
    size++;
    ptr[index] = element;
}

template <typename T>
void Array<T>::insert(const T &element)
{
    insert(element, size);
}

template <typename T>
void Array<T>::increaseCapacity(int newCapacity)
{
    capacity = newCapacity;
    T *newPtr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        newPtr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = newPtr;
}

template <typename T>
void Array<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        throw ArrayException();
    }
    for (int j = index; j < size - 1; j++)
    {
        ptr[j] = ptr[j + 1];
    }
    ptr[size - 1] = T();
    size--;
}

template <typename T>
int Array<T>::getSize() const
{
    return size;
}

template <typename T>
ostream &operator<<(ostream &out, const Array<T> &arr)
{
    out << "Total size: " << arr.size << endl;
    for (int i = 0; i < arr.size; i++)
    {
        out << arr.ptr[i] << endl;
    }
    return out;
}
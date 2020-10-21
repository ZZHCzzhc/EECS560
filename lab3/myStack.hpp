#ifndef _MYSTACK_H
#define _MYSTACK_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
template <typename T>
class myStack
{  
private:
    int capacity;
    int theSize;
    T* m_top;

    void init()
    {
        theSize = 0;
        capacity = 10;
        m_top = new T[10];
    }
    void resize()
    {
        if(theSize == capacity)
        {
            capacity = capacity*2;
            T* temp = new T[capacity];
            for(int i = 0; i < theSize; i++)
                temp[i] = m_top[i];

            swap(m_top, temp);
            delete[] temp;
        }
    }

public:
    myStack()
    {
        init();
    }

    ~myStack()
    {

        if (m_top != nullptr)
            delete[] m_top;
        m_top = nullptr;
    }

    myStack(myStack &&rhs) : theSize{rhs.theSize}, capacity{rhs.capacity}, m_top{rhs.m_top}
    {
        rhs.theSize = 0;
        rhs.m_top = nullptr;
    }

    myStack &operator=(myStack &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(m_top, rhs.m_top);
        return *this;
    }

    myStack(const myStack<T> &rhs)
    {
        init();
        for (int i = 0; i < rhs.theSize; i++)
        {
            push(rhs.m_top[i]);
        }

    }

    myStack &operator=(const myStack &rhs)
    {
        myStack copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    void push(T &x)
    {
        m_top[theSize] = x;
        theSize++;
        resize();
    }

    T pop()
    {
        if(empty())
            throw std::runtime_error("Empty Stack\n");
        T temp = m_top[theSize-1];
        theSize--;
        return temp;
    }

    T top()
    {
        return m_top[theSize-1];
    }

    bool empty()
    {
        return (theSize == 0);
    }

    void clear()
    {
        theSize = 0;
    }
};
#endif

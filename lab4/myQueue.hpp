#ifndef _MYQUEUE_H
#define _MYQUEUE_H
#include <iostream>
#include <vector>
#include <algorithm>
template <typename T>
class myQueue
{
private:
    int capacity;
    int theSize;
    T *m_front;
    int frnt;
    int back;

    void init()
    {
        theSize = 0;
        capacity = 10;
        m_front = new T[10];
        frnt = back = -1;
    }
    void resize()
    {
        if (theSize == capacity)
        {
            capacity = capacity * 2;
            T *temp = new T[capacity];
            int f = frnt;
            int i = 0;
            while (i != theSize)
            {
                temp[i] = m_front[f];
                i++;
                f++;
                if(f == theSize)
                    f = 0;
            }
            swap(m_front, temp);
            delete[] temp;
            frnt = 0;
            back = theSize - 1;
        }
    }

public:
    myQueue()
    {
        init();
    }
    ~myQueue()
    {
        std::cout << "q1\n";
        if (m_front != nullptr)
            delete[]  m_front;
        m_front = nullptr;
        std::cout << "q2\n";
    }
    myQueue(myQueue &&rhs): theSize{rhs.theSize}, capacity{rhs.capacity},  m_front{rhs.m_front}, frnt{rhs.frnt}, back{rhs.back}
    {
        rhs.theSize = 0;
        frnt = 0;
        back = 0;
        rhs.m_front = nullptr;
    }
    myQueue &operator=(myQueue &&rhs)
    {
        std::swap(theSize, rhs.theSize);
        std::swap(m_front, rhs.m_front);
        std::swap(frnt, rhs.frnt);
        std::swap(back, rhs.back);
        return *this;
    }
    myQueue(const myQueue<T> &rhs)
    {
        init();
        int f = rhs.frnt;
        for (int i = 0; i < rhs.theSize; i++)
        {
            enqueue(rhs.m_front[f]);
            f++;
            if(f == rhs.capacity)
                f = 0;
        }
    }
    myQueue &operator=(const myQueue &rhs)
    {
        myQueue copy(rhs);
        std::swap(*this, copy);
        return *this;
    }
    void enqueue(T &x)
    {
        m_front[back+1] = x;
        if (empty())
            frnt  =  back = 0;
        else
            back++;
        theSize++;
        resize();
        
    }
    T dequeue()
    {
        if (empty())
            throw std::runtime_error("Empty Queue\n");
        T temp =  m_front[frnt];
        if (theSize == 1)
            frnt =  back  = -1;
        else
        {
            frnt++;
            if(back == capacity)
                back = 0;
        }
        theSize--;
        return temp;
    }
    T& front()
    {
        if (empty())
            throw std::runtime_error("Empty Queue\n");
        return m_front[frnt];
    }
    bool empty()
    {
        return (theSize == 0);
    }
    void clear()
    {
        frnt = back = -1;
        theSize = 0;
    }
};
#endif
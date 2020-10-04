#ifndef _MYHASHTABLE_
#define _MYHASHTABLE_
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "myDlList.hpp"

template <typename HashedObj>
class myHashTable
{
public:
    explicit myHashTable(int size = 101)
    {
        currentSize = 0;
        theLists.resize(101);
    }
    bool contains(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        return find(getiteratorbegin(myhash(x)), getiteratorend(myhash(x)), x) != getiteratorend(myhash(x));
    }
    void makeEmpty()
    {
        for (auto &thisList : theLists)
            thisList.clear();
    }
    bool insert(const HashedObj &x)
    {

        auto &whichList = theLists[myhash(x)];
        if (find(getiteratorbegin(myhash(x)), getiteratorend(myhash(x)), x) != getiteratorend(myhash(x)))
            return false;
        whichList.push_back(x);

        if (++currentSize > theLists.size())
        {
            rehash();
        }

        return true;
    }
    bool insert(HashedObj &&x)
    {
        auto y = std::move(x);
        auto &whichList = theLists[myhash(x)];
        if (find(getiteratorbegin(myhash(x)), getiteratorend(myhash(x)), x) != getiteratorend(myhash(x)))
            return false;
        whichList.push_back(y);
        if (++currentSize > theLists.size())
            rehash();
        return true;
    }
    bool remove(const HashedObj &x)
    {
        auto &whichList = theLists[myhash(x)];
        auto itr = find(getiteratorbegin(myhash(x)), getiteratorend(myhash(x)), x);
        if (itr == getiteratorend(myhash(x)))
            return false;
        whichList.erase(itr);
        --currentSize;
        return true;
    }

    int hashsize()
    {
        return theLists.size();
    }

    typename myDlList<HashedObj>::iterator find(typename myDlList<HashedObj>::iterator from, typename myDlList<HashedObj>::iterator to, const HashedObj &x)
    {
        for (auto &it = from; it != to; it++)
        {
            if (it == x)
                return it;
        }
    }
    typename myDlList<HashedObj>::iterator getiteratorbegin(int index)
    {
        return theLists[index].begin();
    }
    typename myDlList<HashedObj>::iterator getiteratorend(int index)
    {
        return theLists[index].end();
    }

private:
    std::vector<myDlList<HashedObj>> theLists; // The array of Lists
    int currentSize;
    void rehash()
    {
        std::vector<myDlList<HashedObj>> oldLists = theLists;
        // Create new double-sized, empty table
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto &thisList : theLists)
            thisList.clear();
        // Copy table over
        currentSize = 0;
        for (auto &thisList : oldLists)
            for (auto &x : thisList)
                insert(std::move(x));
    }
    size_t myhash(const HashedObj &x) const
    {
        static hash hf;
        return hf(x) % theLists.size();
    }

    int nextPrime(int n)
    {
        if (n <= 1)
            return 2;

        int prime = n;
        bool found = false;

        // Loop continuously until isPrime returns
        // true for a number greater than n
        while (!found)
        {
            prime++;

            if (isPrime(prime))
                found = true;
        }

        return prime;
    }
    bool isPrime(int n)
    {
        // Corner cases
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;

        // This is checked so that we can skip
        // middle five numbers in below loop
        if (n % 2 == 0 || n % 3 == 0)
            return false;

        for (int i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;

        return true;
    }

    class hash
    {
    public:
        size_t operator()(const std::string &key)
        {
            size_t hashVal = 0;
            for (char ch : key)
                hashVal = 37 * hashVal + ch;
            return hashVal;
        }

        size_t operator()(const int &key)
        {
            size_t hashVal = abs(key);
            return hashVal;
        }
    };
};
#endif

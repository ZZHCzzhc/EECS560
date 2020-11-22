#include <iostream>
#include <vector>

template <typename Comparable>
const Comparable &median3(std::vector<Comparable> &a, int left, int right, bool reverse)
{
  int center = (left + right) / 2;

  if (reverse)
  {
    if (a[center] > a[left])
      std::swap(a[left], a[center]);
    if (a[right] > a[left])
      std::swap(a[left], a[right]);
    if (a[right] > a[center])
      std::swap(a[center], a[right]);
  }
  else
  {
    if (a[center] < a[left])
      std::swap(a[left], a[center]);
    if (a[right] < a[left])
      std::swap(a[left], a[right]);
    if (a[right] < a[center])
      std::swap(a[center], a[right]);
  }

  // Place pivot at position right-1
  std::swap(a[center], a[right-1]);
  return a[right-1];
}

template <typename Comparable>
void insertionSort(std::vector<Comparable> &a, int left, int right, bool reverse)
{
  int i;
  int j;
  for (i = left + 1; i <= right; i++)
  {
    j = i;
    if (reverse)
    {
      while (--j >= left && a[j] < a[j + 1])
        std::swap(a[j + 1], a[j]);
    }
    else
    {
      while (--j >= left && a[j] > a[j + 1])
        std::swap(a[j + 1], a[j]);
    }
  }
}

template <typename Comparable>
void quickSort(std::vector<Comparable> &a, int left, int right, bool reverse)
{
  if (left + 10 <= right)
  {
    const Comparable &pivot = median3(a, left, right, reverse);
    //print pivot
    std::cout << pivot << std::endl;

    // Begin partitioning
    int i = left, j = right - 1;
    while (1)
    {
      if (!reverse)
      {
        while (a[++i] < pivot) {}
        while (pivot < a[--j]) {}
      }
      else
      {
        while (a[++i] > pivot) {}
        while (pivot > a[--j]) {}
      }

      if (i < j)
        std::swap(a[i], a[j]);
      else
        break;
    }

    std::swap(a[i], a[right - 1]); // Restore pivot

    quickSort(a, left, i - 1, reverse);  // Sort small elements
    quickSort(a, i + 1, right, reverse); // Sort large elements
  }
  else // Do an insertion sort on the subarray
    insertionSort(a, left, right, reverse);
}

template <typename Comparable>
void quickSort(std::vector<Comparable> &a, bool reverse = false) //interface
{
  quickSort(a, 0, a.size() - 1, reverse);
  // insertionSort(a,0,a.size()-1,reverse);
}
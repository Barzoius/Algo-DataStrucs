#include <iostream>
#include <vector>
#include <string>

template <typename T, typename U>
int binSearch(T vec, int left, int right, U elem)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (vec[mid] == elem)
            return mid;
        else if (vec[mid] < elem)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

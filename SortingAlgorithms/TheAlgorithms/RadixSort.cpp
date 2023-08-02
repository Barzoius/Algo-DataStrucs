#include <iostream>
#include <vector>
#include <algorithm>

void CountSort(std::vector<int>& v, int exp)
{
    std::vector<int> vout(v.size());
    std::vector<int> count(10, 0);

    for (int i = 0; i < v.size(); i++)
    {
        count[(v[i]/exp)%10]++;
    }

    for (int i = 1; i < 10; i++)
    {
        count[i] += count[i-1];
    }

    for (int i = v.size()-1; i >= 0; i--)
    {
        vout[count[(v[i]/exp)%10]-1] = v[i];
        count[(v[i]/exp)%10]--;
    }

    for (int i = 0; i < v.size(); i++)
    {
        v[i] = vout[i];
    }
  
}

void RadixSort(std::vector<int>& v)
{
    int max_element = *std::max_element(v.begin(), v.end());

    for (int exp = 1; max_element/exp > 0; exp *= 10)
    {
        CountSort(v, exp);
    }
}

// int main()
// {

//     return 0;
// }

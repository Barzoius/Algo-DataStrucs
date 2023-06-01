#include <iostream>

/// The Pattern for this one is of the form:
/// 1, 2,1, 3,2,1, 4,3,2,1, ........, k,k-1,k-2,.....2,1 (easy pattern)

int main()
{
    int k;
    std::cin>>k;
    int size =(k*(k+1))/2; //The size is this way because it is equal to the sum of k elements
    int v[size];
    int index = 0;

    for(int i = 1; i <= k; i++)
    {
        for(int j = i; j >= 1; j--)
        {
            v[index] = j;
            index++;
        }
    }

    int x;
    std::cin>>x;
    std::cout<<v[x];
    
    return 0;
}

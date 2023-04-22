#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>


using namespace std::chrono;

void mergeop(std::vector<int>& v, int l, int m, int r, std::vector<int>& temp){

    int i = l;
    int j = m + 1;
    int k = 0;

    while(i <= m  && j <= r)
    {
        if(v[i] <= v[j])
        {
            temp[k++] = v[i++];
        }
        else
        {
            temp[k++] = v[j++];
        }
    }
    while(i <= m )
    {
        temp[k++] = v[i++];

    }

    while(j <= r)
    {
        temp[k++] = v[j++];
    }

    for(int p = l; p <= r; p++){
        v[p] = temp[p - l];
    }
}

void mergesort(std::vector<int>& v, int l, int r, std::vector<int>& temp){

    if(l < r) {

        int m = l + (r - l) / 2;

        mergesort(v, l, m, temp);
        mergesort(v, m +  1, r, temp);

        mergeop(v, l, m , r, temp);
    }
}

// void STANDARDsort(std::vector<int>& v){
//     int n = v.size();
//     std::vector<int> temp(n);
//     mergesort(v, 0, n-1, temp);
// }

// void printVector(std::vector<int>& vec) {
//     for (int i = 0; i < vec.size(); i++) {
//         std::cout << vec[i] << " ";
//     }
//     std::cout << std::endl;
// }

// int main()
// {
//     STANDARDsort(...)    
//     return 0;
// }

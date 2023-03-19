#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <random>

using namespace std::chrono;

void ShellSort(std::vector<int>& v)
{
    int n = v.size();
    // Ne alegem gap-ul, in cazul de fata porneste de la n/2 si continuam sa impartim la 2
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Restul codului este doar un insert sort :D
        for (int i = gap; i < n; i++)
        {
            int k = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > k; j -= gap)
            { v[j] = v[j - gap]; }
            v[j] = k;
        }
    }
}


void KnuthShellSort(std::vector<int>& v)
    {
        int n = v.size();
        int gap  = 1;
        while(gap < n/3) { gap = gap * 3 + 1; }

        while(gap >= 1)
        {
            for(int i = gap; i < n; i++ )
            {
                int k = v[i];
                int j;
                for(j = i; j >= gap && v[j - gap] > k; j -= gap)
                { v[j] = v[j - gap]; }
                v[j] = k;
            }
            gap /= 3;
        }
    }


// int main()
// {
//     return 0;
// }

#include <iostream>

int main()
{

    int n;
    std::cin>>n;

    for(int i = 1; i <=n ; i++)
    {
        int k = i;
        while(k!=0) {
            for (int j = 1; j <= i; j++) {
                std::cout << i;
            }
            std::cout<<"\n";
            k--;
        }

    }

//    n = 3
//    1
//    22
//    22
//    333
//    333
//    333

    return 0;
}

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

class RMQ{
    int n;
    std::vector<int> v;

public:

    RMQ(int N, std::vector<int> V) : n(N), v(std::move(V)){}

    std::vector<std::vector<int>> CREATE_RMQ() const{
        std::vector<std::vector<int>> r(17, std::vector<int>(n));
        for(int i = 0; i < n; i++){
            r[0][i] = v[i];
        }

        for(int p = 1; (1 << p) <= n; p++){
            for(int i = 0; i < n; i++){
                r[p][i] = r[p - 1][i];
//                int k = i + (int)pow(2, (p - 1)); both k work
                int k = i + (1<<(p-1));
                if(k <= n && r[p][i] > r[p -1][k])
                    r[p][i] = std::min(r[p - 1][i], r[p - 1][k]);
            }
        }

        return r;

    }

    static void DISPLAY(const std::vector<std::vector<int>>& r){

        int size = r[0].size();
        int c = (int)pow(2, floor(log2(size)));
        std::cout << std::left << std::setw(10) << "Pow of 2 ";
        for(int p = 0; p < size; p++) {
            std::cout<<std::left<<std::setw(10)<<p;
        }

        for(int p = 0; p < c; p++ ){
            std::cout<<std::endl;
            std::cout<<std::left<<std::setw(0)<<"2^("<<p<<"): "<<std::left<<std::setw(5);
            for(int i = 0; i < r[0].size(); i++){
                std::cout<<std::left<<std::setw(10)<<r[p][i];
            }
            std::cout<<std::endl;
        }
    }
};

int main() {

    int N ;
    std::cin>>N;
    std::vector<int> V(N);

    for(int i = 0; i < N; i++){
        std::cin>>V[i];
    }

    RMQ rmq(N, V);
    std::vector<std::vector<int>> r = rmq.CREATE_RMQ();
    RMQ::DISPLAY(r);

    return 0;
}

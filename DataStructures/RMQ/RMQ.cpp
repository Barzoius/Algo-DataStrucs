#include <iostream>
#include <vector>
#include <cmath>

class RMQ{
    int n;
    std::vector<int> v;

public:

    RMQ(int N, std::vector<int> V) : n(N), v(std::move(V)){}

    std::vector<std::vector<int>> CREATE_RMQ() const{
        std::vector<std::vector<int>> r(17, std::vector<int>(n));
        for(int i = 0; i < n; i++){
            std::cin>>r[0][i];
        }

        for(int p = 1; (1 << p) <= n; p++){
            for(int i = 0; i < n; i++){
                r[p][i] = r[p - 1][i];
                int k = i + (int)pow(2, (p - 1));
                if(k <= n && r[p][i] > r[p -1][i])
                    r[p][i] = std::min(r[p - 1][i], r[p - 1][k]);
            }
        }

        return r;

    }

    static void DISPLAY(const std::vector<std::vector<int>>& r){
        for(int p = 0; p < r.size(); p++ ){
            std::cout<<"2^("<<p<<")"<<":\n";
            for(int i = 0; i < r[0].size(); i++){
                std::cout<< r[p][i] << " ";
            }
        }
    }
};

int main() {

    int N ;
    std::vector<int> V;

    std::cin>>N;
    for(int i = 0; i < N; i++){
        std::cin>>V[i];
    }

    RMQ rmq(N, V);
    std::vector<std::vector<int>> r = rmq.CREATE_RMQ();
    RMQ::DISPLAY(r);

    return 0;
}


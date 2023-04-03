#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

using namespace std::chrono;

//This will randomly create vector of different sizes from 10 to 10^K 
//with different maximum values from 10 to 10^P.
//For every combination of vector size and max value
//it will generate 10 different vectors and print the average run time

void TEST(int K, int P, const int NrRuns){

    for(int k = 1; k <= K; k++) {
        int n = std::pow(10, k);
        for (int p = 1; p <= P; p++) {
            int maxV = std::pow(10, p);

            std::vector<int> v(n);

            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            srand(seed);

            for (int i = 0; i < n; i++) {
                v[i] = std::rand() % maxV;
            }


            //std::vector<int> temp(n);
            std::vector<std::chrono::milliseconds> runTimes(NrRuns);

            for (int i = 0; i < NrRuns; i++) {

                auto start = high_resolution_clock::now();

                algsort(v);

                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<milliseconds>(stop - start);

                runTimes[i] = duration;
            }

            double TimpTotal = 0;
            for (int i = 0; i < NrRuns; i++) {
                TimpTotal += runTimes[i].count();
            }
            double AvgTime = TimpTotal / NrRuns;

            std::cout << "Size: " << n << ", MaxValue: " << maxV << ", AvgTime: " << AvgTime << " miliseconds "
                      << std::endl;

        }
    }
}


//This will simply generate a vector of size n
//with only 1s as elements and one zero with random position

  int n = 1000000000;
    std::vector<int> v(n, 1);

    // genereaza un index random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n-1);
    int index = dis(gen);

    // seteaza valuarea de la index la 0
    v[index] = 0;

     Sort the vector using mergesort
    std::vector<int> temp(n);

    try {
        std::cout << "Devious acts are in motion...\n";
        algsort();
        std::cout << "The sort is done.\n";
    } catch (const std::exception& e) {
        std::cout << "Dios mio: " << e.what() << "\n";
    }

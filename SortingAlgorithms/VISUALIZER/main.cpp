#include "../HEADERS/VIS.hpp"

 int main(int argc, char* argv[])
 {
    std::uniform_int_distribution<int> d(1, 99);
    std::random_device random;
    std::vector<int> vec;
    for(int i = 0; i < 100; i++){
        vec.push_back(d(random));
    }
     Visualizer V;
     V.SimpleSort(vec);
     return 0;
 }


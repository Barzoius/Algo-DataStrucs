#include "HEADERS/VIS.hpp"

Visualizer::Visualizer() : window(nullptr), renderer(nullptr){
    SDL_CreateWindowAndRenderer(
            100*10, 100*10, 0,
            &window, &renderer);

    SDL_RenderSetScale(renderer, 10, 10);
    std::vector<int> vec = {12, 3, 3, 6};

    SimpleSort(vec);
}

Visualizer::~Visualizer()= default;

void Visualizer::Draw_State(std::vector<int> &vec, SDL_Renderer *renderer1, unsigned int red, unsigned int blue) {
    int size_vec = vec.size();
    for(int i = 0; i < size_vec; i++){
        if(i == red){
            SDL_SetRenderDrawColor(renderer1, 255, 0, 0, 255);
        }
        else if(i == blue){
            SDL_SetRenderDrawColor(renderer1, 191, 180, 131, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);
        }

        SDL_RenderDrawLine(renderer1, i, size_vec, i, vec[i]);
    }
}

void Visualizer::SimpleSort(std::vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (v[i] < v[j]) {
                std::swap(v[i], v[j]);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                Draw_State(v, renderer, i, j);

                SDL_RenderPresent(renderer);
                SDL_Delay(100);
            }
        }
    }
}

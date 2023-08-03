#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "SDL_opengl.h"
#include <algorithm>
#include <random>
#include <vector>

class Visualizer{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Visualizer();
    ~Visualizer();

    SDL_Renderer* GetRenderer() const { return this -> renderer; }

    void Draw_State(std::vector<int>& vec, SDL_Renderer* renderer1, unsigned int red, unsigned int blue);
    void SimpleSort(std::vector<int>& v);
};


void mergeop(std::vector<int>& v, int l, int m, int r, std::vector<int>& temp);
void mergesort(std::vector<int>& v, int l, int r, std::vector<int>& temp);
//void SimpleSort(std::vector<int>&);


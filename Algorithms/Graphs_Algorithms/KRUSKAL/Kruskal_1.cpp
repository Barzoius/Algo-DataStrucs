#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

class DSU{

private:
    std::vector<int> parent;
    std::vector<int> rank;

public:

    DSU(int n) : parent(n, -1), rank(n, 1) {}

    int DSU_find(int i)
    {
        if(parent[i] == -1)
            return i;

        return parent[i] = DSU_find(parent[i]);
    }

    void DSU_union(int x, int y)
    {
        int X = DSU_find(x);
        int Y = DSU_find(y);

        if(rank[X] > rank[Y])
            std::swap(X, Y);

        parent[X] = Y;
        rank[Y] += rank[X];
    }
};

class Graph {

private:

    size_t num_vertices;

    std::vector<std::vector<int>> Adjacency_List;
    std::vector<std::vector<std::tuple<int, int>>> Weighted_Adjacency_List;

    std::vector<std::tuple<int, int>> Edges_List;
    std::vector<std::tuple<int, int, int>> Weighted_Edges_List;


public:

    static bool weight_compartor(const std::tuple<int, int, int>& a,
                                 const std::tuple<int, int, int>& b)
    {
        return std::get<2>(a) < std::get<2>(b);
    }

    void Kruskal_sort()
    {
        std::sort(Weighted_Edges_List.begin(),
                  Weighted_Edges_List.end(),
                  weight_compartor);
    }

    int KRUSKAL()
    {
        Kruskal_sort();
        DSU D(num_vertices);
        int rez = 0;
        for (auto edge : Weighted_Edges_List) {
            int x = std::get<0>(edge);
            int y = std::get<1>(edge);
            int w = std::get<2>(edge);

            // The union is peformed only if x and y do not form a cycle
            if (D.DSU_find(x) != D.DSU_find(y)) {
                D.DSU_union(x, y);
                rez += w;
                //std::cout << x << " -- " << y << " == " << w << std::endl;
            }
        }
        std::cout << "Minimum Cost Spanning Tree: " << rez;;
        return rez;
    }

};

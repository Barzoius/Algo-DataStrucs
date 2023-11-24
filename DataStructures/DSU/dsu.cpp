#include <iostream>
#include <vector>
#include <tuple>
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


int main()
{
  int n = 4;
  DSU D(n);
  return 0;
}

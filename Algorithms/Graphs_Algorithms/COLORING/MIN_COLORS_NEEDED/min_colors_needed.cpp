#include <iostream>
#include <vector>
#include <bitset>

enum COLOR {RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE};

class GRAPH{

private:

    int num_vertices;
    std::vector<int> COLORS;
    std::vector<std::vector<int>> ADJ_LIST;
    std::bitset<16> VIS;

    const unsigned int N_COLOR = 6;
    enum COLOR COLOR;

    int min_num_colors;

public:

    GRAPH() = default;

    explicit GRAPH(int n) : num_vertices(n), min_num_colors(0)
    {
        ADJ_LIST.reserve(num_vertices);

        COLORS.reserve(5);

        if(num_vertices != 0) min_num_colors = 1;

    }

    std::vector<std::vector<int>> GET_ADJ_LIST() { return ADJ_LIST;}

    bool COLORING(int start_vertex)
    {
        COLORS[start_vertex] = COLOR::RED;

        for(int adj_vertex = 0 ; adj_vertex < ADJ_LIST[start_vertex].size(); adj_vertex++)
        {
                if(COLORS[adj_vertex] == COLORS[start_vertex]) break;
                else
                {
                    COLORS[adj_vertex] = COLORS[start_vertex]++;
                    min_num_colors++;
                }

                if(COLORING(adj_vertex))
                {
                    std::cout<<"Min colors needed: " << min_num_colors;
                    return true;
                }

                COLORS[adj_vertex] = 0;

        }

        std::cout<<"Invalid GRAPH";
        return false;
    }
};

int main()
{
    int n = 6;
    GRAPH G(n);

    std::vector<int> V_1 = {1, 3 , 5};
    std::vector<int> V_2 = {0, 3 , 4};
    std::vector<int> V_3 = {1, 5 , 3};
    std::vector<int> V_4 = {0, 1 , 2};
    std::vector<int> V_5 = {1, 2 , 5};
    std::vector<int> V_6 = {1, 3 , 4};

    G.GET_ADJ_LIST().push_back(V_1);
    G.GET_ADJ_LIST().push_back(V_2);
    G.GET_ADJ_LIST().push_back(V_3);
    G.GET_ADJ_LIST().push_back(V_4);
    G.GET_ADJ_LIST().push_back(V_5);
    G.GET_ADJ_LIST().push_back(V_6);

//    COLOR f = COLOR::PURPLE;
//    std::cout<<(int)f;

    G.COLORING(0);
    return 0;
}

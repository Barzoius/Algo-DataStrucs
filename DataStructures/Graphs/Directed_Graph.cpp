#include <io.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

class Implementations{
public:
    virtual void Add_to_adj_list(std::vector<int>&, int) = 0;
    virtual void Add_to_edge_list(std::tuple<int, int>&) = 0;

    virtual ~Implementations() = default;
};

class iterator;

class Graph : public virtual Implementations{

private:

    size_t num_vertices;
    std::vector<std::vector<int>> Adjacency_List;
    std::vector<std::tuple<int, int>> Edges_List;

    std::vector<bool> VIS;

public:
    std::vector<bool> GetVis() const { return VIS; }
    Graph() : num_vertices(0) {}

    explicit Graph(size_t vertices_number ) : num_vertices(vertices_number)
    {
        Adjacency_List.resize(vertices_number);
        VIS.resize(vertices_number, false);
    }

    std::vector<std::vector<int>> Get_Adjacency_List(){ return Adjacency_List;}
    size_t Get_Graph_Size() const { return num_vertices; }

    void Add_to_adj_list(std::vector<int>& adj_vertices, int index) override
    {
        Adjacency_List[index].insert(Adjacency_List[index].end(),
                                        adj_vertices.begin(),
                                        adj_vertices.end()
                                    );
    }

    void Add_to_edge_list(std::tuple<int, int>& tuplu) override
    {
        Edges_List.push_back(tuplu);
//        std::sort(Edges_List.begin(), Edges_List.end());
    }

    void Add_Vertex(size_t x){
        Adjacency_List.resize(num_vertices + x);
    }

    void PrintAdjList(){

        for(size_t i = 0; i < Adjacency_List.size(); i++){
            std::cout<<i+1<<": "<<"[";
            for(size_t j = 0; j < Adjacency_List[i].size() ; j++){
                std::cout << Adjacency_List[i][j];
                if (j < Adjacency_List[i].size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout<<"]";
            std::cout<<std::endl;
        }
    }

    void PrintEdges(){
        std::sort(Edges_List.begin(), Edges_List.end());
        for(size_t i = 0; i < Edges_List.size(); i++)
        {
            std::cout<<"(";
            std::cout<<std::get<0>(Edges_List[i]) << ", ";
            std::cout<<std::get<1>(Edges_List[i]) << "";
            std::cout<<")";
            std::cout<<std::endl;
        }
    }


    void DFS(int start_vertex, bool flag)
    {
        start_vertex--;
        VIS[start_vertex] = true;

        if(flag) std::cout << start_vertex + 1 << " ";


        for(const auto&  j : Adjacency_List[start_vertex])
        {
            int adj_vertex = j - 1;

            if(!VIS[adj_vertex])
                DFS(j, flag);

        }
    }

    void PrintDFS()
    {
        std::fill(VIS.begin(), VIS.end(), false);
        std::cout<<"The DFS traversal is: ";
        for (int i = 0; i < Get_Graph_Size(); i++)
            if (!GetVis()[i])
                DFS(i + 1, true);
    }


    int GetConexElemets()
    {
        std::fill(VIS.begin(), VIS.end(), false);
        int cnt = 0;
        for (int i = 0; i < Get_Graph_Size(); i++)
        {
            if (!GetVis()[i])
            {
                cnt++;
                DFS(i + 1, false);
            }

        }
        std::cout<<std::endl;
        std::cout<<"The number of conex elemets is: " << cnt;

        return cnt;
    }
};


int main() {

    Graph g(7);
    std::vector<int> vec1 = {2};
    std::vector<int> vec2 = {1, 6, 7};
    std::vector<int> vec3 = {};
    std::vector<int> vec4 = {5};
    std::vector<int> vec5 = {4};
    std::vector<int> vec6 = {2};
    std::vector<int> vec7 = {2};

    g.Add_to_adj_list(vec1, 0);
    g.Add_to_adj_list(vec2, 1);
    g.Add_to_adj_list(vec3, 2);
    g.Add_to_adj_list(vec4, 3);
    g.Add_to_adj_list(vec5, 4);
    g.Add_to_adj_list(vec6, 5);
    g.Add_to_adj_list(vec7, 6);
    g.PrintAdjList();

    g.PrintDFS();
    g.GetConexElemets();
    std::cout<<std::endl;


    return 0;
}

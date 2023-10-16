#include <io.h>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

struct Vertex{

};

struct Undirected_Edge{

};

struct Directed_Edge{

};

class Implementations{
public:
    virtual void Add_to_adj_list(std::vector<int>&, int) = 0;
    virtual void Add_to_edge_list(std::tuple<int, int>&) = 0;
};

class Graph : public virtual Implementations{

private:

    size_t num_vertices;
    std::vector<std::vector<int>> Adjacency_List;
    std::vector<std::tuple<int, int>> Edges_List;

public:

    Graph() : num_vertices(0) {}

    explicit Graph(size_t vertices_number ) : num_vertices(vertices_number)
    {
        Adjacency_List.resize(vertices_number);
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

    void PrintGraph(){

        for(size_t i = 0; i < Adjacency_List.size(); i++){
            std::cout<<i+1<<": ";
            for(size_t j = 0; j < Adjacency_List[i].size() ; j++){
                std::cout << Adjacency_List[i][j];
                if (j < Adjacency_List[i].size() - 1) {
                    std::cout << ", ";
                }
            }
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
};

class Undirected_Graph : public Graph{

};

class Directed_Graph : public Graph{

};

int main() {

    Graph g(2);
    std::vector<int> vec1 = {12, 32, 43, 43};
    std::vector<int> vec2 = {52, 2, 43, 3567};
    g.Add_to_adj_list(vec1, 0);
    g.PrintGraph();
    g.Add_Vertex(3);
    g.Add_to_adj_list(vec2, 2);
    g.PrintGraph();

    Graph h;
    std::tuple<int, int> tup1 = std::make_tuple(1, 2);
    std::tuple<int, int> tup4 = std::make_pair(3, 2);
    std::tuple<int, int> tup2 = std::make_tuple(2, 1);
    std::tuple<int, int> tup3 = std::make_tuple(1, 3);
    h.Add_to_edge_list(tup1);
    h.Add_to_edge_list(tup4);
    h.Add_to_edge_list(tup2);
    h.Add_to_edge_list(tup3);
    h.PrintEdges();


    return 0;
}


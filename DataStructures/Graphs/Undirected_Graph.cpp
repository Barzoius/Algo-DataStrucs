#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <queue>

class Implementations{
public:
    virtual void Add_to_adj_list(std::vector<int>&, int) = 0;
    virtual void Add_to_edge_list(std::tuple<int, int>&) = 0;

    virtual ~Implementations() = default;
};

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
            std::cout<<i<<": "<<"[";
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

///---------------------------DFS_BASED_THINGS---------------------------///

    void DFS(int start_vertex, bool flag)
    {
//        start_vertex--;
        VIS[start_vertex] = true;

        if(flag) std::cout << start_vertex  << " ";


        for(const auto&  j : Adjacency_List[start_vertex])
        {
            int adj_vertex = j ;

            if(!VIS[adj_vertex])
                DFS(adj_vertex, flag);

        }
    }

    void PrintDFS()
    {
        std::fill(VIS.begin(), VIS.end(), false);
        std::cout<<"The DFS traversal is: ";
        for (int i = 0; i < Get_Graph_Size(); i++)
            if (!GetVis()[i])
                DFS(i, true);
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


    std::vector<int> height = std::vector<int>(num_vertices);
    std::vector<int> min_height = std::vector<int>(num_vertices);

    std::vector<std::vector<int>> DF(int start_vertex, int father, int Cnt, std::vector<std::vector<int>>& res)
    {

        int cnt = Cnt;


        height[start_vertex] = cnt;
        min_height[start_vertex] = height[start_vertex];

        cnt++;

        VIS[start_vertex] = true;

        for(const auto&  adj_vertex : Adjacency_List[start_vertex])
        {
            if(adj_vertex == father) continue;

            if(!VIS[adj_vertex])
            {
//                height[adj_vertex] = height[start_vertex] + 1;
                DF(adj_vertex, start_vertex, cnt, res);

                min_height[start_vertex] = std::min(min_height[start_vertex], min_height[adj_vertex]);

                if(min_height[adj_vertex] > height[start_vertex])
                {
                    res.push_back({adj_vertex, start_vertex});
                    std::cout<<"["<<start_vertex<<", "<<adj_vertex<<"]"<<std::endl;
                }
            }
            else
            {
                if(height[adj_vertex] < height[start_vertex] - 1)
                    min_height[start_vertex] = std::min(min_height[start_vertex], height[adj_vertex]);
            }

        }

        return  res;
    }


///---------------------------BFS_BASED_THINGS---------------------------///

    void BFS(int start_vertex)
    {

        std::cout<<"The BFS traversal is: ";
        std::fill(VIS.begin(), VIS.end(), false);

        std::queue<int> QUEUE;

        VIS[start_vertex] = true;
        QUEUE.push(start_vertex);

        while(!QUEUE.empty())
        {
            int vertex = QUEUE.front();
            std::cout<<vertex <<" ";

            QUEUE.pop();

            for (int j : Adjacency_List[vertex]) {
                if (!VIS[j])
                {
                    VIS[j] = true;
                    QUEUE.push(j);
                }
            }
        }

    }

    bool Is_Bipartit()
    {
        std::vector<int> color(num_vertices, -1);

        for (size_t i = 0; i < num_vertices; i++)
        {
            if (color[i] == -1)
            {
                std::queue<int> QUEUE;
                QUEUE.push(i);
                color[i] = 0;

                while (!QUEUE.empty())
                {
                    int vertex = QUEUE.front();
                    QUEUE.pop();

                    for (int j : Adjacency_List[vertex])
                    {
                        if (color[j] == color[vertex])
                            return false;

                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[vertex];
                            QUEUE.push(j);
                        }
                    }
                }
            }
        }

        return true;
    }

    bool possibleBipartition(int n, std::vector<std::vector<int>>& dislikes) {

        num_vertices = n;
        std::vector<std::vector<int>> adjacency_List;
        adjacency_List.resize(num_vertices);

        for (const auto& edge : dislikes) {
            int u = edge[0];
            int v = edge[1];
            adjacency_List[u].push_back(v);
            adjacency_List[v].push_back(u); // For undirected graph
        }

        std::vector<int> color(num_vertices, -1);

        for (size_t i = 0; i < num_vertices; i++)
        {
            if (color[i] == -1)
            {
                std::queue<int> QUEUE;
                QUEUE.push(i);
                color[i] = 0;

                while (!QUEUE.empty())
                {
                    int vertex = QUEUE.front();
                    QUEUE.pop();

                    for (int j : adjacency_List[vertex])
                    {
                        if (color[j] == color[vertex])
                            return false;

                        if (color[j] == -1)
                        {
                            color[j] = 1 - color[vertex];
                            QUEUE.push(j);
                        }
                    }
                }
            }
        }

        return true;

    }


};


int main() {

    Graph g(4);
    std::vector<int> vec1 = {1, 2};
    std::vector<int> vec2 = {0, 2, 3};
    std::vector<int> vec3 = {0, 1};
    std::vector<int> vec4 = {1};

    g.Add_to_adj_list(vec1, 0);
    g.Add_to_adj_list(vec2, 1);
    g.Add_to_adj_list(vec3, 2);
    g.Add_to_adj_list(vec4, 3);
//    g.Add_to_adj_list(vec5, 4);
//    g.Add_to_adj_list(vec6, 5);
//    g.Add_to_adj_list(vec7, 6);
    g.PrintAdjList();


//    std::vector<std::vector<int>> res;
//
//    g.DF(0, -1, 0, res);
//
//    std::vector<std::vector<int>> new_res = g.DF(0, -1, 0, res);
//
//    for(auto i : new_res){
//        std::cout<<i[0]<<"-"<<i[1]<<std::endl;
//    }




//    std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
//    bool ss = g.possibleBipartition(4, edges);
//
//    if(ss){
//        std::cout<<"YES for leetcode";
//    }
//    else
//    {
//        std::cout<<"NO for leetcode";
//    }
//
//    std::cout<<std::endl;
//
//    bool a = g.Is_Bipartit();
//    if(a){
//        std::cout<<"YES";
//    }
//    else
//    {
//        std::cout<<"NO";
//    }

//    g.PrintDFS();
//    g.GetConexElemets();
//    std::cout<<std::endl;
//    g.BFS(4);


    return 0;
}


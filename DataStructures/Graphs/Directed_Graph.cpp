#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

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
    std::vector<int> INT_VIS;
    std::vector<bool> BOOL_VIS;


    std::queue<std::pair<int, int>> QUEUE_1;


    ///---Used for the Tarjan's Algorithm---///
    std::vector<int> height = std::vector<int>(num_vertices);
    std::vector<int> min_height = std::vector<int>(num_vertices);
    ///------------------------------------///


    std::vector<int> safe_nodes;
    std::vector<int> unsafe_nodes;


public:

    std::vector<bool> GetVis() const { return VIS; }
    Graph() : num_vertices(0) {}

    explicit Graph(size_t vertices_number ) : num_vertices(vertices_number)
    {
        Adjacency_List.resize(num_vertices);
        VIS.resize(num_vertices, false);
        INT_VIS.resize(num_vertices, -1);
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


///---------------------------LEET_CODE_PROBLEMS---------------------------///

///-----1192.Critical_Connections_in_a_Network-----///
         ///-----Tarjan's Algorithm-----///

//    std::vector<int> height = std::vector<int>(num_vertices);
//    std::vector<int> min_height = std::vector<int>(num_vertices);

    std::vector<std::vector<int>> DF(int start_vertex, int father, int Cnt,
                                     std::vector<std::vector<int>>& res)
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
                DF(adj_vertex, start_vertex, cnt, res);

                min_height[start_vertex] = std::min(min_height[start_vertex], min_height[adj_vertex]);

                if(min_height[adj_vertex] > height[start_vertex])
                {
                    res.push_back({adj_vertex, start_vertex});
                    std::cout<<"["<<start_vertex<<", "<<adj_vertex<<"]"<<std::endl;
                }
            }
            else    //cycle
            {
                min_height[start_vertex] = std::min(min_height[start_vertex], height[adj_vertex]);
            }

        }

        return  res;
    }


///-----934.Shortest_Bridge-----///

//    std::queue<std::pair<int, int>> QUEUE_1;
    void Matrix_DFS(int xpos, int ypos, std::vector<std::vector<int>>& Matrix, int n = 0, int m = 0)
    {

        if(m == 0) m = n;
        if(xpos < 0 || xpos >= n || ypos < 0 || ypos >= m) return;

        if(Matrix[xpos][ypos] == 1)
        {
            Matrix[xpos][ypos] = 2;
            QUEUE_1.push({xpos, ypos});

            Matrix_DFS(xpos + 1, ypos, Matrix, n, m);
            Matrix_DFS(xpos, ypos + 1, Matrix, n, m);
            Matrix_DFS(xpos - 1, ypos, Matrix, n, m);
            Matrix_DFS(xpos, ypos - 1, Matrix, n, m);
        }
    }

    std::pair<int, int> TILE_SEARCH(int n, std::vector<std::vector<int>>& Map){
        for (int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if (Map[i][j]==1){
                    return {i, j};
                }
        return {-1,-1};
    }

    int shortestBridge(std::vector<std::vector<int>>& grid) {
        int bridge = 0;
        bool bridge_found = false;

        int grid_size = (int)grid.size();
        std::pair<int, int> Coords = TILE_SEARCH(grid_size, grid);


        Matrix_DFS(Coords.first, Coords.second, grid, grid_size, grid_size);

        while (!bridge_found) {
            std::queue<std::pair<int, int>> QUEUE_2;

            while (!QUEUE_1.empty() && !bridge_found) {
                Coords = QUEUE_1.front();
                QUEUE_1.pop();
                int xpos = Coords.first;
                int ypos = Coords.second;

                std::vector<std::pair<int, int>> adj({ /// adjacent cells ///
                                                             {xpos + 1, ypos}, /// >
                                                             {xpos, ypos + 1}, /// ^
                                                             {xpos - 1, ypos}, /// <
                                                             {xpos, ypos - 1}}); /// v

                for (auto &coords : adj) {
                    if (coords.first < 0 ||
                        coords.first >= grid_size ||
                        coords.second < 0 ||
                        coords.second >= grid_size)
                        continue; //bad cell

                    if (grid[coords.first][coords.second] == 1) {
                        bridge_found = true;
                        break;
                    } else if (grid[coords.first][coords.second] == 0) {
                        QUEUE_2.push({coords.first, coords.second});
                        grid[coords.first][coords.second] = -1 - bridge;
                    }
                }
            }

            if (!bridge_found) {
                QUEUE_1 = QUEUE_2;
                bridge++;
            }
        }

        return bridge;
    }


///-----886.Possible_Bipartition-----///

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

///-----990.Satisfiability_of_Equality_Equations-----///

    bool equationsPossible(std::vector<std::string>& equations) {
        std::vector<std::vector<int>> adjacency_List(26);

        for (std::string& equation : equations) {
            if (equation[1] == '=') {
                int adj_index = equation[0] - 'a';
                int adj_vertex = equation[3] - 'a';

                if (adj_index == adj_vertex) {
                    continue; // Skip a == a equations
                }

                adjacency_List[adj_index].push_back(adj_vertex);
                adjacency_List[adj_vertex].push_back(adj_index);
            }
        }

        std::vector<int> visited(26, -1);

        int component = 0; // Component identifier

        for (int i = 0; i < 26; i++) {
            if (visited[i] == -1) {
                std::stack<int> stack;
                stack.push(i);
                visited[i] = component; // Assign the current component
                while (!stack.empty()) {
                    int node = stack.top();
                    stack.pop();
                    for (int neighbor : adjacency_List[node]) {
                        if (visited[neighbor] == -1) {
                            stack.push(neighbor);
                            visited[neighbor] = component;
                        }
                    }
                }
                component++;
            }
//            std::cout<<std::endl;
//            std::cout<<component;
        }

        for (std::string& equation : equations) {
            if (equation[1] == '!') {
                int adj_index = equation[0] - 'a';
                int adj_vertex = equation[3] - 'a';

                if(adj_index == adj_vertex) return false; // Exit on a!=a equations

                if (visited[adj_index] != visited[adj_vertex]) { //check if they connect somewhere
                    continue;
                } else {
                    return false;
                }
            }
        }

        return true;
    }


///-----802.Find_Eventual_Safe_States-----///

//    std::vector<int> safe_nodes;  // all adj_vertex have to be safe
//    std::vector<int> unsafe_nodes; // cycles the route

    bool DFS(std::vector<std::vector<int>>& adj_list, int vertex, std::vector<int>& visited)
    {

        if(std::find(unsafe_nodes.begin(), unsafe_nodes.end(), vertex) != unsafe_nodes.end())
            return false;
        if(std::find(safe_nodes.begin(), safe_nodes.end(), vertex) != safe_nodes.end())
            return true;

        if(std::find(visited.begin(), visited.end(),vertex) != visited.end())
        {
            unsafe_nodes.emplace_back(vertex);
            return false;
        }

        visited.emplace_back(vertex);

        for(int adj_vertex : adj_list[vertex])
        {
            if(!DFS(adj_list, adj_vertex, visited))
            {
                unsafe_nodes.emplace_back(vertex);
                return false;
            }
        }

        safe_nodes.emplace_back(vertex);
        return true;
    }

    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        //Adjacency_List = graph;
        std::vector<int> res , visited;

        for(int i = 0; i < graph.size(); i++)
        {
            if(DFS(graph, i, visited))
                res.emplace_back(i);
        }

        return res;
    }



};


int main() {


    Graph g(4);
    std::vector<std::vector<int>> ff = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    std::vector<std::vector<int>> gg = {{1, 0}, {0, 1}};
//    g.findOrder(2, gg);
//    std::vector<std::vector<int>> vv = {{1, 2}, {0, 2, 3}, {0, 1}, {1}};

    std::vector<int> vec1 = {1, 2};
    std::vector<int> vec2 = {0, 2, 3};
    std::vector<int> vec3 = {0, 1};
    std::vector<int> vec4 = {1};

    g.Add_to_adj_list(vec1, 0);
    g.Add_to_adj_list(vec2, 1);
    g.Add_to_adj_list(vec3, 2);
    g.Add_to_adj_list(vec4, 3);
////    g.PrintAdjList();
//
//    std::vector<std::vector<int>> grid ={{0,1,0,0,0},
//                                         {0,1,0,1,1},
//                                         {0,0,0,0,1},
//                                         {0,0,0,0,0},
//                                         {0,0,0,0,0}};
//    int res = g.shortestBridge(grid);
//    std::cout<<res;
//
////    int adj_index = 'o' - 'a' + 1;
////    std::cout<<"let::" <<adj_index;
//    std::cout<<std::endl;
//    std::vector<std::string> ecuatii = {{"a==b"}, {"b!=c"}, {"c==a"}};
//    if(g.equationsPossible(ecuatii)) {
//        std::cout<<"TRUE";
//    }
//    else{
//        std::cout<<"FALSE";
//    }
//
//    std::cout<<std::endl;
//    std::vector<std::vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
//    std::vector<int> rezultat = g.eventualSafeNodes(graph);
//
//    for(int i : rezultat)
//    {
//        std::cout<<i<<" ";
//    }

//    g.Equations(ecuatii);


    std::vector<std::vector<int>> res;
//
//    g.DF(0, -1, 0, res);
//
    std::cout<<std::endl;
    std::vector<std::vector<int>> new_res = g.DF(0, -1, 0, res);
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

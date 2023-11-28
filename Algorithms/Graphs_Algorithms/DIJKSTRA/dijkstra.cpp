#include <iostream>


class Graph{

private:
    std::vector<std::vector<std::tuple<int, long long>>> ADJ_LIST;

    std::vector<long long> distance;

    std::vector<int> predecessors;

    int num_vertexes;

public:

    Graph(int n) : num_vertexes(n){ ADJ_LIST.resize(num_vertexes); 
                                    distance.resize(n);
                                    predecessors.resize(n);}

    void DIJKSTRA(int start_vertex) {

        std::priority_queue<std::tuple<long long, int>,
                std::vector<std::tuple<long long, int>>,
                std::greater<>> PQ;

        PQ.emplace(std::make_tuple(0, start_vertex));

        distance[start_vertex] = 0;
        predecessors[start_vertex] = 0; // root

        while (!PQ.empty()) {

            int vertex = std::get<1>(PQ.top());
            PQ.pop();

            for (const auto& adj_tuple: ADJ_LIST[vertex]) {

                int adj_vertex = std::get<0>(adj_tuple);
                long long adj_weight = std::get<1>(adj_tuple);

                if (distance[adj_vertex] > distance[vertex] + adj_weight) {
                    
                    distance[adj_vertex] = distance[vertex] + adj_weight;
                    
                    PQ.push(std::make_tuple(distance[adj_vertex], adj_vertex));
                    
                    predecessors[adj_vertex] = vertex;
                }
            }
        }
    }


    void Dijkstra_Path(int start_vertex)
    {
        int K = 0;
        std::queue<int> QUEUE;

        while(start_vertex != 0)
        {
            QUEUE.push(start_vertex);
            start_vertex = predecessors[start_vertex];

            // K++;
            // std::cout<<start_vertex;
        }
        // fout << K << " ";

        while(!QUEUE.empty())
        {
            fout << QUEUE.front() << " ";
            QUEUE.pop();
        }
        fout << "\n";
    }

};

int main()
{

  return 0;
}

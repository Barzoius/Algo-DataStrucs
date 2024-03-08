std::vector<std::vector<int>> Adjacency_List;
std::vector<bool> VIS;

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

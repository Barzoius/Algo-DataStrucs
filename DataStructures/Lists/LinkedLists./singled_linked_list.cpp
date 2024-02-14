#include <iostream>
#include <vector>
#include <string>

template <typename T>
class List
{

private:

    T val;
    List * next;

public:


    List() : val(T()), next(nullptr){}

    List(T v) : val(v), next(nullptr){}

    List(T v, List * n) : val(v), next(n){};


    int GetVal(List * element) const { return element -> val;}

    void SetVal(T v) { val = v;}

    static List* VConstruct(std::vector<T>& vec)
    {
        List* head = nullptr;
        List* current = nullptr;

        for(int i = 0; i < vec.size(); i++)
        {
            List * temp = new List(vec[i]);

            if(head == nullptr)
            {
                head = temp;
                current = temp;
            }
            else
            {
                current -> next = temp;
                current = current -> next;
            }
        }

        return head;
    }


    static void PrintList(List * head)
    {
        List * current  =  head;
        while(current != nullptr)
        {
            std::cout<<current -> val;
            if(current->next != nullptr)
                std::cout<<" -> ";
            current = current -> next;
        }

        std::cout<<"\n";
    }

};

int main() {

    std::vector<int> vec = {1, 2, 3, 45, 5};
    List<int>* head = List<int>::VConstruct(vec);
    List<int>::PrintList(head);

    std::vector<char> cvec = {'c', 't', 'g', 'f', 'd'};
    List<char>* chead = List<char>::VConstruct(cvec);
    List<char>::PrintList(chead);

    std::vector<std::string> svec = {"asd", "sdsad", "dsa", "fd", "132"};
    List<std::string>* shead = List<std::string>::VConstruct(svec);
    List<std::string>::PrintList(shead);
    return 0;
}


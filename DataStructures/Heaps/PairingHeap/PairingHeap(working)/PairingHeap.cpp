sda#include <iostream>


template <class T>
struct NODE{

    T KEY;
    NODE<T>* CHILD;
    NODE<T>* NEXT; //sib
    NODE<T>* PREV; // prev sib or parent

};

template <typename T>
class PAIRING_HEAP{
private:

    NODE<T>* MERGE(NODE<T>* A, NODE<T>* B)
    {
        if(A == nullptr)
            return B;
        if(B == nullptr)
            return A;

        if(A -> KEY <= B -> KEY)
        {
            B -> PREV = A;
            B -> NEXT = A -> CHILD;
            A -> CHILD = B;
            return A;

        }else // if(B -> KEY <= A -> KEY)
        {
            A -> PREV = B;
            A -> NEXT = B -> CHILD;
            B -> CHILD = A;
            return B;
        }
    }

    NODE<T>* MELD(NODE<T>* FIRST)
    {
        if(FIRST == nullptr || FIRST -> NEXT == nullptr) {
            return FIRST;
        }

        NODE<T>* A = FIRST;
        NODE<T>* B = FIRST -> NEXT;
        NODE<T>* C = B -> NEXT;

        A -> NEXT = nullptr;
        B -> NEXT = nullptr;

        if(C != nullptr)
        {
            C -> PREV = nullptr;
        }

        NODE<T> *MERGED = MERGE(MERGE(A, B), MELD(C));
        MERGED -> PREV = nullptr;
        return MERGED;
    }

public:
    NODE<T>* ROOT;

    PAIRING_HEAP() : ROOT(nullptr){}

    bool EMPTY()
    {
        return ROOT == nullptr;
    }

    T MIN()
    {
        return ROOT -> KEY;
    }

    void INSERT(T KEY)
    {
        auto* NEW_NODE = new NODE<T>; //  NODE<T>* NEW_NODE
        NEW_NODE -> KEY = KEY;
        NEW_NODE ->  NEXT = nullptr;
        NEW_NODE -> PREV = nullptr;
        NEW_NODE -> CHILD = nullptr;

        ROOT = MERGE(ROOT, NEW_NODE);

    }

    void DELETE_ROOT()
    {
        NODE<T>* PREV_ROOT = ROOT;
        ROOT = MELD(ROOT -> CHILD);
        delete PREV_ROOT;
    }

    void DECREASE_KEY(NODE<T>* NODE, const T& NEW_KEY)
    {

        if(NODE -> KEY <= NEW_KEY) { return; }

        NODE -> KEY = NEW_KEY;

        if(NODE == ROOT) { return; }

        if(NODE -> PREV -> CHILD == NODE)
        {
            NODE -> PREV -> CHILD = NODE -> NEXT;

        }else
        {
            NODE -> PREV -> NEXT = NODE ->NEXT;
        }

        if(NODE -> NEXT != nullptr)
        {
            NODE -> NEXT -> PREV = NODE -> PREV;
        }

        NODE -> NEXT = nullptr;
        ROOT = MERGE(ROOT, NODE);
    }

    NODE<T>* FIND_NODE(NODE<T>* NODE, T KEY) {
        if (NODE == nullptr) {
            return nullptr;
        }
        if (NODE->KEY == KEY) {
            return NODE;
        }
        auto CHILD_RE = FIND_NODE(NODE->CHILD, KEY);
        if (CHILD_RE != nullptr) {
            return CHILD_RE;
        }
        return FIND_NODE(NODE->NEXT, KEY);
    }
};

int main()
{
    PAIRING_HEAP<int> A;
    A.INSERT(12);
    A.INSERT(2);
    A.INSERT(17);
    std::cout<< A.MIN()<<std::endl;
    //A.DELETE_ROOT();
    std::cout<<A.MIN()<<std::endl;

    auto node = A.FIND_NODE(A.ROOT, 17);
    A.DECREASE_KEY(node, 1);
    std::cout<<A.MIN()<<std::endl;
}




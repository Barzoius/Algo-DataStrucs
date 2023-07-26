#include <iostream>
#include <memory>
#include <vector>


template<typename T>
class NODE{

public:
    T KEY;
    std::unique_ptr<NODE> PARENT;
    std::unique_ptr<NODE> CHILD;
    std::unique_ptr<NODE> LEFT_BROTHER;
    std::unique_ptr<NODE> RIGHT_BROTHER;

public:

    NODE(const T& key):
        KEY(key),
        PARENT(nullptr),
        CHILD(nullptr),
        LEFT_BROTHER(nullptr),
        RIGHT_BROTHER(nullptr){}

    bool isROOT() const { return PARENT == nullptr; }

};


template <typename T>
class PairingHEAP{

public:
    std::unique_ptr<NODE<T>>ROOT;

public:

    PairingHEAP() : ROOT(nullptr) {}

    bool EMPTY() const { return ROOT == nullptr; }

    void INSERT(const T& KEY)
    {
        std::unique_ptr<NODE<T>> NEW_NODE = std::make_unique<NODE<T>>(KEY);
        ROOT = MELD(std::move(ROOT), std::move(NEW_NODE));
    }

    T FIND_POP_MIN()
    {
        if(ROOT == nullptr){ throw std::out_of_range("THE HEAP IS EMPTY!"); }

        T MIN = ROOT -> KEY;

        std::unique_ptr<NODE<T>> NEW_ROOT = nullptr;
        if(ROOT -> CHILD != nullptr)
        {
            NEW_ROOT = std::move(ROOT -> CHILD);
            NEW_ROOT -> PARENT = nullptr;

            std::unique_ptr<NODE<T>> PREV_CHILD = nullptr;
            std::unique_ptr<NODE<T>> ACTUAL_CHILD = std::move(NEW_ROOT);

            while(ACTUAL_CHILD != nullptr)
            {
                std::unique_ptr<NODE<T>> NEXT_CHILD = std::move(ACTUAL_CHILD -> RIGHT_BROTHER);
                ACTUAL_CHILD -> RIGHT_BROTHER = std::move(PREV_CHILD);
                ACTUAL_CHILD -> LEFT_BROTHER = std::move( NEXT_CHILD);
                PREV_CHILD = std::move(ACTUAL_CHILD);
                ACTUAL_CHILD = std::move(NEXT_CHILD);

            }

            NEW_ROOT = MELDING(std::move(NEW_ROOT));
        }

        ROOT = std::move(NEW_ROOT);

        return MIN;

    }


    std::unique_ptr<NODE<T>> MELD(std::unique_ptr<NODE<T>> THIS, std::unique_ptr<NODE<T>> THAT)
    {
        if(THIS == nullptr)
            return std::move(THAT);
        if(THAT == nullptr)
            return std::move(THIS);

        if(THIS -> KEY < THAT -> KEY)
        {
            THAT -> LEFT_BROTHER = std::move(THIS);
            THIS -> RIGHT_BROTHER = std::move(THAT);
            THIS -> CHILD = MELD(std::move(THIS -> CHILD), std::move(THAT));
            THIS->CHILD -> PARENT = std::move(THIS);
            return std::move(THIS);

        }else
        {
            THIS -> LEFT_BROTHER = std::move(THAT);
            THAT -> RIGHT_BROTHER = std::move(THIS);
            THAT -> CHILD = MELD(std::move(THAT -> CHILD), std::move(THIS));
            THAT -> CHILD -> PARENT = std::move(THAT);
            return std::move(THAT);
        }

    }

    std::unique_ptr<NODE<T>> MELDING(std::unique_ptr<NODE<T>> node)
    {

        if(node == nullptr || node -> RIGHT_BROTHER == nullptr) { return node; }

        std::vector<std::unique_ptr<NODE<T>>> VEC_REP;

        while(node != nullptr)
        {
            std::unique_ptr<NODE<T>> THIS = std::move(node);
            std::unique_ptr<NODE<T>> THAT = std::move(THIS -> RIGHT_BROTHER);
            node = std::move(THAT -> RIGHT_BROTHER);

            THIS -> RIGHT_BROTHER = nullptr;
            THAT -> RIGHT_BROTHER = nullptr;
            THIS -> LEFT_BROTHER = nullptr;
            THAT -> LEFT_BROTHER = nullptr;

            VEC_REP.push_back(MELD(std::move(THIS), std::move(THAT)));
        }

        int LAST = VEC_REP.size() - 1;


        for(int i = LAST; i > 0; i -= 2)
        {
            VEC_REP[i - 1] = MELD(std::move(VEC_REP[i - 1]),std::move( VEC_REP[i]));
        }
        return std::move(VEC_REP[0]);
    }
};


int main() {
    PairingHEAP<int> my_heap; 

    my_heap.INSERT(4); 
    my_heap.INSERT(3);
    my_heap.INSERT(6);
    my_heap.INSERT(2);

    int min_element = my_heap.FIND_POP_MIN(); 
    std::cout << "The minimum element is: " << min_element << std::endl;

    return 0;
}

#include <iostream>
#include <vector>

class BinNode{

    int value;
    BinNode* left_first;
    BinNode* right_second;

    int Parent_Index;

public:
    explicit BinNode(int val) :
     value(val),
     left_first(nullptr),
     right_second(nullptr),
     Parent_Index(-1){}

     void SET_value(int v){ value = v; }
     void SET_index(int i) { Parent_Index = i; }

     int GET_value() const { return value;}
     int GET_index() const { return Parent_Index; }
     BinNode* GET_left() const { return left_first; }
     BinNode* GET_right() const { return right_second; }
};


class BIN_TREE{

    BinNode* TREE;
    std::vector<BinNode> binaryTREE;
    int root;
public:

    BIN_TREE() : TREE(nullptr), root(0){}

    void insert(int val);
    void deletion(int val);
};

void BIN_TREE::insert(int val) {
    if(binaryTREE.at(root).GET_value() == 0)
    {
//        TREE -> SET_index(-1);
        TREE -> SET_value(val);
        binaryTREE[0] = *TREE;
    }
    else{
        if(TREE->GET_left() != nullptr){
            TREE -> GET_left() -> SET_value(val);
        }
            
        
    }
}

void BIN_TREE::deletion(int val) {

}

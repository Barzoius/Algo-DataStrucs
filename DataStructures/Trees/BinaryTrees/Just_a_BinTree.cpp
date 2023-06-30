#include <iostream>

class BinNode{

    int value;
    BinNode* left_first;
    BinNode* right_second;

public: 
    explicit BinNode(int val) :
     value(val),
     left_first(nullptr),
     right_second(nullptr){}
};

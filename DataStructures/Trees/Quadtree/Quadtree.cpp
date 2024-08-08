#include <iostream>
#include <utility>

#define POINT std::pair<int, int>
#define X first
#define Y second

struct NODE
{
private:
    POINT mPos;
    int mData;

public:
    NODE() : mData(0) {}

    NODE(POINT pPos, int pData)
    :
    mPos(std::move(pPos)),
    mData(pData)
    {}
};

class QUAD_TREE
{
private:
    POINT topLeft;
    POINT bottomRight;

    NODE* mNODE;

    QUAD_TREE* topLeftTree;
    QUAD_TREE* topRightTree;
    QUAD_TREE* bottomLeftTree;
    QUAD_TREE* bottomRightTree;

public:


};

int main()
{
    return 0;
}


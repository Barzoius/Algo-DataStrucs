#include <iostream>
#include <vector>

bool isPointOnSegment(std::pair<int, int> point, std::pair<int, int> segStart, std::pair<int, int> segEnd) {
    int xP = point.first, yP = point.second;
    int x1 = segStart.first, y1 = segStart.second;
    int x2 = segEnd.first, y2 = segEnd.second;


    int crossProduct = (y2 - y1) * (xP - x1) - (x2 - x1) * (yP - y1);
    if (crossProduct != 0) {
        return false;
    }

    if (xP < std::min(x1, x2) || xP > std::max(x1, x2) || yP < std::min(y1, y2) || yP > std::max(y1, y2)) {
        return false;
    }

    return true;
}

std::string position(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>& edgeList,
                     std::pair<int, int> point)
{
    int cnt = 0;
    for(const auto& edge : edgeList){
        int xPE1 = edge.first.first;
        int yPE1 = edge.first.second;

        int xPE2 = edge.second.first;
        int yPE2 = edge.second.second;

        if (isPointOnSegment(point, {xPE1, yPE1}, {xPE2, yPE2})) {
            return "BOUNDARY";
        }

        if( (point.second < yPE1) != (point.second < yPE2) &&
             point.first < xPE1 + ((point.second - yPE1) / (yPE2 -yPE1)) * (xPE2 - xPE1) )
            cnt++;
    }

    if(cnt % 2 == 1)
        return "INSIDE";
    else
        return "OUTSIDE";
}

int main(){
    std::vector<std::pair<int, int>> polyPointsList;
    int nr_polyPoints;
    std::cin>>nr_polyPoints;

    int x, y;
    for(int i = 0; i < nr_polyPoints; i++){
        std::cin>>x>>y;
        polyPointsList.emplace_back(std::make_pair(x, y));
    }

    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> edgeList;
    for(int i = 0; i < nr_polyPoints; i++) {
        std::pair<int, int> start = polyPointsList[i];
        std::pair<int, int> end = polyPointsList[(i + 1) % nr_polyPoints];
        edgeList.emplace_back(start, end);
    }

    int nr_points;
    std::cin>>nr_points;
    std::vector<std::pair<int, int>> pointsList;
    for(int i = 0; i < nr_points; i++){
        std::cin>>x>>y;
        pointsList.emplace_back(std::make_pair(x, y));
    }

    for(const auto& point : pointsList){
        std::cout<<position(edgeList, point)<<"\n";
    }

    std::cout<<std::flush;
    return 0;
}


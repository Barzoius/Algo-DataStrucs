#include <iostream>
#include <vector>
#include <utility>

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

std::string position(const std::vector<std::pair<int, int>>& polyPointsList, std::pair<int, int> point) {
    bool isInside = false;
    int cnt = 0;

    for (const auto& polyPoint : polyPointsList) {
        int x1 = polyPoint.first, y1 = polyPoint.second;
        const auto& nextPoint = (polyPoint == polyPointsList.back()) ? polyPointsList.front() : *(std::next(&polyPoint));

        int x2 = nextPoint.first, y2 = nextPoint.second;

        if (isPointOnSegment(point, polyPoint, nextPoint)) {
            return "BOUNDARY";
        }

        if (((y1 > point.second) != (y2 > point.second)) &&
            (point.first < (double)(x2 - x1) * (point.second - y1) / (double)(y2 - y1) + x1)) {
            isInside = !isInside;
            cnt++;
        }
    }

    if (cnt % 2 == 0)
        return "OUTSIDE";
    else
        return "INSIDE";
}

int main() {
    std::vector<std::pair<int, int>> polyPointsList;
    int nr_polyPoints;
    std::cin >> nr_polyPoints;

    int x, y;
    for (int i = 0; i < nr_polyPoints; i++) {
        std::cin >> x >> y;
        polyPointsList.emplace_back(x, y);
    }

    int nr_points;
    std::cin >> nr_points;
    std::vector<std::pair<int, int>> pointsList;
    for (int i = 0; i < nr_points; i++) {
        std::cin >> x >> y;
        pointsList.emplace_back(x, y);
    }

    for (const auto& point : pointsList) {
        std::cout << position(polyPointsList, point) << "\n";
    }

    //std::cout << std::flush;
    return 0;
}

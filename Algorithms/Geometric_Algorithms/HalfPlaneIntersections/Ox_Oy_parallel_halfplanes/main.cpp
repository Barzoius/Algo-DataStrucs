#include <iostream>
#include <vector>
#include <limits>
#include <tuple>

#define SEMIPLANE std::tuple<int, int, int> 

std::string Intersection(int n, const std::vector<SEMIPLANE>& semiplanes) {
    double x_min = -std::numeric_limits<double>::infinity();
    double x_max = std::numeric_limits<double>::infinity();
    double y_min = -std::numeric_limits<double>::infinity();
    double y_max = std::numeric_limits<double>::infinity();

    for (const auto& semiplane : semiplanes) {
        int a, b, c;
        std::tie(a, b, c) = semiplane;

        if (a == 0 && b != 0) { // orizontal
            double y = -static_cast<double>(c) / b;
            if (b > 0) {
                y_max = std::min(y_max, y);
            } else {
                y_min = std::max(y_min, y);
            }
        } else if (b == 0 && a != 0) { // vertical
            double x = -static_cast<double>(c) / a;
            if (a > 0) {
                x_max = std::min(x_max, x);
            } else {
                x_min = std::max(x_min, x);
            }
        }
    }

    if (x_min > x_max || y_min > y_max) {
        return "VOID";
    } else if (x_min == -std::numeric_limits<double>::infinity() || 
               x_max == std::numeric_limits<double>::infinity()  ||
               y_min == -std::numeric_limits<double>::infinity() || 
               y_max == std::numeric_limits<double>::infinity()) {
        return "UNBOUNDED";
    } else {
        return "BOUNDED";
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<SEMIPLANE> semiplanes(n);
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        semiplanes[i] = std::make_tuple(a, b, c);
    }

    std::cout << Intersection(n, semiplanes) << std::endl;
    retur

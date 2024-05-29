#include <iostream>

//  | 1   1   1  |
//  | p1  q1  r1 |
//  | p2  q2  r2 |

// (1 * q1 * r2) + (p1 * q2 * 1) + (1 * r1 * p2) -
// (p2 * q1 * 1) - (1 * q2 * r1) - (p1 * 1 * r2)
int determinant(std::pair<int, int> p, std::pair<int, int> q, std::pair<int, int> r) {
    return (p.first * q.second) + (p.second * r.first) + (q.first * r.second) -
           (q.second * r.first) - (p.first * r.second) - (p.second * q.first);
}



void pozitie_punct(std::pair<int, int> p, std::pair<int, int> q, std::pair<int, int> r) {
    int det = determinant(p, q, r);
    if (det == 0)
        std::cout << "TOUCH" << std::endl;
    else if (det < 0)
        std::cout << "RIGHT" << std::endl;
    else
        std::cout << "LEFT" << std::endl;
}

int main() {
    int tests;
    std::cin >> tests;

    for (int i = 0; i < tests; ++i) {
        std::pair<int, int> p, q, r;
        std::cin >> p.first >> p.second >> q.first >> q.second >> r.first >> r.second;
        pozitie_punct(p, q, r);
    }

    return 0;
}

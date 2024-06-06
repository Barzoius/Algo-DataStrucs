#include <iostream>
#include <vector>

#define point std::pair<int, int>
#define x first
#define y second

// | A.x  A.y  (A.x^2 + A.y^2)  1 |
// | B.x  B.y  (B.x^2 + B.y^2)  1 |
// | C.x  A.y  (C.x^2 + C.y^2)  1 |
// | D.x  D.y  (D.x^2 + D.y^2)  1 |

double determinant3x3(double a1, double a2, double a3,
                      double b1, double b2, double b3,
                      double c1, double c2, double c3) {
    return a1 * (b2 * c3 - b3 * c2) -
           a2 * (b1 * c3 - b3 * c1) +
           a3 * (b1 * c2 - b2 * c1);
}

double determinant4x4(point A, point B, point C, point D) {
    double a1 = A.x, a2 = A.y, a3 = A.x * A.x + A.y * A.y, a4 = 1;
    double b1 = B.x, b2 = B.y, b3 = B.x * B.x + B.y * B.y, b4 = 1;
    double c1 = C.x, c2 = C.y, c3 = C.x * C.x + C.y * C.y, c4 = 1;
    double d1 = D.x, d2 = D.y, d3 = D.x * D.x + D.y * D.y, d4 = 1;

    double det = a1 * determinant3x3(b2, b3, b4,
                                     c2, c3, c4,
                                     d2, d3, d4)
                 - a2 * determinant3x3(b1, b3, b4,
                                       c1, c3, c4,
                                       d1, d3, d4)
                 + a3 * determinant3x3(b1, b2, b4,
                                       c1, c2, c4,
                                       d1, d2, d4)
                 - a4 * determinant3x3(b1, b2, b3,
                                       c1, c2, c3,
                                       d1, d2, d3);

    return det;
}


int main() {
    point A, B, C;

    std::cin>>A.x>>A.y;
    std::cin>>B.x>>B.y;
    std::cin>>C.x>>C.y;

    int num_points;
    std::cin>>num_points;

    std::vector<point> points(num_points);;
    for(int i = 0; i < num_points; i++)
        std::cin>>points[i].x >> points[i].y;

    for(auto & D : points){
        double rez = determinant4x4(A, B, C, D);
        if(rez > 0)
            std::cout<<"INSIDE"<<"\n";
        else if(rez < 0)
            std::cout<<"OUTSIDE"<<"\n";
        else if(rez == 0)
            std::cout<<"BOUNDARY"<<"\n";
    }
    return 0;
}

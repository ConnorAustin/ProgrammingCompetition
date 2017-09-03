#include <iostream>
#include <cmath>

#define pi 3.141592653589793

int main() {
    double xa, xb, xd, ya, yb, yd;
    std::cin >> xa >> ya >> xb >> yb >> xd >> yd;
    
    double K = -2 * (xd + xb);
    double L = 2 * (yd - ya);
    double M = xd*xd - xa*xa - ya*ya + yd*yd;
    double N = -2 * (xb + xb);
    double O = 2 * (yd - yb);
    double P = xd*xd - xb*xb - yb*yb + yd*yd;
    
    /*Kx + Ly = M
    Nx + Oy = P
    
    x = (M - Ly) / K
    (N * (M - Ly) / K) + Oy = P
    
    NM/K - NLy/K + Oy = P
    NM/K - y(NL/K + O) = P*/
    
    double y = (N*M/K - P) / (N*L/K + O);
    double x = (M - L*y) / K;
    
    double xdiff = x - xa;
    double ydiff = y - ya;
    double radius = sqrt(xdiff * xdiff + ydiff*ydiff);
    std::cout << 2 * radius * pi << std::endl;
}

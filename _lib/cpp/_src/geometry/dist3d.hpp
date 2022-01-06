#include "../macros.hpp"

// 3次元での2点間距離√((x1-x2)^2+(y1-y2)^2+(z1-z2)^2)
ld dist3d(tuple<ld, ld, ld> a, tuple<ld, ld, ld> b) {
    return sqrt((get<0>(a)-get<0>(b))*(get<0>(a)-get<0>(b))+(get<1>(a)-get<1>(b))*(get<1>(a)-get<1>(b))+(get<2>(a)-get<2>(b))*(get<2>(a)-get<2>(b)));
}

#include "../macros.hpp"

// 余弦定理(辺a,bと間の角度degから、反対側の辺cを求める)
ld cos_formula(ld a, ld b, ld deg) {
    return sqrt(a*a+b*b-2*a*b*cos(radians(deg)));
}

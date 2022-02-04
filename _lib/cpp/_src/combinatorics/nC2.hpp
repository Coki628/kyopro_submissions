#include "../macros.hpp"

ll nC2(ll n) {
    if (n < 2) return 0;
    return n*(n-1)/2;
}

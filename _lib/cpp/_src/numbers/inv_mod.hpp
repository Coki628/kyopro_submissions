#pragma once
#include "extgcd.hpp"

// MOD逆元(modが素数でなくても、aとmodが互いに素なら可)
template<typename T>
T inv_mod(T a, T mod) {
    T x, y;
    extgcd(a, mod, x, y);
    return (mod + x%mod) % mod;
}

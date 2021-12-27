#include "../macros.hpp"
#include "mt.hpp"

// [l,r)の範囲で乱数生成
ll randrange(ll l, ll r) {
    uniform_int_distribution<ll> rand(l, r-1);
    return rand(mt);
}

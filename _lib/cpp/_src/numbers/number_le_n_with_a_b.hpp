#include "../macros.hpp"

// N以下の自然数でa+b=xを作る通り数
ll number_le_n_with_a_b(ll n, ll x) {
    return max(min(x-1, n*2+1-x), 0LL);
}

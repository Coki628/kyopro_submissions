#include "../macros.hpp"

// ピタゴラス数(未整備。重複削除とかgcdで互いに素とか考えてない。)
vector<ll> pythagorean_triple(ll m, ll n) {
    ll a = abs(pow(m, 2) - pow(n, 2));
    ll b = 2*m*n;
    ll c = pow(m, 2) + pow(n, 2);
    vector<ll> res = {a, b, c};
    sort(ALL(res));
    return res;
}

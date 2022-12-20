/*
・なんとか自力AC！
・ソートして愚直シミュしながら、他方はsetから消していけばいいんだけど、
　1匹倒した瞬間に次受けるダメージ量は、同じタイミングで倒れた敵を
　全て考慮した後に決めないといけないのでややめんどい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> H(N), P(N);
    cin >> H >> P;

    vector<pll> HI;
    rep(i, N) {
        HI.eb(H[i], i);
    }
    sort(ALL(HI));
    set<pll> se;
    rep(i, N) {
        se.insert({P[i], i});
    }

    ll i = 0;
    ll curd = 0, curk = K;
    while (i < N) {
        auto [h, j] = HI[i];
        ll curp = se.begin()->first;
        while (curd < h and curk > 0) {
            curd += curk;
            if (curd < h) {
                curk = max(curk - curp, 0LL);
            }
        }
        if (HI[i].first > curd) {
            NO();
            return;
        }
        while (i < N and HI[i].first <= curd) {
            auto [h, j] = HI[i];
            se.erase({P[j], j});
            i++;
        }
        if (i < N) {
            assert(se.size());
            curp = se.begin()->first;
            curk = max(curk - curp, 0LL);
        }
    }
    YES();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

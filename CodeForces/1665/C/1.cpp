/*
・きっちり自力AC！
・遅延セグ木、区間加算・区間最大値取得
・子要素の数で各要素を管理。根を子と見た分で1を加える。
　ソートして、大きい方から感染させてく。
　全グループ感染したら、その時一番多い所をやる。
　区間加算・区間最大値取得の遅延セグ木使ったら愚直っぽくシミュれた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N-1);
    rep(i, N-1) P[i]--;
    vector<ll> C(N);
    rep(i, N-1) {
        C[P[i]]++;
    }

    vector<ll> healthy;
    rep(i, N) {
        if (C[i]) healthy.eb(C[i]);
    }
    healthy.eb(1);
    ll M = healthy.size();
    sort(healthy.rbegin(), healthy.rend());
    auto infected = get_lazy_segment_tree(f, g, h, T, E);
    infected.build(vector<ll>(M, 0));
    rep(i, M) {
        infected.update(0, i, -1);
        infected.update(i, healthy[i]-1);
    }
    ll sec = M;
    while (infected.query(0, M) > 0) {
        infected.update(0, M, -1);
        ll mx = infected.query(0, M);
        ll i = infected.find_first(0, [&](ll x) { return x >= mx; });
        infected.update(i, -1);
        sec++;
    }
    print(sec);
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

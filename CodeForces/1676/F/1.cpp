/*
・自力AC！若干もたついた。。
・Kの条件を満たす候補だけ先に集めておいて、
　ソートしてランレングスっぽく見ていく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    auto C = Counter(A);
    vector<ll> vec;
    for (auto [k, v] : C) {
        if (v >= K) {
            vec.eb(k);
        }
    }
    sort(ALL(vec));

    if (vec.empty()) {
        print(-1);
        return;
    }
    ll mx = -INF;
    pll cur = {vec[0], vec[0]}, ans;
    rep(i, 1, vec.size()) {
        if (vec[i - 1] + 1 == vec[i]) {
            cur.second = vec[i];
        } else {
            if (chmax(mx, cur.second - cur.first)) {
                ans = cur;
            }
            cur = {vec[i], vec[i]};
        }
    }
    if (chmax(mx, cur.second - cur.first)) {
        ans = cur;
    }
    print(ans);
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

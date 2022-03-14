/*
・きっちり自力AC！
・L,R毎のY座標毎に隣接リストに持ってソートしてRの先頭とLの末尾を比較。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }
    string S;
    cin >> S;

    map<ll, vector<ll>> adjl, adjr;
    rep(i, N) {
        if (S[i] == 'L') {
            adjl[Y[i]].eb(X[i]);
        } else {
            adjr[Y[i]].eb(X[i]);
        }
    }
    for (auto& [k, v] : adjl) {
        sort(ALL(v));
    }
    for (auto& [k, v] : adjr) {
        sort(ALL(v));
        if (adjl.count(k)) {
            if (v[0] <= adjl[k].back()) {
                Yes();
                return;
            }
        }
    }
    No();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

/*
・色々試すと、OKであれば比較的N+1以降早い値で確定していたので、
　じゃあもう100くらい試せばいけんじゃね？って感じで投げたのがこれ。
　まあWAなんだけど。。。
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
    auto A =  LIST(N);

    UNIQUE(A);
    if (A.size() < N) {
        NO();
        return;
    }

    set<ll> ok;
    vector<ll> rest;
    rep(i, N) {
        if (A[i] <= N) {
            ok.insert(A[i]);
        } else {
            rest.eb(A[i]);
        }
    }
    if (rest.empty()) {
        YES();
        return;
    }
    vector<ll> expected(N);
    iota(ALL(expected), 1);
    rep(mod, N+1, N+100) {
        auto cur = ok;
        for (auto a : rest) {
            cur.insert(a%mod);
        }
        vector<ll> ans(ALL(cur));
        if (ans == expected) {
            cout << "YES " << mod << '\n';
            return;
        }
    }
    NO();
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

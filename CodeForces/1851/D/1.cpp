/*
・自力AC！
・累積和から元の列の復元なので、差分列取るとだいたい分かるんだけど、ちょっとめんどい。
　結局サンプル合うかどうか色々ガチャガチャやって適当に投げる感じになってしまった。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N - 1);
    cin >> A;
    
    vector<ll> B(N - 1);
    B[0] = A[0];
    rep(i, 1, N - 1) {
        B[i] = A[i] - A[i - 1];
    }
    ll sm = 0;
    rep(i, 1, N + 1) {
        sm += i;
    }
    vector<ll> C(N + 1);
    set<ll> se;
    vector<ll> vec;
    rep(i, N - 1) {
        if (not se.count(B[i]) and B[i] <= N) {
            C[B[i]] = 1;
        } else {
            vec.eb(B[i]);
        }
        se.insert(B[i]);
    }
    if (vec.size() == 1 and sum(B) == sm or sum(C) == N - 1) {
        YES();
    } else {
        NO();
    }
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

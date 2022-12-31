/*
・なんとか自力AC…。
・ぱっと浮かばずさっさと愚直書いて実験した。
　けどあんまりいい感じの法則も見えず。
　結局ガチャガチャした後「K個毎に見て、0個目に大きいの、
　K-1個目に小さいのを入れて、残りは適当に埋める」ってやって通った…。
・終了後TLによると、N,1,N-1,2...で通るらしい。
　結構近いのは割と最初にやったんだけどね。。
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

    vector<ll> P(N);
    iota(ALL(P), 1);
    // ll ans = INF;
    // vector<ll> vec;
    // for (auto perm : permutations(P)) {
    //     ll res = 0;
    //     rep(i, N - K + 1) {
    //         ll mx = -INF, mn = INF;
    //         rep(j, i, i + K) {
    //             chmax(mx, perm[j]);
    //             chmin(mn, perm[j]);
    //         }
    //         chmax(res, mx + mn);
    //     }
    //     if (chmin(ans, res)) {
    //         vec = perm;
    //     }
    // }
    // print(ans);
    // print(vec);

    if (K == 1) {
        print(P);
        return;
    }

    deque<ll> que(ALL(P));
    vector<ll> ans(N, -1);
    ll i = 0;
    while (i < N) {
        ans[i] = que.back();
        que.pop_back();
        if (i != N - 1) {
            ans[min(i + K - 1, N - 1)] = que.front();
            que.pop_front();
        }
        i += K;
    }
    rep(i, N) {
        if (ans[i] == -1) {
            ans[i] = que.back();
            que.pop_back();
        }
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

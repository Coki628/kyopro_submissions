/*
ライブラリ整備：Suffix Array
・ACLをラップした。とりあえず今回の問題で必要な機能しか付けてないので、
　今後必要に応じて追加していく予定。
・速度は0.39秒→0.49秒くらいで若干遅くなってる。
　まあ機能が分かりやすく可視化するのであれば許容範囲内。
　(saの添字周りまじでややこしいし)
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

#include "string/SuffixArray.hpp"

void solve() {
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    auto U = S + S + T + T;
    SuffixArray sa(U);
    // P[i] := sa内でi番目にある文字列Tの、saのindex(ややこしい)
    vector<int> P;
    rep(i, N*4) {
        if (N*2 <= sa.sa[i] and sa.sa[i] < N*3) {
            P.eb(i);
        }
    }
    ll ans = 0;
    rep(i, N) {
        ll res = bisearch_min(-1, N, [&](ll x) {
            ll j = sa.sa[P[x]];
            // U[i]とU[j]のLCPを取得
            ll len = sa.get_lcp(i, j);
            if (len >= N) return true;
            return U[i+len] <= U[j+len];
        });
        ans += N - res;
    }
    print(ans);
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

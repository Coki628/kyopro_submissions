/*
・自力AC！これ手際よく通せたのは良かった。
・制約の但し書きにある完全ランダムだよみたいな記述が気になる。
　大きいビットから貪欲に立てたい。片方は全体を使うとして、
　ペアに何個ずらした位置を使うかN-1個を候補にしておく。
　全体を大きいビットから見ていって0があったら、その位置を立てれる候補だけ残す。
　完全ランダムならここで毎回半分くらいに減るはずなので、
　結局全体が10^6あってもこれをやる回数はそう多くない。
　最後リーディングゼロを忘れずに除去(みんな1ペナこれ？)。空文字列には0追加。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    vector<ll> cur(N-1);
    iota(ALL(cur), 1);
    auto ans = S;
    rep(i, N) {
        if (S[i] == '0') {
            vector<ll> nxt;
            bool ok = false;
            rep(j, cur.size()) {
                ll k = i - (N-cur[j]);
                if (k >= 0 and S[k] == '1') {
                    nxt.eb(cur[j]);
                    ok = true;
                }
            }
            if (ok) {
                swap(cur, nxt);
                ans[i] = '1';
            }
        }
    }
    reverse(ALL(ans));
    while (ans.back() == '0') {
        ans.pop_back();
    }
    if (ans.empty()) {
        ans += '0';
    }
    reverse(ALL(ans));
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

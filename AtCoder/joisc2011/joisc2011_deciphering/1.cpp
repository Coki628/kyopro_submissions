/*
・JOI埋め
・自力AC！
・部分文字列DP、貰うDP、種類数のDP
・部分列を重複なく数えるやつ。配るDP的なのと貰うDP的なのがあるけど後者でやった。
　文字の並びに制約がなければ、同じ文字の前回出現位置以降から区間の遷移をすればいいが、
　遷移させるとダメな文字の組があるので、状態を最後に使った文字毎に分けて管理。
　毎回区間和を26回取ることになるけど、これはまあ間に合うでしょってことで。
　TLが0.5秒のlog許さないマン設定だったけど、無事AC0.32秒。
　最初前計算をmapでやっていて0.40秒だったのを、vectorに変えて少し速くした。
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
constexpr int MOD = 10000000;
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
    vector<ll> A(N);
    rep(i, N) A[i] = S[i] - 'A';
    ll M;
    cin >> M;
    ll L = 26;
    auto ng = list2d(L+1, L+1, false);
    rep(i, M) {
        char a, b;
        cin >> a >> b;
        ng[a-'A'][b-'A'] = true;
    }

    // prv[i] := i番目の要素と同じ値が直前に出現したindex
    vector<ll> prv(N), mp(L, -1);
    rep(i, N) {
        if (mp[A[i]] != -1) {
            prv[i] = mp[A[i]];
        }
        mp[A[i]] = i + 1;
    }

    // dp[c][i] := 最後に文字cを位置iで使った通り数
    vector<BIT<mint>> dp(L+1, BIT<mint>{N+1});
    dp[L].add(0, 1);
    rep(i, N) {
        rep(c, L+1) {
            if (ng[c][A[i]]) continue;
            // 直前にその値を使った位置以降から遷移
            dp[A[i]].add(i+1, dp[c].query(prv[i], i+1));
        }
    }
    mint ans = 0;
    rep(i, N) {
        ans += dp[A[i]][i+1];
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

/*
・きっちり自力AC！
・インタラクティブ
・難読。full spanning forestってなんだよ…。でもまあ全域木の森版だと思えば良さそう。
　で、どうやらクエリに対して、返答はその全域森？のでかい方を返すらしい。
　予め辺コストは1箇所だけのクエリで調べておく。
　最小全域木作る時みたいにコスト小さい方から繋いでみて、
　今の総コスト+その辺のコスト=クエリの返答となったらその辺は採用、
　ってやったらうまくいく気がして、実際うまくいった。
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

// インタラクティブ用
ll ask(string s) {
    ll res;
    cout << "? " << s << endl;
    cin >> res;
    return res;
}

void answer(ll i) {
    cout << "! " << i << endl;
}

void solve() {
    ll N, M;
    cin >> N >> M;

    vector<pll> P(M);
    string S(M, '0');
    rep(i, M) {
        S[i] = '1';
        P[i] = {ask(S), i};
        S[i] = '0';
    }
    sort(ALL(P));
    ll ans = 0;
    for (auto [cost, i] : P) {
        S[i] = '1';
        ll res = ask(S);
        if (ans+cost == res) {
            ans += cost;
        } else {
            S[i] = '0';
        }
    }
    answer(ans);
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

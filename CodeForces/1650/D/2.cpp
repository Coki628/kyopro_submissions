/*
・自力AC。
・サイクルシフト
・後から貪欲に。前半切って後半くっつけてみたいのvectorだとやりづらくてpython使いたくなった。
　vectorにサイクルシフトの関数あったのは思い出したけど、名前出てこなかったのと、
　それなりに扱いにくかったような覚えがあったので、分解と連結で済ませてしまった。
・↑やった。「サイクルシフト」で検索かけたらcf1579_bが出てきて、ちゃんと使い方書いてあったから
　そんなに面倒じゃなかった。これなら調べてこっちやった方が早かったかな…。
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
    auto A = LIST(N);
    rep(i, N) A[i]--;

    vector<ll> ans(N);
    rep(i, N-1, -1, -1) {
        rep(j, i-1, -1, -1) {
            if (A[j] == i) {
                ans[i] = j+1;
                // rotate(l, m, r) : [l,r)の範囲で、mが先頭、m-1が末尾になるように左シフトする
                rotate(A.begin(), A.begin()+j+1, A.begin()+i+1);
                break;
            }
        }
    }
    vector<ll> expected(N);
    iota(ALL(expected), 0);
    assert(A == expected);
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

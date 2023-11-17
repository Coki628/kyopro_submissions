/*
・なんとか自力AC！本日のボトルネック…。
・順列、配列の構築
・2乗OKの制約を見逃したまま結構悩んだのが致命傷だった。
　それが分かれば比較的愚直っぽいシミュができる。
　最大値を先頭にするためには、
　3つ目のブロックの先頭にそれを持ってくるのはほぼ必須なので、
　後ろの区切りrはそこで固定して前の区切りlを全探索する。
　先頭が最大値だと2番目を狙う必要があるのと、
　3つ目のブロックを無にして2つ目のブロックを先頭にするケースがあるのだが、
　どちらもご丁寧にサンプルに入っているので、色々確認しながら実装できる。
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
    vector<ll> P(N);
    cin >> P;

    vector<ll> ans(N);
    iota(ALL(ans), 1);
    ll r = find(ALL(P), P[0] == N ? N - 1 : N) - P.begin();
    rep(l, r) {
        auto v1 = subarray(P, 0, l);
        auto v2 = subarray(P, l, r);
        auto v3 = subarray(P, r, N);
        auto cur = concat(concat(v3, reversed(v2)), v1);
        chmax(ans, cur);
    }
    // l=N-1,r=N
    auto cur = concat(subarray(P, N - 1, N), subarray(P, 0, N - 1));
    chmax(ans, cur);
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

/*
参考：https://atcoder.jp/contests/abc297/editorial/6172
・自力ならず。
・ゲーム、複数山Nim、Grundy数、メモ化再帰、実験エスパー
・各山Grundy数求めてxorと思ったけど各山のGrundy数が求まらず…。
・さて、公式解説でさえ実験してみろって言ってる。これはもう面倒がらずやるしかない。
　このくらいのGrundy数のDPはためらわず息を吸うように書けるべきなんだろう。
　で、実際書いてみて適当にL,Rを2,3個試すと、
　確かにそれだけであからさまな規則性が見える。やるべきなんだよなぁ。
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
    ll N, L, R;
    cin >> N >> L >> R;
    vector<ll> A(N);
    cin >> A;

    // vector<ll> grundy(30, -1);
    // auto rec = [&](auto &&f, ll i) {
    //     if (grundy[i] != -1) {
    //         return grundy[i];
    //     }
    //     set<ll> se;
    //     rep(j, L, R + 1) {
    //         if (i - j >= 0) {
    //             se.insert(f(f, i - j));
    //         }
    //     }
    //     ll g = 0;
    //     while (se.count(g)) g++;
    //     grundy[i] = g;
    //     return g;
    // };
    // rep(x, 30) {
    //     grundy[x] = rec(rec, x);
    // }
    // -> floor(x mod (L + R), L)

    vector<ll> B(N);
    rep(i, N) {
        B[i] = (A[i] % (L + R)) / L;
    }
    ll res = 0;
    rep(i, N) {
        res ^= B[i];
    }
    if (res) {
        print("First");
    } else {
        print("Second");
    }
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

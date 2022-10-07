/*
・公式解より
・ダブリング
・公式解は再帰でやってたけど、とりあえず慣れた形に近い方法で。
　それでも今まで見てきたダブリングと結構雰囲気違う。
　2冪だけ前計算しておいて、使う時には必要な部分だけ使ってちょうどいい数にする。
　冪乗の計算に使う繰り返し二乗法の感じに近いのかもしんない。
　結構重くて、AC0.59秒。多分一番深いとこでpowpowみたいなことしてるから。
・↑前計算した。やっぱりすげー速くなってAC0.05秒。
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
// using mint = ModInt<MOD>;
#include "template.hpp"

#include "combinatorics/ArbitraryModInt.hpp"
using mint = ArbitraryModInt;

void solve() {
    ll K, M;
    cin >> K >> M;
    mint::set_mod(M);

    ll L = 40;
    // pow10[k] := 10^(2^k) mod M (今の値を2^k桁ずらすのに使う)
    vector<mint> pow10(L);
    rep(k, L) {
        pow10[k] = pow(10, pow(2, k), M);
    }
    // db[a][k] := 数字aが2^k個連なった値 mod M
    auto db = listnd(10, L, (mint)0);
    rep(a, 10) {
        db[a][0] = a;
        rep(k, 1, L) {
            // 前の値を10冪でずらした所に前の値を足し込む
            db[a][k] =  db[a][k-1]*pow10[k-1] + db[a][k-1];
        }
    }

    mint ans = 0;
    rep(i, K) {
        ll c, d;
        cin >> c >> d;
        rep(k, L-1, -1, -1) {
            if (d>>k & 1) {
                // d個ちょうどになるように2冪から選んで使う(桁をずらしながら)
                ans = ans*pow10[k] + db[c][k];
            }
        }
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

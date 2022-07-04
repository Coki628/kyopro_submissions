/*
参考：https://discuss.codechef.com/t/lcmseq-editorial/101986
・自力ならず。。結構いい方針で考察できてたみたいなので悔しい。
・約数列挙、重複を省いて数え上げ
・題意に該当する部分列のパターンは2つだけで、
　・全部の値が同じ
　・要素全てが列の長さlenの倍数
　の2種類。前者はCounterすればすぐ数えられて、2^出現数から、
　空集合と要素が1つだけの分を引く。(長さ2以上が条件なので)
　後者は約数列挙N回でも間に合うので、やる。
・この2つには重複があるので、その分は引く。ここの詰めが足りず。。
　前者が被るのを、値が長さlenと同値のものしか見てなかった。
　各値について、約数全部について前者との重複を取り除くようにするとうまくいく。
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
    auto A = LIST(N);

    ModTools<mint> mt(N);
    auto C = Counter(A);
    vector<ll> C2(N+1);
    mint ans = 0;
    for (auto [k, v] : C) {
        ans += mint(2).pow(v) - v - 1;
        for (auto div : divisors(k)) {
            if (1 < div and div <= N) {
                C2[div] += v;
                ans -= mt.nCr(v, div);
            }
        }
    }
    rep(len, 2, N+1) {
        ans += mt.nCr(C2[len], len);
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

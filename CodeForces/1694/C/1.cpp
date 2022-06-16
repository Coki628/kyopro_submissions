/*
参考：https://twitter.com/shiro537/status/1537473907979980800
　　　https://twitter.com/butsurizuki/status/1537475044023996417
・自力ならず。まあ時間10分くらいしかなかったんだけどね…。
・じっくり考えられたとして分かったかは分からないんだけど、とりあえず方針を。
　まず自明に無理なやつを処理。で、この後何をするか考える。
　最後にA[0]に戻らないといけないので、後ろから順に最後に訪問する瞬間がある。
　それと、途中をどう移動しようと、端の確実な所から決めていけば、
　各所を通った回数の累計は一意になる。(多分)
　なので右端から順に辻褄を合わせようとすると、後ろから累積和みたいな形になる。
　一度でも通ってれば0未満、通ってなければ0であることを必要条件として、
　順に見ていけばOK。最後、A[0]は0であること。
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

    if (A.back() > 0) {
        No();
        return;
    }
    if (A[0] == 0 and count(ALL(A), 0) < N) {
        No();
        return;
    }

    bool visited = false;
    rep(i, N-1, 0, -1) {
        if (A[i] < 0) {
            visited = true;
        }
        if (A[i] > 0) {
            No();
            return;
        }
        if (visited and A[i] >= 0) {
            No();
            return;
        }
        A[i-1] += A[i];
    }
    if (A[0] == 0) {
        Yes();
    } else {
        No();
    }
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

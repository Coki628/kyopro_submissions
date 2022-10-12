/*
・自力AC。遅い。
・末尾の文字でまず判定、同じなら文字列長、ってやろうとして地味にガチャガチャしたあと、
　Sなら文字列長引いてLなら文字列長足すみたいな重み付けでいいと気付いた。
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
    string a, b;
    cin >> a >> b;

    vector<string> vec = {a, b};
    vector<ll> val(2);
    rep(i, 2) {
        auto base = vec[i].back();
        if (base == 'S') {
            val[i] -= vec[i].size();
        } elif (base == 'L') {
            val[i] += vec[i].size();
        }
    }
    if (val[0] < val[1]) {
        print("<");
    } elif (val[0] == val[1]) {
        print("=");
    } else {
        print(">");
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

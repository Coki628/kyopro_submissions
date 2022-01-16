/*
・動作確認テスト用
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "_src/macros.hpp"

#include "_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "_src/template.hpp"

// template<typename T, typename F>
// vector<T> accumulate(vector<T> &A, const F &func=[](T a, T b) { return a + b; }) {
//     int N = A.size();
//     if (!N) return {};
//     vector<T> res(N);
//     res[0] = A[0];
//     rep(i, 1, N) res[i] = func(res[i-1], A[i]);
//     return res;
// }

void solve() {
    // splitとjoin
    // string S = "123:12:23";
    // auto v1 = mapping<ll>(split(S, ':'), [](string s) { return toint(s); });
    // print(v1);
    // auto T1 = join(v1);
    // auto T2 = join(v1, ',');
    // print(T1);
    // print(T2);
    // auto v2 = split(S, ':');
    // auto T3 = join(v2, '.');
    // print(T3);
    // auto T4 = join(v2);
    // print(T4);
    // print(join(v2, '\n'));

    // vector<pll> V = {{1, 3}, {3, 2}, {4, 7}};
    // print(V);
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

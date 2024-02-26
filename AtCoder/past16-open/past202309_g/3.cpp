/*
・本番中、正しく組めなかった再帰全探索の解法。
　これはさすがにちゃんと組めるようにしときたいので通しておいた。
　abc236_dで「2つ選んでから潜る」パターンをやっていたが、
　これは3つ選んでから潜る。使用済フラグを管理しつつ、
　普通に3重ループを再帰の内側で書いたらちゃんと動いた。
　ただしこれだと各N個の三角形間の順序が全て考慮されてしまうので、
　最後にN!の重複度で割る調整をしている。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "combinatorics/factorial.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N * 3);
    cin >> A;

    ll ans = 0;
    vector<int> used(N * 3);
    auto rec = [&](auto rec, ll n) {
        if (n == N) {
            ans++;
            return;
        }
        vector<ll> vec;
        rep(i, N * 3) {
            if (used[i]) continue;
            vec.eb(i);
            rep(j, i + 1, N * 3) {
                if (used[j]) continue;
                vec.eb(j);
                rep(k, j + 1, N * 3) {
                    if (used[k]) continue;
                    vec.eb(k);
                    auto tmp = vec;
                    sort(ALL(vec), [&](ll a, ll b) { return A[a] < A[b]; });
                    if (A[vec[0]] + A[vec[1]] > A[vec[2]]) {
                        used[vec[0]] = true;
                        used[vec[1]] = true;
                        used[vec[2]] = true;
                        rec(rec, n + 1);
                        used[vec[0]] = false;
                        used[vec[1]] = false;
                        used[vec[2]] = false;
                    }
                    vec = tmp;
                    vec.pop_back();
                }
                vec.pop_back();
            }
            vec.pop_back();
        }
    };
    rec(rec, 0);
    ans /= factorial<ll>(N);
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

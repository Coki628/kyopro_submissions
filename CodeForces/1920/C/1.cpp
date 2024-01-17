/*
・なんとか自力AC！
・約数列挙、差分GCD
・全約数kについて、うまくいくかA[i]全部チェックする全探索はできる。
　2以上の好きなMODで全要素同じにするとのことだが、
　ぐっと睨んで差分GCDでいけそうな気がしたのでやったら無事AC。。。
・本番中はAC2.12秒(制約3秒)だったけど、終わってから
　これソートしなくてもいけるぽくないかな、って投げてみたら無事AC1.22秒。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll ans = 0;
    for (auto k : divisors(N)) {
        vvl adj(k);
        rep(i, N) {
            adj[i % k].eb(A[i]);
        }
        ll g = 0;
        rep(i, k) {
            // sort(ALL(adj[i]));
            rep(j, 1, adj[i].size()) {
                g = gcd(g, abs(adj[i][j] - adj[i][j - 1]));
            }
        }
        if (g != 1) {
            ans++;
        }
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
